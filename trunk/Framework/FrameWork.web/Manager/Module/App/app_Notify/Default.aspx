<%@ Page Language="C#" MasterPageFile="~/Manager/MasterPage/PageTemplate.Master" AutoEventWireup="True"
    Codebehind="Default.aspx.cs" Inherits="FrameWork.web.Manager.Module.App.app_Notify.Default"
    Title="�ޱ���ҳ" %>

<asp:Content ID="Content1" ContentPlaceHolderID="PageBody" runat="server">
    <FrameWorkWebControls:HeadMenuWebControls ID="HeadMenuWebControls1" runat="server"
         HeadOPTxt="�б�" HeadTitleTxt="">
        <FrameWorkWebControls:HeadMenuButtonItem ButtonPopedom="New" ButtonUrl="Manager.aspx?CMD=New"
            ButtonUrlType="Href" ButtonVisible="True" ButtonName="" />
    </FrameWorkWebControls:HeadMenuWebControls>
    <FrameWorkWebControls:TabOptionWebControls ID="TabOptionWebControls1" runat="server">
        <FrameWorkWebControls:TabOptionItem ID="TabOptionItem1" runat="server" Tab_Name="�б�">
            <asp:GridView ID="GridView1" runat="server" OnSorting="GridView1_Sorting" OnRowCreated="GridView1_RowCreated" >
                <Columns>
                    <asp:TemplateField SortExpression="ID" HeaderText="���"> 
                        <ItemTemplate>
                        <a href="Manager.aspx?IDX=<%#Eval("ID")%>&CMD=List"><%# (this.AspNetPager1.CurrentPageIndex - 1) * this.AspNetPager1.PageSize + Container.DataItemIndex + 1%></a>
                        </ItemTemplate>
                        <ItemStyle Wrap="True" />  
                        <HeaderStyle Wrap="False" />    
                    </asp:TemplateField>
                    <asp:BoundField HeaderText="����" SortExpression="Title" DataField="Title" />
                    <asp:BoundField HeaderText="֪ͨ����" SortExpression="Notifier" DataField="Notifier" />
                    <asp:BoundField HeaderText="֪ͨʱ��" SortExpression="AddTime" DataField="AddTime" />
                    <asp:BoundField HeaderText="֪ͨ����" SortExpression="Content" DataField="Content" />
                </Columns>
            </asp:GridView>
            <FrameWorkWebControls:AspNetPager ID="AspNetPager1" runat="server" OnPageChanged="AspNetPager1_PageChanged">
            </FrameWorkWebControls:AspNetPager>
            <asp:Button ID="Button2" Visible="false" CssClass="button_bak" runat="server" Text="ɾ��" OnClientClick="return deleteop();" OnClick="Button2_Click" />
        </FrameWorkWebControls:TabOptionItem>
        <FrameWorkWebControls:TabOptionItem ID="TabOptionItem2" runat="server" Tab_Name="��ѯ">
            <table width="100%" border="0" cellspacing="1" cellpadding="3" align="center">
                <tr>
                    <td class="table_body">
                        ����</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="Title_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        </td>
                </tr>
                <tr>
                    <td class="table_body">
                        ֪ͨ����</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="Notifier_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        </td>
                </tr>
                <tr>
                    <td class="table_body">
                        ֪ͨʱ��</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="AddTime_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        </td>
                </tr>
                <tr>
                    <td class="table_body">
                        ֪ͨ����</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="Content_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        </td>
                </tr>
                <tr>
                    <td colspan="4" align="right">
                        <asp:Button ID="Button1" runat="server" CssClass="button_bak" Text="��ѯ" OnClick="Button1_Click" /></td>
                </tr>
            </table>
        </FrameWorkWebControls:TabOptionItem>
    </FrameWorkWebControls:TabOptionWebControls>

<script language="javascript" type="text/javascript">
<!--

function SelectAll()
{
   var e=document.getElementsByTagName("input");
   var IsTrue;
   if(document.getElementById("CheckboxAll").value=="0")
�� {
���� IsTrue=true;
���� document.getElementById("CheckboxAll").value="1"
�� }
�� else
�� {
����IsTrue=false;
����document.getElementById("CheckboxAll").value="0"
����}
����
��for(var i=0;i<e.length;i++)
��{
����if (e[i].type=="checkbox")
����{
����   e[i].checked=IsTrue;
����}
��}
}
function deleteop()
{
    var checkok = false;
    var e=document.getElementsByTagName("input");
    for(var i=0;i<e.length;i++)
��  {
��     if (e[i].type=="checkbox")
����     {
����         if (e[i].checked==true)
����         {
����             checkok = true;
����             break;����             
����         }
����     }  
��  }
��  if (checkok) 
        return confirm('ɾ���󲻿ɻָ�,ȷ��Ҫ����ɾ��ѡ�м�¼��');
    else
    {
        
        alert("��ѡ��Ҫɾ���ļ�¼!");
        return false;
    }
}
// -->
    </script>

</asp:Content>
