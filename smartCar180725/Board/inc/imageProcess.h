#ifndef __imageProcess_H__
#define __imageProcess_H__

extern uint8 CorrImg[CAMERA_H][CAMERA_W];
extern uint8 img[CAMERA_H][CAMERA_W];
extern int Rnum;
#define rowStart getRowStart//Rnum//               //图像处理起始行数
#define rowEnd   (getRowStart+10 )         //图像处理终止行数
#define rowNum   10 //rowEnd-rowStart  //有效处理行数，原始采集行数为ROW(在Include.h中定义)15
#define proPix   8                //边缘跟踪搜索边界有效像素 10 
#define CENTURE  (CAMERA_W/2)     //中心值
#define servMotorLeft     440     //390舵机左极限，38 78
#define servMotorCenture  540      //舵机中心位置53 50-28
#define servMotorRight    640      //670舵机右极限，68 24
#define servPram       getServoPram //舵机转角比例系数，调整方法：若舵机角度跟随慢增大该值，若舵机角度摆幅很大减小该值
#define BLACK   0
#define WHITE   255
#define EDGE  WHITE-BLACK         //边界值大小
//
////////////障碍物判别/////////////////////////////////
#define  obstaclesOnLeft   8 //障碍物中线偏差偏移
#define  obstaclesOnRight  3
int obstaclesErr;
/////////////////////////////////////////////////////
#define ROW 46//50//45
int black_left[60],black_right[60];//
int black_leftP[60],black_rightP[60];//横向搜索结果
int black_leftS[60],black_rightS[60];
int center_virtual[60],center[60];
int center_virtual_left[60],center_virtual_right[60];
int center_preJudge[60],center_preJudge_left[60],center_preJudge_right[60];
int getOneSideResult[60];//进圆环条件触发后单边搜线结果
int bTw,wTb;//blackToWhite
//

uint32 zuo[rowNum] = {0};         //存放有效处理行中双线左边缘的列坐标，初始化为0
uint32 you[rowNum] = {CAMERA_W-1};     //存放有效处理行中双线右缘的列坐标，初始化为COL-1

int32 zuoPos = 0;                 //左边界位置[有符号数]
int32 youPos = 0;                 //右边界位置[有符号数]
int32 centure = 0;               //计算出的当前车体的中心位置[无符号数]
int32 centureErr = 0;             //计算出的当前车体位置偏差 [有符号数]
int32 turn = 0;                   //边界走势  正为向左偏转  负为向右偏转
uint8 zuoEdgeFlag = 0;            //左边界确认标志，找到后边界置位
uint8 youEdgeFlag = 0;            //右边界确认标志，找到后边界置位
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
//-------------------------------------------原图使用参数------------------------
int16 manageData[4];

float angleWeightValue[10]={1.8,1.6,1.3,1.2,1.1,1,1,1,1,1};
int half_Width_deal=20;
int obstacles_Width=10;
float obstacles[60];
int turnPointPosLeft,turnPointPosRight,turnPointNumLeft,turnPointNumRight;
int turnPointPos_StartLeft,turnPointPos_StartRight;
int toLeftNum,toRightNum;
//圆环
int circleTo_Left_Flag=0,circleTo_Right_Flag=0;//进圆环标志
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
int topLostPos,topLostPosFlag;//起始丢边参数
int left_start,left_end,right_start,right_end;
int leftPosGetFlag=0,rightPosGetFlag=0;
int CENTER_virtual;//虚拟中心                    
int deal_lineNum;//处理行数
int CentureErr_coefficient;//中心偏移量
char obstaclesFlag;
void outCircle();
int getObstacles();//障碍物识别
void showImgData();
int getOneSideResultL[60],getOneSideResultR[60];
int followOneside(char dir);
//-------------------------------------------参数截止--------------------------------
//
extern char circleEnable;
extern char obstaclesEnable;
//
extern int i1;
extern char Fn[5];
//Fn[0]--赛道类型-L-R-S
//Fn[1]--图像数据显示
//Fn[2]--数据显示
//Fn[3]--
//Fn[4]--圆环标志-L-R

///////////////圆环作用参数///////////////////
extern int d_outcircleGiveValue_Left;// 16 //13出圆环边界补偿值，越大，出环越靠外
extern int d_inCircleValueL;// 23 //20进圆环系数，越小作用越大
extern int WanDaoLAdd;
extern int WanDaoRAdd;


uint8 antiVibrath;//防抖系数
int getRowStart;//前瞻
int getRowStartW;
float getServoPram;//打角系数
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
int getLostSideStartRow(int startL,char dir);//开始丢边位置
int getLostSideNum(int startL,int finshL,char dir);//指定区间丢边数量_(:з」∠)_
int getLostSideRow(int startL,int finshL,char dir);//指定区间丢边位置
void imgAddDot(int h,int w,int a);//找中线时画点函数
int lost_Left[60],lost_Right[60];
void getJudgePoint(int row);
int preJudgeLeftPos= 0;
int preJudgeRightPos=0;
int leftPos[60],rightPos[60],centerPos[60],searchPos[60];
int searchPosOne;
int searchPos[60];
int turnEr;//转向趋势-15~15
void oled_Show_Data(int page);   
extern int Row;
extern int pag;
#endif  //__imageProcess_H__