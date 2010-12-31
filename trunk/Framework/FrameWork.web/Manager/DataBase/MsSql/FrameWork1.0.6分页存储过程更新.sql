
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

