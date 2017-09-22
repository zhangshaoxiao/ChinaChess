// Move.cpp: implementation of the CMove class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Chess.h"
#include "Move.h"
#include "define.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMove::CMove()
{
	m_pickstoneID=NOCHESS;
	S.stack=NULL;
	S.maxsize=0;
	S.top=-1;
	InitStack(S);


}

CMove::~CMove()
{
	DeleteStack(S);
}
StepNode CMove::operator =(StepNode &node)
{
	StepNode temp;
	temp.from=node.from;
	temp.to=node.to;
	temp.movestoneID=node.movestoneID;
	temp.movestoneno=node.movestoneno;
	temp.bekillstonepos=node.bekillstonepos;
	temp.bekillstoneID=node.bekillstoneID;
	temp.bekillstoneno=node.bekillstoneno;
	return temp;
}
void CMove::InitStack(StepStack &S)
{
	if(S.stack==NULL)
	{
		S.stack=new StepNode[75];
		S.maxsize=75;
		S.top=-1;
	}	
}
void CMove::PutStack(StepNode item)
{
	if(S.top==S.maxsize-1)
	{
		StepNode* p=new StepNode[2*S.maxsize+1];
		for(int i=0;i<S.top;i++)
			p[i]=S.stack[i];
		delete []S.stack;
		S.stack=p;
		S.maxsize=S.maxsize*2+1;
	}
	S.stack[++S.top]=item;

}
StepNode CMove::PushStack()
{
	if(S.top!=-1)
	{
		return S.stack[S.top--];
	}

}
void CMove::DeleteStack(StepStack &S)
{
	if(S.stack!=NULL)
	{
		delete[]S.stack;
		S.stack=NULL;
		S.top=-1;
		S.maxsize=-1;
	}
}

BOOL CMove::MayMove(CHESSMANPOS mark[10][9],const int xfrom,const int yfrom,const int xto,const int yto,bool ischangestone)
{
	if(xfrom==xto&&yfrom==yto) 
		return FALSE;
	int i=0;
	int j=0;
	int TargetID;
	int MovechessID;
	TargetID=mark[yto][xto].chessID;
	if(m_pickstoneID!=NOCHESS)
	{
		MovechessID=m_pickstoneID;
	}
	else 
	{
		MovechessID=mark[yfrom][xfrom].chessID;
	}
	if(IsSameSide(MovechessID,TargetID))//���ܳ��Լ�����,��define.h ����ĺ�
		return FALSE;
	switch(MovechessID)
	{
	case B_K:
		if(!ischangestone)	 //û�н���������ɫ
		{
			if(TargetID==R_K)//�Ͻ�����
			{
				if(xfrom!=xto)
					return FALSE;
				for(i=yfrom+1;i<yto;i++)
					if(mark[i][xfrom].chessID!=NOCHESS)	
						return FALSE;
			}
			else           //����������ɫ
			{
				if(xto<3||xto>5||yto<0||yto>2)//�ڹ�����
				   return FALSE;
				if((abs(xto-xfrom)+abs(yto-yfrom))>1)//ֻ��һ��
					return FALSE;
			}
		}
		else
		{
			if(TargetID==B_K)
			{ 
				if(xfrom!=xto)
					return FALSE;
				for(i=yfrom-1;i>yto;i--)
					if(mark[i][xfrom].chessID!=NOCHESS)
						return FALSE;
			}
			else
			{
				if(xto<3||xto>5||yto<7||yto>9)
					return FALSE;
				if((abs(xto-xfrom)+abs(yto-yfrom))>1)
					return FALSE;
			}
		}
		break;
	case R_K://��˧
		if(!ischangestone)
		{
			if(TargetID==B_K)
			{ 
				if(xfrom!=xto)
					return FALSE;
				for(i=yfrom-1;i>yto;i--)
					if(mark[i][xfrom].chessID!=NOCHESS)
						return FALSE;
			}
			else
			{
				if(xto<3||xto>5||yto<7||yto>9)
					return FALSE;
				if((abs(xto-xfrom)+abs(yto-yfrom))>1)
					return FALSE;
			}
		}
		else
		{
			if(TargetID==R_K)//�Ͻ�����
			{
				if(xfrom!=xto)
					return FALSE;
				for(i=yfrom+1;i<yto;i++)
					if(mark[i][xfrom].chessID!=NOCHESS)	
						return FALSE;
			}
			else
			{
				if(xto<3||xto>5||yto<0||yto>2)//�ڹ�����
				   return FALSE;
				if((abs(xto-xfrom)+abs(yto-yfrom))>1)//ֻ��һ��
					return FALSE;
			}
		}
		break;
	case B_S://��ʿ
		if(!ischangestone)
		{
			if(xto<3||xto>5||yto<0||yto>2) 
				return FALSE;
			if(abs(xto-xfrom)!=1||abs(yto-yfrom)!=1)
				return FALSE;
		}
		else
		{
			if(xto<3||xto>5||yto<7||yto>9)
				return FALSE;
			if(abs(xto-xfrom)!=1||abs(yto-yfrom)!=1)
				return FALSE;
		}
		break;
	case R_S:
		if(!ischangestone)
		{
			if(xto<3||xto>5||yto<7||yto>9)
				return FALSE;
			if(abs(xto-xfrom)!=1||abs(yto-yfrom)!=1)
				return FALSE;
		}
		else
		{
			if(xto<3||xto>5||yto<0||yto>2) 
				return FALSE;
			if(abs(xto-xfrom)!=1||abs(yto-yfrom)!=1)
				return FALSE;
		}
		break;
	case B_X://����
		if(!ischangestone)
		{
			if(yto>4||yto<0)
				return FALSE;
			if(abs(xto-xfrom)!=2||abs(yto-yfrom)!=2)
				return FALSE;
			if(mark[(yfrom+yto)/2][(xfrom+xto)/2].chessID!=NOCHESS)
				return FALSE;
		}
		else
		{
			if(yto<5||yto>9)
				return FALSE;
			if(abs(xto-xfrom)!=2||abs(yto-yfrom)!=2)
				return FALSE;
			if(mark[(yfrom+yto)/2][(xfrom+xto)/2].chessID!=NOCHESS)
				return FALSE;
		}
		break;
	case R_X:
		if(!ischangestone)
		{
			if(yto<5||yto>9)
				return FALSE;
			if(abs(xto-xfrom)!=2||abs(yto-yfrom)!=2)
				return FALSE;
			if(mark[(yfrom+yto)/2][(xfrom+xto)/2].chessID!=NOCHESS)
				return FALSE;
		}
		else
		{
			if(yto>4||yto<0)
				return FALSE;
			if(abs(xto-xfrom)!=2||abs(yto-yfrom)!=2)
				return FALSE;
			if(mark[(yfrom+yto)/2][(xfrom+xto)/2].chessID!=NOCHESS)
				return FALSE;
		}
		break;
	case B_M://��
	case R_M:
		if((abs(xfrom-xto)!=1||abs(yfrom-yto)!=2)&&
			(abs(xfrom-xto)!=2||abs(yfrom-yto)!=1))
			return FALSE;
		//�����
		if(xto-xfrom==2)
		{
			i=xfrom+1;
			j=yfrom;
		}
		else if(xfrom-xto==2)
		{
			i=xfrom-1;
			j=yfrom;
		}
		else if(yto-yfrom==2)
		{
			i=xfrom;
			j=yfrom+1;
		}
		else if(yfrom-yto==2)
		{
			i=xfrom;
			j=yfrom-1;
		}
		if(mark[j][i].chessID!=NOCHESS)
			return FALSE;
		break;
	case B_C://��
	case R_C:
		if((xfrom!=xto)&&(yfrom!=yto))
			return FALSE;
		if(xfrom==xto)//ͬһ����
		{
			if(yfrom<yto)
			{
				for(i=yfrom+1;i<yto;i++)
					if(mark[i][xfrom].chessID!=NOCHESS)
						return FALSE;
			}
			else
			{
				for(i=yfrom-1;i>yto;i--)
					if(mark[i][xfrom].chessID!=NOCHESS)
						return FALSE;
			}
		}
		else if(yfrom==yto)//ͬһ����
		{
			if(xfrom<xto)
			{
				for(i=xfrom+1;i<xto;i++)
					if(mark[yfrom][i].chessID!=NOCHESS)
						return FALSE;
			}
			else
			{
				for(i=xfrom-1;i>xto;i--)
					if(mark[yfrom][i].chessID!=NOCHESS)
						return FALSE;
			}
		}
		break;
	case B_B://�ڱ�
		if(!ischangestone)
		{
			if(yto<=4)
			{
				if(xto%2!=0)
					return FALSE;
			}
			//ֻ��һ��
			if(abs(xto-xfrom)+abs(yto-yfrom)>1)
					return FALSE;
			//���ܻ�ͷ
			if(yto<yfrom)
				return FALSE;
		}
		else
		{
			if(yto>=5)
			{
				if(xto%2!=0)
					return FALSE;
			}
			if(abs(xto-xfrom)+abs(yto-yfrom)>1)
					return FALSE;

			if(yto>yfrom)
				return FALSE;	
		}
		break;
	case R_B://���
		if(!ischangestone)
		{
			if(yto>=5)
			{
				if(xto%2!=0)
					return FALSE;
			}
			if(abs(xto-xfrom)+abs(yto-yfrom)>1)
					return FALSE;

			if(yto>yfrom)
				return FALSE;
		}
		else
		{
			if(yto<=4)
			{
				if(xto%2!=0)
					return FALSE;
			}
			//ֻ��һ��
			if(abs(xto-xfrom)+abs(yto-yfrom)>1)
					return FALSE;
			//���ܻ�ͷ
			if(yto<yfrom)
				return FALSE;
		}
		break;
	case B_P://��
	case R_P:
		if(xto!=xfrom&&yto!=yfrom)
			return FALSE;
		if(TargetID==NOCHESS)//�ڲ�����ʱ
		{
			if(xto==xfrom)
			{
				if(yfrom<yto)
				{
					i=yfrom+1;
					j=yto;
					for(;i<j;i++)
						if(mark[i][xfrom].chessID!=NOCHESS)
							return FALSE;

				}
				else
				{
					i=yfrom-1;
					j=yto;
					for(;i>j;i--)
						if(mark[i][xfrom].chessID!=NOCHESS)
							return FALSE;

				}
			}//end xto==xfrom
			else if(yto==yfrom)
			{
				if(xfrom<xto)
				{
					i=xfrom+1;
					j=xto;
					for(;i<j;i++)
						if(mark[yfrom][i].chessID!=NOCHESS)	
							return FALSE;
				}
				else
				{
					i=xfrom-1;
					j=xto;
					for(;i>j;i--)
						if(mark[yfrom][i].chessID!=NOCHESS)	
							return FALSE;
				}

			}
		}//end not eat 
		else//���ӵ�ʱ��
		{
			int n=0;
			if(xfrom==xto)
			{

				if(yfrom<yto)
				{
					i=yfrom+1;
			    	j=yto;
					for(;i<j;i++)
					{
						if(mark[i][xfrom].chessID!=NOCHESS)
							n++;
					}
					if(n!=1)return FALSE;

				}
				else
				{
				i=yfrom-1;
				j=yto;
					for(;i>j;i--)
					{
						if(mark[i][xfrom].chessID!=NOCHESS)
							n++;
					}
					if(n!=1)return FALSE;

				}

			}//end xfrom==xto
			else if(yfrom==yto)
			{
				if(xfrom<xto)
				{
					i=xfrom+1;
					j=xto;
					for(;i<j;i++)
					{
						if(mark[yfrom][i].chessID!=NOCHESS)
							n++;
					}
					if(n!=1)return FALSE;
				}
				else 
				{
				i=xfrom-1;
				j=xto;
					for(;i>j;i--)
					{
						if(mark[yfrom][i].chessID!=NOCHESS)
							n++;
					}
					if(n!=1)
						return FALSE;

				}


			}//end yfrom==yto


		}//end eat
		break;
		default:
			return FALSE;
		}//end switch

	return TRUE;
}

