#ifndef __imageProcess_H__
#define __imageProcess_H__

extern uint8 CorrImg[CAMERA_H][CAMERA_W];
extern uint8 img[CAMERA_H][CAMERA_W];
extern int Rnum;
#define rowStart getRowStart//Rnum//               //ͼ������ʼ����
#define rowEnd   (getRowStart+10 )         //ͼ������ֹ����
#define rowNum   10 //rowEnd-rowStart  //��Ч����������ԭʼ�ɼ�����ΪROW(��Include.h�ж���)15
#define proPix   8                //��Ե���������߽���Ч���� 10 
#define CENTURE  (CAMERA_W/2)     //����ֵ
#define servMotorLeft     440     //390������ޣ�38 78
#define servMotorCenture  540      //�������λ��53 50-28
#define servMotorRight    640      //670����Ҽ��ޣ�68 24
#define servPram       getServoPram //���ת�Ǳ���ϵ��������������������Ƕȸ����������ֵ��������ǶȰڷ��ܴ��С��ֵ
#define BLACK   0
#define WHITE   255
#define EDGE  WHITE-BLACK         //�߽�ֵ��С
//
////////////�ϰ����б�/////////////////////////////////
#define  obstaclesOnLeft   8 //�ϰ�������ƫ��ƫ��
#define  obstaclesOnRight  3
int obstaclesErr;
/////////////////////////////////////////////////////
#define ROW 46//50//45
int black_left[60],black_right[60];//
int black_leftP[60],black_rightP[60];//�����������
int black_leftS[60],black_rightS[60];
int center_virtual[60],center[60];
int center_virtual_left[60],center_virtual_right[60];
int center_preJudge[60],center_preJudge_left[60],center_preJudge_right[60];
int getOneSideResult[60];//��Բ�����������󵥱����߽��
int bTw,wTb;//blackToWhite
//

uint32 zuo[rowNum] = {0};         //�����Ч��������˫�����Ե�������꣬��ʼ��Ϊ0
uint32 you[rowNum] = {CAMERA_W-1};     //�����Ч��������˫����Ե�������꣬��ʼ��ΪCOL-1

int32 zuoPos = 0;                 //��߽�λ��[�з�����]
int32 youPos = 0;                 //�ұ߽�λ��[�з�����]
int32 centure = 0;               //������ĵ�ǰ���������λ��[�޷�����]
int32 centureErr = 0;             //������ĵ�ǰ����λ��ƫ�� [�з�����]
int32 turn = 0;                   //�߽�����  ��Ϊ����ƫת  ��Ϊ����ƫת
uint8 zuoEdgeFlag = 0;            //��߽�ȷ�ϱ�־���ҵ���߽���λ
uint8 youEdgeFlag = 0;            //�ұ߽�ȷ�ϱ�־���ҵ���߽���λ
uint8 time;
uint32 centurepart[rowNum];
uint8 servoPmwData[3];
int half_Width[60]={0,0,0,0,0,0,4,4,5,5,6,               //0-10
                    6,6,7,7,7,8,8,9,9,9,                  //11-20
                    10,10,11,11,11,12,12,13,13,14,        //21-30
                    14,15,15,15,16,16,16,16,16,16,       //31-40
                    16,16,16,16,16,17,18,18,18,18};   //41-50 
int all_Width[10]={17,19,19,20,21,
                    23,23,25,26,27};//15-25
//-------------------------------------------ԭͼʹ�ò���------------------------
int16 manageData[4];

float angleWeightValue[10]={1.8,1.6,1.3,1.2,1.1,1,1,1,1,1};
int half_Width_deal=20;
int obstacles_Width=10;
float obstacles[60];
int turnPointPosLeft,turnPointPosRight,turnPointNumLeft,turnPointNumRight;
int turnPointPos_StartLeft,turnPointPos_StartRight;
int toLeftNum,toRightNum;
//Բ��
int circleTo_Left_Flag=0,circleTo_Right_Flag=0;//��Բ����־
int circleTo_Left_Flag1Num=0,circleTo_Left_Flag2Num=0;
int circleTo_Right_Flag1Num=0,circleTo_Right_Flag2Num=0;
//
void getSide_forHorizontal(int startL,int finshL,char dir);
void dealCircle();
int getLineInfo(char dir);
int zuoGetFlag,youGetFlag;
int lostLimitFlag;
int lostStartPos,lostEndPos;
int lostLeftPos,lostRightPos;
int lostLeftNum,lostRightNum;
int topLostPos,topLostPosFlag;//��ʼ���߲���
int left_start,left_end,right_start,right_end;
int leftPosGetFlag=0,rightPosGetFlag=0;
int CENTER_virtual;//��������                    
int deal_lineNum;//��������
int CentureErr_coefficient;//����ƫ����
char obstaclesFlag;
void outCircle();
int getObstacles();//�ϰ���ʶ��
void showImgData();
int getOneSideResultL[60],getOneSideResultR[60];
int followOneside(char dir);
//-------------------------------------------������ֹ--------------------------------
//
extern char circleEnable;
extern char obstaclesEnable;
//
extern int i1;
extern char Fn[5];
//Fn[0]--��������-L-R-S
//Fn[1]--ͼ��������ʾ
//Fn[2]--������ʾ
//Fn[3]--
//Fn[4]--Բ����־-L-R

///////////////Բ�����ò���///////////////////
extern int d_outcircleGiveValue_Left;// 16 //13��Բ���߽粹��ֵ��Խ�󣬳���Խ����
extern int d_inCircleValueL;// 23 //20��Բ��ϵ����ԽС����Խ��
extern int WanDaoLAdd;
extern int WanDaoRAdd;


uint8 antiVibrath;//����ϵ��
int getRowStart;//ǰհ
int getRowStartW;
float getServoPram;//���ϵ��
int getLostTopPosition(char dir);
void getCenter();
void getCenter_deal();
extern void DataReset(); 
extern void testImg();
extern void imageproc();
extern void preImageproc();
extern void getQianZhan_1();
void getAllPre_JudgePoint(int startRow,char showStat);
void getJudgePoint35_45();
void getCenterPoint(int row);
int getCircleOneSide(char P);
int absGet(int16 a);
int toTurnLineNum(int st,int fi,char dir);
void centureOut();
int getLostSideStartRow(int startL,char dir);//��ʼ����λ��
int getLostSideNum(int startL,int finshL,char dir);//ָ�����䶪������_(:�١���)_
int getLostSideRow(int startL,int finshL,char dir);//ָ�����䶪��λ��
void imgAddDot(int h,int w,int a);//������ʱ���㺯��
int lost_Left[60],lost_Right[60];
void getJudgePoint(int row);
int preJudgeLeftPos= 0;
int preJudgeRightPos=0;
int leftPos[60],rightPos[60],centerPos[60],searchPos[60];
int searchPosOne;
int searchPos[60];
int turnEr;//ת������-15~15
void oled_Show_Data(int page);   
extern int Row;
extern int pag;
#endif  //__imageProcess_H__