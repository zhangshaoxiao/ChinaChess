// Plate.h: interface for the CPlate class.
//
//////////////////////////////////////////////////////////////////////
#include "define.h"
#include "Move.h"
#if !defined(AFX_PLATE_H__D491B3DE_DFFD_4EED_B19A_8CADA70537C9__INCLUDED_)
#define AFX_PLATE_H__D491B3DE_DFFD_4EED_B19A_8CADA70537C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPlate  
{
public:
	CHESSMANPOS platepos[10][9];//���̸������������
	int m_ndx;     //���Ŀ�
	int m_ndy;     //���ĳ�
	int m_nPlateX; //���̵Ŀ�
	int m_nPlateY; //���̵ĳ�

	int m_nPlateLeft;//����λ����Ϣ
	int m_nPlateRight;
	int m_nPlateTop;
	int m_nPlateBottom;
public:
	CPlate();
	virtual ~CPlate();

};

#endif // !defined(AFX_PLATE_H__D491B3DE_DFFD_4EED_B19A_8CADA70537C9__INCLUDED_)
