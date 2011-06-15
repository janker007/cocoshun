#include<stdio.h>
#include<winsock2.h>
#include<string.h>
#include<windows.h>
#include<mstcpip.h>
#pragma comment(lib,"ws2_32.lib")
#define RECVPORT 7000     //�󶨵ĽӰ��˿ں�

struct iphdr
{
	unsigned char head;
	unsigned char tos;
	unsigned short length;     //IP��ͷ����
	unsigned short flags;
	unsigned short offset;
	unsigned char ttl;
	unsigned char protc;
	unsigned short checksum;
	unsigned int sourceip;
	unsigned int destip; 
};

struct udphdr
{
	unsigned int sourceport;
	unsigned int destport;
	unsigned int length;				//UDP��ͷ����
	unsigned int checksum;
};

struct tcphdr
{
	USHORT sourceport;
	USHORT destport;
	unsigned int seq;
	unsigned int ack;					//TCP��ͷ����
	unsigned char offset;
	unsigned char flags;
	USHORT win;
	USHORT checksum;
	USHORT urg;
};

	FILE *f;
	char orig[100],*p,end;
	char type[20]={0},version[20]={0},plat[20]={0},ttl[20]={0},win[20]={0},df[20]={0},tos[20]={0};
	int i=0,j=0;
	int ttli,dfi,tosi,winb,wine;
	bool winf=false;
	

int solve(char *buff,char cmd)          //�����������
{	
	struct iphdr *ip;
	struct tcphdr *tcp;
	struct udphdr *udp;
	struct sockaddr_in test1,test2;
	BYTE *datat=NULL,*datau=NULL;
	BYTE test;

	ip=(struct iphdr*)buff;												//ȡIPͷ
	tcp=(struct tcphdr*)(buff+((ip->head)&0xf)*sizeof(unsigned int)); //ȡTCPͷ
    udp=(struct udphdr*)(buff+((ip->head)&0xf)*sizeof(unsigned int)); //ȡUDPͷ
	test1.sin_addr.s_addr=ip->sourceip;
    test2.sin_addr.s_addr=ip->destip;
	datat=((BYTE *)tcp)+(tcp->offset>>4)*4;
	datau=(BYTE *)udp;

	if(cmd!='a'&&cmd!='t'&&cmd!='u'&&cmd!='A'&&cmd!='T'&&cmd!='U')
	{
		printf("command error!");                          //�ж����������Ƿ���ȷ
		exit(0);
	}
	else if((cmd=='t'||cmd=='T')&&ip->protc!=6)            
		return 0;                                            //�ж������������
	else if((cmd=='u'||cmd=='U')&&ip->protc!=17)
		return 0;
	else if(cmd=='a'||cmd=='A')
	{	
		printf("FROM:%s,",inet_ntoa(test1.sin_addr));
		printf("TO:%s\n",inet_ntoa(test2.sin_addr));
		switch(ip->protc)
		{
// 			case 1:printf("Proto ICMP,");break; 
// 			case 2:printf("Proto IGMP,");break;
 			case 6:printf("Proto TCP,");break;
// 			case 8:printf("Proto EGP,");break;
// 			case 9:printf("Proto IGP,");break;
// 			case 17:printf("Proto UDP,");break;
// 			case 41:printf("Proto IPv6,");break;
// 			case 89:printf("Proto OSPF,");break;
// 			default:printf("Proto error,");break;
		}
		if(ip->protc==6)
		{
			printf("FROM TCPPORT:%d,TO TCPPORT:%d,SEQ:%d,ACK:%d\n",ntohs(tcp->sourceport),ntohs(tcp->destport),ntohl(tcp->seq),ntohl(tcp->ack));
			printf("FLAGS:");
			if(tcp->flags&0x20)
				printf("URG ");
			if(tcp->flags&0x10)
				printf("ACK ");
			if(tcp->flags&0x8)                   //��TCP��������־λ
				printf("PSH ");
			if(tcp->flags&0x4)
				printf("RST ");
			if(tcp->flags&0x2)
				printf("SYN ");
			if(tcp->flags&0x1)
				printf("FIN ");
			printf("data:%s\n",datat);
		}		
		else if(ip->protc==17)
		{
			//printf("FROM UDPPORT:%d,TO UDPPORT:%d,\nDATA:%s",ntohs(udp->sourceport),ntohs(udp->destport),datau);
		}
		//printf("TTL:%d\n",ip->ttl);
		printf("\n");
	}		
		return 0;
}

int main()
{
	WSADATA ws;
	long lresult;
	SOCKET sock;
	struct sockaddr_in myaddress;					//��������������
	struct hostent *host;
	char name[100],command,buffer[65535];
    int err1,err2,err3;
        
	lresult=WSAStartup(MAKEWORD(2,2),&ws);
	if(lresult<0)
		printf("error!");
	printf("Please enter Packet's proto(a(ALL),u(UDP),t(TCP)):");
	scanf("%c",&command);
	myaddress.sin_family=AF_INET;
	myaddress.sin_port=htons(RECVPORT);             //��ʼ��
	gethostname(name,sizeof(name));
	host=gethostbyname(name);
	memcpy(&myaddress.sin_addr,host->h_addr_list[0],host->h_length);
    
	sock=socket(AF_INET,SOCK_RAW,IPPROTO_IP);
	err2=bind(sock,(PSOCKADDR)&myaddress,sizeof(myaddress));   //�󶨶˿�
	if(err2<0)
	{
		printf("BIND ERROR!");
		exit(1);	
	}
	DWORD inbuffer=1;
	DWORD outbuffer[10];
	DWORD returned=0;
	err1=WSAIoctl(sock,SIO_RCVALL,&inbuffer,sizeof(inbuffer),&outbuffer,sizeof(outbuffer),&returned,NULL,NULL);
	if(err1<0)
	{
		printf("IO OPTION SET ERROR!");						//���ö˿�Ϊ�������а�ģʽ
		exit(1);	
	}	
	for(;;)
	{
		memset(buffer,0,sizeof(buffer));//��ս��ջ�����
		err3=recv(sock,buffer,sizeof(buffer),0);    //�Ӱ�
		if(err3<0)
		{
			printf("RECEIVE ERROR!");
			exit(1);	
		}
		solve(buffer,command);          //�������������
	}	
	return 0;
}