﻿<%@ Page Language="C#" MasterPageFile="~/Manager/MasterPage/PageTemplate.Master" AutoEventWireup="true" CodeBehind="moduleManager.aspx.cs" Inherits="FrameWork.web.Module.FrameWork.ModuleManager.moduleManager"  %>
<asp:Content ID="Content1" ContentPlaceHolderID="PageBody" runat="server">
    <FrameWorkWebControls:HeadMenuWebControls ID="HeadMenuWebControls1" runat="server"
        HeadTitleTxt="应用模块管理">
        <FrameWorkWebControls:HeadMenuButtonItem ButtonIcon="list.gif" ButtonName="应用列表"
            ButtonPopedom="List" ButtonUrl="list.aspx" ButtonUrlType="Href" ButtonVisible="True" />
    </FrameWorkWebControls:HeadMenuWebControls>
    <FrameWorkWebControls:TabOptionWebControls ID="TabOptionWebControls1" runat="server">
        <FrameWorkWebControls:TabOptionItem ID="TabOptionItem1" runat="server">
            <table width="100%" border="0" cellspacing="1" cellpadding="3" align="center">
		    <tr>
		        <td class="table_title" colspan="2">
		            <asp:Label ID="Title_Txt" runat="server"></asp:Label>
		        </td>
		    </tr>
		    <tr id="TopTr" runat="server">
			    <td class="table_body">
                    <p align="left">
                        所属应用程序</p>
                    </td>
			    <td class="table_none">
                    <asp:Label ID="M_ApplicationID_Txt" runat="server"></asp:Label></td>
		    </tr>	
                <tr runat="server">
                    <td class="table_body">
                        父级模块</td>
                    <td class="table_none">
                        <asp:Label ID="M_ParentID_Txt" runat="server"></asp:Label></td>
                </tr>
                <tr runat="server">
                    <td class="table_body" style="height: 25px">
                        模块编码</td>
                    <td class="table_none" style="height: 25px">
                        <asp:Label ID="M_PageCode_Txt" runat="server"></asp:Label>
                        <asp:TextBox ID="M_PageCode" runat="server" CssClass="text_input" title="请输入模块编码~6:!"></asp:TextBox></td>
                </tr>
                <tr runat="server">
                    <td class="table_body">
                        模块名称</td>
                    <td class="table_none">
                        <asp:Label ID="M_CName_Txt" runat="server"></asp:Label>
                        <asp:TextBox ID="M_CName" runat="server" CssClass="text_input" title="请输入模块名称~50:!"></asp:TextBox></td>
                </tr>
                <tr runat="server">
                    <td class="table_body" style="height: 25px">
                        模块地址</td>
                    <td class="table_none" style="height: 25px">
                        <asp:Label ID="M_Directory_Txt" runat="server"></asp:Label>
                        <asp:TextBox ID="M_Directory" runat="server" CssClass="text_input" title="请输入模块地址~255:" Columns="50"></asp:TextBox></td>
                </tr>
                <tr runat="server">
                    <td class="table_body">
                        是否为系统模块</td>
                    <td class="table_none">
                        <asp:Label ID="M_IsSystem_Txt" runat="server"></asp:Label>
                        <asp:DropDownList ID="M_IsSystem" disabled runat="server">
                        <asp:ListItem Value="0">否</asp:ListItem>
                        <asp:ListItem Value="1">是</asp:ListItem>
                        </asp:DropDownList>(注:系统模块无法修改删除)</td>
                </tr>
                <tr runat="server">
                    <td class="table_body">
                        是否关闭</td>
                    <td class="table_none">
                        <asp:Label ID="M_Close_Txt" runat="server"></asp:Label>
                        <asp:DropDownList ID="M_Close" runat="server">
                        <asp:ListItem Value="0">否</asp:ListItem>
                        <asp:ListItem Value="1">是</asp:ListItem>
                        </asp:DropDownList></td>
                </tr>
		    <tr id="SubmitTr" runat="server"><td colspan="2" align="right">
            <asp:Button ID="Button1" runat="server" CssClass="button_bak" Text="确定" OnClick="Button1_Click" />
            <input id="Reset1" class="button_bak" type="reset" value="重填" />&nbsp;
		    </td>
		    </tr>	
		  

		  </table>
        </FrameWorkWebControls:TabOptionItem>
        <FrameWorkWebControls:TabOptionItem ID="TabOptionItem2" runat="server" Tab_Name="模块列表">
        
            <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="false">
                <Columns>
                    <asp:HyperLinkField DataNavigateUrlFields="M_ApplicationID,ModuleID" DataNavigateUrlFormatString="ModuleManager.aspx?S_ID={0}&ModuleID={1}"
                        DataTextField="M_CName" HeaderText="模块名称" />
                    <asp:BoundField DataField="M_PageCode" HeaderText="模块编码" />
                    <asp:BoundField DataField="M_Directory" HeaderText="模块文件地址" />
                    <asp:TemplateField HeaderText="系统模块">
                        <ItemTemplate>
                            <%#GetStatus((int)Eval("M_IsSystem"))%>
                        </ItemTemplate>
                    </asp:TemplateField>
                    <asp:TemplateField HeaderText="关闭">
                        <ItemTemplate>
                            <%#GetStatus((int)Eval("M_Close"))%>
                        </ItemTemplate>
                    </asp:TemplateField>                          
                </Columns>
            </asp:GridView>
        </FrameWorkWebControls:TabOptionItem>
        <FrameWorkWebControls:TabOptionItem ID="TabOptionItem3" runat="server" Tab_Name="排序模块">
          <table width="100%" border="0" cellspacing="1" cellpadding="3" align="center" >
          <tr class="table_none">
            <td align="center">
                <table >
                <tr>
                    <td><asp:ListBox ID="OrderByListItems" runat="server" SelectionMode="Multiple"></asp:ListBox></td>
                    <td>
                       	<img border="0" src="<%=Page.ResolveUrl("~/Manager/") %>images/up01.gif" OnClick="javascript:moveUpDown('up','<%=OrderByListItems_UniqueID %>');" style="cursor:pointer;">
    			        <p><img border="0" src="<%=Page.ResolveUrl("~/Manager/") %>images/down01.gif" OnClick="javascript:moveUpDown('down','<%=OrderByListItems_UniqueID %>');" style="cursor:pointer;">
                    </td>
                </tr>
                </table>
                
            </td>
          </tr>
          <tr><td align="right">
          <asp:Button ID="Button2" runat="server" CssClass="button_bak" Text="确定" OnClick="Button2_Click" />
          </td></tr>
          </table>
        </FrameWorkWebControls:TabOptionItem>
    </FrameWorkWebControls:TabOptionWebControls>
</asp:Content>
