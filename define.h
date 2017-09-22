//define.h//data structure and macros
#ifndef _DEFINE_H_
#define _DEFINE_H_
#define NOCHESS 0
#define B_K 1//黑将
#define B_C 2//黑车
#define B_M 3//黑马
#define B_P 4//黑炮
#define B_S 5//黑士
#define B_X 6//黑象
#define B_B 7//黑兵
#define B_START B_K
#define B_END B_B
#define R_K 8//红帅
#define R_C 9//红车
#define R_M 10//红马
#define R_P 11//红炮
#define R_S 12//红士
#define R_X 13//红相
#define R_B 14//红兵
#define R_START R_K
#define R_END R_B
#define IsBlack(x) (x>=B_START&&x<=B_END)//判断是不是黑方的子
#define IsRed(x) (x>=R_START&&x<=R_END)//判断是不是红方的子
//判断是不是同一边的子
#define IsSameSide(x,y) ((IsBlack(x)&&IsBlack(y))||(IsRed(x)&&IsRed(y)))
//棋子位置的结构
typedef struct _chessmanposition
{
	BYTE x;
	BYTE y;
	int chessID;//1-7是黑|8-14是红的
}CHESSMANPOS;
struct StepNode 
{
	//移动的棋子
	CPoint from,to;
	int movestoneID;
	int movestoneno;//移动的棋子的号码
	//被吃的棋子
	CPoint bekillstonepos;
	int bekillstoneID;
	int bekillstoneno;//被吃的棋子的号码
};
struct StepStack
{
	StepNode* stack;
	int top;
	int maxsize;
};




#endif