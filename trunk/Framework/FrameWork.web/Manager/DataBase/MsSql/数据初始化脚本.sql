--Ӧ������Start
SET IDENTITY_INSERT [sys_Applications] ON
insert sys_Applications(ApplicationID,A_AppName,A_AppDescription,A_AppUrl) values(	1	,	N'����ģ��'	,	N'����ģ��ɲ���'	,	'http://framework.web'	)
SET IDENTITY_INSERT [sys_Applications] OFF
--Ӧ������End
---ϵͳģ���ʼ��Start
SET IDENTITY_INSERT [sys_Module] ON
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	1	,	1	,	0	,	'S00'	,	N'ϵͳӦ��'	,	NULL	,	'0000'	,	1	,	0	)
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	2	,	1	,	1	,	'S00M00'	,	N'Ӧ���б����'	,	N'Module/FrameWork/SystemApp/AppManager/list.aspx'	,	'0001'	,	1	,	0	)
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	4	,	1	,	1	,	'S00M01'	,	N'�������Ϲ���'	,	N'Module/FrameWork/SystemApp/GroupManager/Frame.aspx'	,	'0003'	,	1	,	0	)
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	5	,	1	,	1	,	'S00M02'	,	N'��ɫ���Ϲ���'	,	N'Module/FrameWork/SystemApp/RoleManager/RoleList.aspx'	,	'0004'	,	1	,	0	)
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	6	,	1	,	1	,	'S00M03'	,	N'�û����Ϲ���'	,	N'Module/FrameWork/SystemApp/UserManager/default.aspx'	,	'0005'	,	1	,	0	)
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	7	,	1	,	1	,	'S00M04'	,	N'Ӧ���ֶ��趨'	,	N'Module/FrameWork/SystemApp/FieldManager/default.aspx'	,	'0006'	,	1	,	0	)
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	8	,	1	,	1	,	'S00M05'	,	N'�¼���־����'	,	N'Module/FrameWork/SystemApp/EventManager/default.aspx'	,	'0007'	,	1	,	0	)
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	9	,	1	,	1	,	'S00M06'	,	N'�����û��б�'	,	N'Module/FrameWork/SystemApp/OnlineUserManager/default.aspx'	,	'0008'	,	1	,	0	)
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	26	,	1	,	1	,	'S00M07'	,	N'Ӧ��ģ�����'	,	N'Module/FrameWork/SystemApp/ModuleManager/list.aspx'	,	'0002'	,	1	,	0	)
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	27	,	1	,	0	,	'S01'	,	N'ϵͳά��'	,	N''	,	'0100'	,	1	,	0	)
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	28	,	1	,	27	,	'S01M00'	,	N'ϵͳ����״̬'	,	N'Module/FrameWork/SystemMaintenance/SystemState/default.aspx'	,	'0101'	,	1	,	0	)
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	29	,	1	,	27	,	'S01M01'	,	N'ϵͳ������־'	,	N'Module/FrameWork/SystemMaintenance/SystemErrorLog/default.aspx'	,	'0102'	,	1	,	0	)
insert sys_module(ModuleID,M_ApplicationID,M_ParentID,M_PageCode,M_CName,M_Directory,M_OrderLevel,M_IsSystem,M_Close) values(	30	,	1	,	27	,	'S01M02'	,	N'ϵͳ��������'	,	N'Module/FrameWork/SystemMaintenance/SystemConfig/default.aspx'	,	'0103'	,	1	,	0	)
SET IDENTITY_INSERT [sys_Module] OFF
---ϵͳģ���ʼ��End
--ϵͳ����Ա���� Start---
SET IDENTITY_INSERT [sys_User] ON
insert sys_User(UserID,U_LoginName,U_Password,U_CName,U_EName,U_GroupID,U_Email,U_Type,U_Status,U_Licence,U_Mac,U_Remark,U_IDCard,U_Sex,U_BirthDay,U_MobileNo,U_UserNO,U_WorkStartDate,U_WorkEndDate,U_CompanyMail,U_Title,U_Extension,U_HomeTel,U_PhotoUrl,U_DateTime,U_LastIP,U_LastDateTime,U_ExtendField) values(	1	,	N'admin'	,	'21232F297A57A5A743894A0E4A801FC3'	,	N'����Ա'	,	''	,	0	,	''	,	0	,	0	,	''	,	''	,	N''	,	''	,	0	,	'2007-06-23 00:00:00.000'	,	''	,	''	,	'2007-06-23 00:00:00.000'	,	'2007-06-23 15:32:19.263'	,	''	,	17	,	''	,	''	,	N''	,	'2007-06-23 15:32:19.263'	,	''	,	'2007-06-23 15:32:19.263'	,'1,10')
SET IDENTITY_INSERT [sys_User] OFF
--ϵͳ����Ա���� End--
--Ӧ���ֶ�Start
SET IDENTITY_INSERT [sys_Field] ON
insert sys_Field(FieldID,F_Key,F_CName,F_Remark) values(	2	,	'Title'	,	N'ְ��'	,	N'�û�ְ���б�'	)
SET IDENTITY_INSERT [sys_Field] OFF
SET IDENTITY_INSERT [sys_FieldValue] ON
insert sys_FieldValue(ValueID,V_F_Key,V_Text,V_ShowOrder) values(	5	,	'title'	,	N'��ͨԱ��'	,	5	)
insert sys_FieldValue(ValueID,V_F_Key,V_Text,V_ShowOrder) values(	16	,	'Title'	,	N'ְҵԱ��'	,	3	)
insert sys_FieldValue(ValueID,V_F_Key,V_Text,V_ShowOrder) values(	17	,	'Title'	,	N'�߼�����Ա'	,	2	)
insert sys_FieldValue(ValueID,V_F_Key,V_Text,V_ShowOrder) values(	18	,	'Title'	,	N'������Ա��'	,	4	)
insert sys_FieldValue(ValueID,V_F_Key,V_Text,V_ShowOrder) values(	19	,	'Title'	,	N'����Ա��'	,	1	)
SET IDENTITY_INSERT [sys_FieldValue] OFF
--Ӧ���ֶ�End
