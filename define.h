//define.h//data structure and macros
#ifndef _DEFINE_H_
#define _DEFINE_H_
#define NOCHESS 0
#define B_K 1//�ڽ�
#define B_C 2//�ڳ�
#define B_M 3//����
#define B_P 4//����
#define B_S 5//��ʿ
#define B_X 6//����
#define B_B 7//�ڱ�
#define B_START B_K
#define B_END B_B
#define R_K 8//��˧
#define R_C 9//�쳵
#define R_M 10//����
#define R_P 11//����
#define R_S 12//��ʿ
#define R_X 13//����
#define R_B 14//���
#define R_START R_K
#define R_END R_B
#define IsBlack(x) (x>=B_START&&x<=B_END)//�ж��ǲ��Ǻڷ�����
#define IsRed(x) (x>=R_START&&x<=R_END)//�ж��ǲ��Ǻ췽����
//�ж��ǲ���ͬһ�ߵ���
#define IsSameSide(x,y) ((IsBlack(x)&&IsBlack(y))||(IsRed(x)&&IsRed(y)))
//����λ�õĽṹ
typedef struct _chessmanposition
{
	BYTE x;
	BYTE y;
	int chessID;//1-7�Ǻ�|8-14�Ǻ��
}CHESSMANPOS;
struct StepNode 
{
	//�ƶ�������
	CPoint from,to;
	int movestoneID;
	int movestoneno;//�ƶ������ӵĺ���
	//���Ե�����
	CPoint bekillstonepos;
	int bekillstoneID;
	int bekillstoneno;//���Ե����ӵĺ���
};
struct StepStack
{
	StepNode* stack;
	int top;
	int maxsize;
};




#endif