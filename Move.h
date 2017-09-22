// Move.h: interface for the CMove class.
//
//////////////////////////////////////////////////////////////////////
#include "define.h"

#if !defined(AFX_MOVE_H__AB33FE47_EE94_4B0E_9037_F527ED174E23__INCLUDED_)
#define AFX_MOVE_H__AB33FE47_EE94_4B0E_9037_F527ED174E23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMove  
{
public:
	StepStack S;
	int m_pickstoneID;
public:
 	CMove();
	virtual ~CMove();
	BOOL MayMove(CHESSMANPOS mark[10][9],const int xfrom,const int yfrom,const int xto,const int yto,bool ischangestone);//判断是否能走
	void InitStack(StepStack &S);
	void PutStack(StepNode item);//将棋步压栈
	StepNode PushStack();		 //回棋时要用的
	void DeleteStack(StepStack &S);//清除栈
	StepNode operator =(StepNode &node);
};

#endif // !defined(AFX_MOVE_H__AB33FE47_EE94_4B0E_9037_F527ED174E23__INCLUDED_)
