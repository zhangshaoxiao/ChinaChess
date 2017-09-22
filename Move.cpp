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
	if(IsSameSide(MovechessID,TargetID))//不能吃自己的子,在define.h 里面的宏
		return FALSE;
	switch(MovechessID)
	{
	case B_K:
		if(!ischangestone)	 //没有交换棋子颜色
		{
			if(TargetID==R_K)//老将见面
			{
				if(xfrom!=xto)
					return FALSE;
				for(i=yfrom+1;i<yto;i++)
					if(mark[i][xfrom].chessID!=NOCHESS)	
						return FALSE;
			}
			else           //交换棋子颜色
			{
				if(xto<3||xto>5||yto<0||yto>2)//在宫内走
				   return FALSE;
				if((abs(xto-xfrom)+abs(yto-yfrom))>1)//只走一步
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
	case R_K://红帅
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
			if(TargetID==R_K)//老将见面
			{
				if(xfrom!=xto)
					return FALSE;
				for(i=yfrom+1;i<yto;i++)
					if(mark[i][xfrom].chessID!=NOCHESS)	
						return FALSE;
			}
			else
			{
				if(xto<3||xto>5||yto<0||yto>2)//在宫内走
				   return FALSE;
				if((abs(xto-xfrom)+abs(yto-yfrom))>1)//只走一步
					return FALSE;
			}
		}
		break;
	case B_S://黑士
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
	case B_X://黑象
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
	case B_M://马
	case R_M:
		if((abs(xfrom-xto)!=1||abs(yfrom-yto)!=2)&&
			(abs(xfrom-xto)!=2||abs(yfrom-yto)!=1))
			return FALSE;
		//拌马脚
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
	case B_C://车
	case R_C:
		if((xfrom!=xto)&&(yfrom!=yto))
			return FALSE;
		if(xfrom==xto)//同一列上
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
		else if(yfrom==yto)//同一行上
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
	case B_B://黑兵
		if(!ischangestone)
		{
			if(yto<=4)
			{
				if(xto%2!=0)
					return FALSE;
			}
			//只走一步
			if(abs(xto-xfrom)+abs(yto-yfrom)>1)
					return FALSE;
			//不能回头
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
	case R_B://红兵
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
			//只走一步
			if(abs(xto-xfrom)+abs(yto-yfrom)>1)
					return FALSE;
			//不能回头
			if(yto<yfrom)
				return FALSE;
		}
		break;
	case B_P://炮
	case R_P:
		if(xto!=xfrom&&yto!=yfrom)
			return FALSE;
		if(TargetID==NOCHESS)//炮不吃子时
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
		else//吃子的时候
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

