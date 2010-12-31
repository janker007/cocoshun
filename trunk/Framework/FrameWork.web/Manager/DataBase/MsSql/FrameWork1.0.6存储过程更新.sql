
---��ҳ�洢���̸���,�����ֶ������� 
---by Michael.li 2008/5/30

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO





/*********************************************************************************
*      Copyright (C) 2005 141421.com,All Rights Reserved			 *
*      Function:  SuperPaging			                                 *
*      Description:                                                              *
*             ��ǿͨ�÷�ҳ�洢����						 *
*      Author:                                                                   *
*             ��ѧ��(Ryan)                                                       *
*             lifergb@hotmail.com                                                *
*             http://www.141421.com                                              *
*      Finish DateTime:                                                          *
*             2005��9��24��                                                      *
*      History:									 *
*             2006/4/21 Edit By Michael Li                                       *         
*	   Example:								 *
*	          SuperPaging @TableName='����',@Orderfld='��������'              *           
*********************************************************************************/
ALTER  PROCEDURE SupesoftPage
(
	@TableName		nvarchar(50),			-- ����
	@ReturnFields	nvarchar(2000) = '*',	-- ��Ҫ���ص��� 
	@PageSize		int = 10,				-- ÿҳ��¼��
	@PageIndex		int = 1,				-- ��ǰҳ��
	@Where			nvarchar(2000) = '',		-- ��ѯ����
	@Orderfld		nvarchar(2000),			-- �����ֶ��� ���ΪΨһ����
	@OrderType		int = 1					-- �������� 1:���� ����Ϊ����
	
)
AS
    DECLARE @TotalRecord int
	DECLARE @TotalPage int
	DECLARE @CurrentPageSize int
    DECLARE @TotalRecordForPageIndex int
    DECLARE @OrderBy nvarchar(255)
    DECLARE @CutOrderBy nvarchar(255)
	
	if @OrderType = 1
		BEGIN
			set @OrderBy = ' Order by ' + REPLACE(@Orderfld,',',' desc,') + ' desc '
			set @CutOrderBy = ' Order by '+ REPLACE(@Orderfld,',',' asc,') + ' asc '
		END
	else
		BEGIN
			set @OrderBy = ' Order by ' +  REPLACE(@Orderfld,',',' asc,') + ' asc '
			set @CutOrderBy = ' Order by '+ REPLACE(@Orderfld,',',' desc,') + ' desc '			
		END
	
	
        -- ��¼����
	declare @countSql nvarchar(4000)  
	set @countSql='SELECT @TotalRecord=Count(*) From '+@TableName+' '+@Where
	execute sp_executesql @countSql,N'@TotalRecord int out',@TotalRecord out
	
	SET @TotalPage=(@TotalRecord-1)/@PageSize+1
	SET @CurrentPageSize=@PageSize
        IF(@TotalPage=@PageIndex)
	BEGIN
		SET @CurrentPageSize=@TotalRecord%@PageSize
		IF(@CurrentPageSize=0)
			SET @CurrentPageSize=@PageSize
	END
	-- ���ؼ�¼
	set @TotalRecordForPageIndex=@PageIndex*@PageSize
	exec('SELECT * FROM
		(SELECT TOP '+@CurrentPageSize+' * FROM
			(SELECT TOP '+@TotalRecordForPageIndex+' '+@ReturnFields+'
			FROM '+@TableName+' '+@Where+' '+@OrderBy+') TB2
		'+@CutOrderBy+') TB3
              '+@OrderBy)
	-- ������ҳ�����ܼ�¼��
	SELECT @TotalPage as PageCount,@TotalRecord as RecordCount




GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

--����Ӧ���ֶ�ֵ�洢����

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[sys_FieldValueInsertUpdateDelete]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
drop procedure [dbo].[sys_FieldValueInsertUpdateDelete]
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO






-- ��������ɾ��
CREATE  PROCEDURE sys_FieldValueInsertUpdateDelete
(	

	@ValueID	 int = 0,	-- ����ID��
	@V_F_Key	 varchar(50) = '',	-- ��sys_Field����F_Key�ֶι���
	@V_Text	 nvarchar(100) = '',	-- ����˵��
	@V_Code	 nvarchar(100) = '',	-- ����
	@V_ShowOrder	 int = 0,	-- ͬ����ʾ˳��
	@DB_Option_Action_  nvarchar(20) = ''		-- �������� Insert:���� Update:�޸� Delete:ɾ�� 
)
AS
	DECLARE @ReturnValue int -- ���ز������
	
	SET @ReturnValue = -1
	
	-- ����
	IF (@DB_Option_Action_='Insert')
	BEGIN
		INSERT INTO sys_FieldValue( 
			V_F_Key,
			V_Text,
			V_Code,
			V_ShowOrder
		) VALUES (	
			@V_F_Key,
			@V_Text,
			@V_Code,
			@V_ShowOrder
		)
		SET @ReturnValue = @@ROWCOUNT
	END
	
	-- ����
	IF (@DB_Option_Action_='Update')
	BEGIN
		UPDATE sys_FieldValue SET	
			V_F_Key = @V_F_Key,
			V_Text = @V_Text,
			V_Code = @V_Code,
			V_ShowOrder = @V_ShowOrder
		WHERE (ValueID = @ValueID)
		
		SET @ReturnValue = @@ROWCOUNT
	END
	
	-- ɾ��
	IF (@DB_Option_Action_='Delete')
	BEGIN
		DELETE sys_FieldValue	WHERE (ValueID = @ValueID)
		SET @ReturnValue = @@ROWCOUNT
  	END

SELECT @ReturnValue








GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO



