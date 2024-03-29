﻿/********************************************************************************
     File:																
            Manager.aspx.cs                         
     Description:
            管理
     Author:									
            DDBuildTools
            http://DDBuildTools.supesoft.com
     Finish DateTime:
            2011/1/5 9:15:01
     History:
*********************************************************************************/
using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

using FrameWork.web.Manager.Module.App;
using FrameWork.web.Manager.Module.App.Components;
using FrameWork;
using FrameWork.Components;
using FrameWork.WebControls;

namespace FrameWork.web.Manager.Module.App
{
    public partial class Manager : System.Web.UI.Page
    {
        int IDX = (int)Common.sink("IDX", MethodType.Get, 4, 0, DataType.Int);
        string CMD = (string)Common.sink("CMD", MethodType.Get, 10, 1, DataType.Str);
        protected void Page_Load(object sender, EventArgs e)
        {
            FrameWorkPermission.CheckPagePermission(CMD);
            if (!Page.IsPostBack)
            {
                OnStart();
            }
        }
        
        /// <summary>
        /// 开始操作
        /// </summary>
        private void OnStart()
        {
            app_NewsEntity ut = BusinessFacadeFrameWork.app_NewsDisp(IDX);
            OnStartData(ut);
            switch (CMD)
            { 
                case "New":
                    TabOptionItem1.Tab_Name = HeadMenuWebControls1.HeadOPTxt = "增加";
                    Hidden_Disp();
                    break;
                case "List":
                    TabOptionItem1.Tab_Name = HeadMenuWebControls1.HeadOPTxt = "查看";
                    Hidden_Input();
                    ButtonOption.Visible = false;
                    AddEditButton();
                    break;
                case "Edit":
                    TabOptionItem1.Tab_Name = HeadMenuWebControls1.HeadOPTxt = "修改";
                    Hidden_Disp();
                    AddDeleteButton();
                    break;
                case "Delete":
                    ut.DataTable_Action_ = DataTable_Action.Delete;

                    //删除图片
                    removeImge(ut);
                    if (BusinessFacadeFrameWork.app_NewsInsertUpdateDelete(ut) > 0)
                    {
                        EventMessage.MessageBox(1, "删除成功", string.Format("删除ID:{0}成功!", IDX), Icon_Type.OK, Common.GetHomeBaseUrl("Default.aspx"));
                    }
                    else {
                        EventMessage.MessageBox(1, "删除失败", string.Format("删除ID:{0}失败!", IDX), Icon_Type.Error, Common.GetHomeBaseUrl("Default.aspx"));
                    }

                    break;
                default :
                    EventMessage.MessageBox(2, "不存在操作字符串!", "不存在操作字符串!", Icon_Type.Error, Common.GetHomeBaseUrl("Default.aspx"));
                    break;
            }
        }

        /// <summary>
        /// 删除图片
        /// </summary>
        private static void removeImge(app_NewsEntity ut)
        {
            if (ut.ImagePath.Length > 0)
            {
                FileUpLoadCommon.DeleteFile(string.Format("{0}{1}{2}", Common.UpLoadDir, "NewsImages/", ut.ImagePath));
                FileUpLoadCommon.DeleteFile(string.Format("{0}{1}s_{2}", Common.UpLoadDir, "NewsImages/", ut.ImagePath));
            }
        }

        /// <summary>
        /// 增加修改按钮
        /// </summary>
        private void AddEditButton()
        {
            HeadMenuButtonItem bi = new HeadMenuButtonItem();
            bi.ButtonPopedom = PopedomType.Edit;
            bi.ButtonName = "";
            bi.ButtonUrl = string.Format("?CMD=Edit&IDX={0}", IDX);
            HeadMenuWebControls1.ButtonList.Add(bi);
        }


        /// <summary>
        /// 增加删除按钮
        /// </summary>
        private void AddDeleteButton()
        {
            HeadMenuButtonItem bi = new HeadMenuButtonItem();
            bi.ButtonPopedom = PopedomType.Delete;
            bi.ButtonName = "";
            bi.ButtonUrlType = UrlType.JavaScript;
            bi.ButtonUrl = string.Format("DelData('?CMD=Delete&IDX={0}')", IDX);
            HeadMenuWebControls1.ButtonList.Add(bi);

            HeadMenuButtonItem bi1 = new HeadMenuButtonItem();
            bi1.ButtonPopedom = PopedomType.List;
            bi1.ButtonIcon = "back.gif";
            bi1.ButtonName = "返回";
            bi1.ButtonUrl = string.Format("?CMD=List&IDX={0}", IDX);
            HeadMenuWebControls1.ButtonList.Add(bi1);
        }

        /// <summary>
        /// 初始化数据
        /// </summary>
        /// <param name="ut"></param>
        private void OnStartData(app_NewsEntity ut)
        {
                Title_Input.Text = Title_Disp.Text = ut.Title.ToString();
                Author_Input.Text = Author_Disp.Text = ut.Author.ToString();

                if (ut.AddTime == null || ut.AddTime.ToString().Length == 0)
                {
                    ut.AddTime = DateTime.Now;
                }

                AddTime_Input.Text = AddTime_Disp.Text =  Common.ConvertDate(ut.AddTime);

                Content_Input.Text = Content_Disp.Text = ut.Content.ToString();


                if ((ut.ImagePath + "").Trim() != "")
                {
                    News_Image.ImageUrl = Common.BuildDownFileUrl("NewsImages/s_" + ut.ImagePath);
                    //MaxImgUrl = Common.BuildDownFileUrl("NewsImages/" + ut.U_PhotoUrl);

                }
                ImagePath_Input.Text = ImagePath_Disp.Text = ut.ImagePath.ToString();
                ImageComment_Input.Text = ImageComment_Disp.Text = ut.ImageComment.ToString();
                             
                
                ReCommand_Input.SelectedValue = Convert.ToInt32(ut.ReCommand).ToString();
                ReCommand_Disp.Text = ut.ReCommand.ToString();
                
        }

        /************************************************************************/
        /* 上传新闻图片                                                         */
        /************************************************************************/
        private string UploadPic(app_NewsEntity ut)
        {


            FileUpLoadCommon fc = new FileUpLoadCommon(Common.UpLoadDir + "NewsImages/", false);
            
            // 如果图片上传成功
            if(fc.SaveFile(ImageUpload, true))
            {
                //删除原有图片
                removeImge(ut);
            }
            return fc.newFileName;
        }

        /// <summary>
        /// 隐藏输入框
        /// </summary>
        private void Hidden_Input()
        {
            Title_Input.Visible = false;
            Author_Input.Visible = false;
            AddTime_Input.Visible = false;
            Content_Input.Visible = false;
            ImagePath_Input.Visible = false;
            ImageComment_Input.Visible = false;
            ReCommand_Input.Visible = false;
            ImageUpload.Visible = false;
        }

        /// <summary>
        /// 隐藏显示框
        /// </summary>
        private void Hidden_Disp()
        {
            Title_Disp.Visible = false;
            Author_Disp.Visible = false;
            AddTime_Disp.Visible = false;
            Content_Disp.Visible = false;
            ImagePath_Disp.Visible = false;
            ImageComment_Disp.Visible = false;
            ReCommand_Disp.Visible = false;
            News_Image.Visible = false;
        }

        /// <summary>
        /// 增加/修改事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Button1_Click(object sender, EventArgs e)
        {
        
            
            
            
                    DateTime? AddTime_Value = (DateTime?)Common.sink(AddTime_Input.UniqueID, MethodType.Post, 50, 0, DataType.Dat);
                
            
            
            
                    bool ReCommand_Value = Convert.ToBoolean(Common.sink(ReCommand_Input.UniqueID, MethodType.Post, 1, 0, DataType.Int));
                
            app_NewsEntity ut = BusinessFacadeFrameWork.app_NewsDisp(IDX);
            
            ut.Title = Title_Input.Text;
            ut.Author = Author_Input.Text;
            ut.AddTime = Convert.ToDateTime(AddTime_Input.Text);
            ut.Content = Content_Input.Text;

            string uploadPicName = UploadPic( ut);
            if (uploadPicName.Length > 0)
                ut.ImagePath = uploadPicName;
            ut.ImageComment = ImageComment_Input.Text;
            //ut.ImagePath = ImagePath_Input.Text;
            string booleanValue = ReCommand_Input.Text.Equals("1") ? "true" : "false";
            ut.ReCommand = Convert.ToBoolean(booleanValue);
            
            if (CMD == "New")
            {
                ut.DataTable_Action_ = DataTable_Action.Insert;
            }
            else if (CMD == "Edit")
            {
                ut.DataTable_Action_ = DataTable_Action.Update;
            }
            else
            {
                EventMessage.MessageBox(2, "不存在操作字符串!", "不存在操作字符串!", Icon_Type.Error, Common.GetHomeBaseUrl("Default.aspx"));
            }
            Int32 rInt = BusinessFacadeFrameWork.app_NewsInsertUpdateDelete(ut);
            if ( rInt> 0)
            {
                string OpTxt = string.Format("增加成功!(ID:{0})", rInt);
                if (ut.DataTable_Action_ == DataTable_Action.Update)
                    OpTxt = string.Format("修改成功!(ID:{0})",IDX);
                EventMessage.MessageBox(1, "操作成功", OpTxt, Icon_Type.OK, Common.GetHomeBaseUrl("Default.aspx"));
            }
            else if (rInt == -2)
            {
                removeImge(ut);
                EventMessage.MessageBox(1, "操作失败", "操作失败,存在相同的键值(用户名/数据)!", Icon_Type.Alert, Common.GetHomeBaseUrl("Default.aspx"));
            }
            else
            {
                removeImge(ut);
                EventMessage.MessageBox(1, "操作失败", string.Format("操作失败,返回值:{0}!", rInt), Icon_Type.Error, Common.GetHomeBaseUrl("Default.aspx"));
            }
        }
    }
}
