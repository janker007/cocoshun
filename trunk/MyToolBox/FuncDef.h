// FuncDef.h: interface for the FuncDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCDEF_H__D2FC073C_F1DC_4F80_BA13_69C6FE53C859__INCLUDED_)
#define AFX_FUNCDEF_H__D2FC073C_F1DC_4F80_BA13_69C6FE53C859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/************************************************************************/
/*  ע����������                                                      */
/************************************************************************/
//��������
enum OPERATION_TYPE
{
    Query,		//��ѯ
    Write,		//д����
    Remove		//ɾ������
};

// ֵ����
enum VALUE_TYPE
{
    DW,
    STRING
};

// �ؼ�����
enum CTRL_TYPE
{
    CHECKBOX,
    BUTTON
};

//��������
struct OPER_PARAM
{
    HKEY Root;
    LPCTSTR Path;
    LPCTSTR Key;
    VALUE_TYPE ValueType;
    DWORD dwValue;
    LPCTSTR strValue;
};

struct REG_OPERATION
{
    OPERATION_TYPE OperType;
    OPER_PARAM OperParam;
};

struct CTRL_OPERATION
{
    UINT CtrlID;
    CTRL_TYPE CtrlType;
    REG_OPERATION Action;	    //����
    REG_OPERATION Revert;	    //�ָ�����
    REG_OPERATION Query;	    //��ѯ����
};

enum CRUD
{
    ACTION,
    REVERT,
    GETVALUE
};

#endif // !defined(AFX_FUNCDEF_H__D2FC073C_F1DC_4F80_BA13_69C6FE53C859__INCLUDED_)
