<%@ Page Language="C#" MasterPageFile="~/Manager/MasterPage/PageTemplate.Master" AutoEventWireup="True"
    Codebehind="Manager.aspx.cs" Inherits="FrameWork.web.Manager.Module.App.Web.Module.FrameWork.web.Manager.Module.App.app_StyleShow.Manager"
    Title="�ޱ���ҳ" %>

<asp:Content ID="Content1" ContentPlaceHolderID="PageBody" runat="server">
    <FrameWorkWebControls:HeadMenuWebControls ID="HeadMenuWebControls1" runat="server"  HeadTitleTxt="">
        <FrameWorkWebControls:HeadMenuButtonItem ButtonPopedom="List" ButtonUrl="Default.aspx"
            ButtonUrlType="Href" ButtonVisible="True" ButtonName="" />
    </FrameWorkWebControls:HeadMenuWebControls>
    <FrameWorkWebControls:TabOptionWebControls ID="TabOptionWebControls1" runat="server">
        <FrameWorkWebControls:TabOptionItem ID="TabOptionItem1" runat="server" Tab_Name="�鿴/�޸�/����">
            <table width="100%" border="0" cellspacing="1" cellpadding="3" align="center">

                <tr>
                    <td class="table_body">
                        ����</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="Title_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        <asp:Label ID="Title_Disp" runat="server"></asp:Label></td>
                </tr>

                <tr>
                    <td class="table_body">
                        ͼƬ����ʱ��</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="AddTime_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        <asp:Label ID="AddTime_Disp" runat="server"></asp:Label></td>
                </tr>

                <tr>
                    <td class="table_body">
                        ����</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="Author_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        <asp:Label ID="Author_Disp" runat="server"></asp:Label></td>
                </tr>

                <tr>
                    <td class="table_body">
                        ͼƬ·��</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="ImagePath_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        <asp:Label ID="ImagePath_Disp" runat="server"></asp:Label></td>
                </tr>

                <tr>
                    <td class="table_body">
                        ͼƬע��</td>
                    <td class="table_none">
                     
                        <asp:TextBox ID="Comment_Input"  runat="server" CssClass="text_input"></asp:TextBox>
                    
                        <asp:Label ID="Comment_Disp" runat="server"></asp:Label></td>
                </tr>
                              
                <tr id="ButtonOption" runat="server">
                    <td align="right" colspan="2">
                        <asp:Button ID="Button1" runat="server" CssClass="button_bak" Text="ȷ��" OnClick="Button1_Click" />
                        <input id="Reset1" class="button_bak" type="reset" value="����" />
                    </td>
                </tr>
            </table>
        </FrameWorkWebControls:TabOptionItem>
    </FrameWorkWebControls:TabOptionWebControls>
</asp:Content>
