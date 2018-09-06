#ifndef __dataVisualization_H__
#define __dataVisualization__H__
////////////////数据发送状态/////////////////
#define ERROR 0.001
int16 motorPiToComputerData[4];
int16 servoPdToComputerData[4];
char  SENDPIDDATA='G';//数据发送
char SENDSERVODATA='G';

////////////////赛道特殊元素使能标志/////////////////
char circleEnable='C';
char obstaclesEnable='C';

////////////////赛道标志位/////////////////
char Fn[5];
//Fn[0]--赛道类型-L-R-S
//Fn[1]--数据显示控制
//Fn[2]--
//Fn[3]--
//Fn[4]--圆环标志-L-R

////////////////PID/////////////////
double P_DATA=0;
double I_DATA=0;
int16 setSpeedMotor;
typedef struct PID
{	
  int SetPoint; //设定目标 Desired Value
  long SumError; //误差累计
  double Proportion; //比例常数 Proportional Const
  double Integral; //积分常数 Integral Const
  double Derivative; //微分常数 Derivative Const
  int LastError; //Error[-1]
  int PrevError; //Error[-2]
} PID;
static PID sPID;
static PID *sptr = &sPID;

////////////////速度参数/////////////////
uint16 g16_goalSpeed;//速度调节
uint16 g16_setCoverSpeed;//弯道速度
extern int getRowStart;//前瞻
extern int getRowStartW;//弯道前瞻
extern float getServoPram;//打角系数
extern uint8 antiVibrath;  //直道防抖动系数
int WanDaoLAdd,WanDaoRAdd;
uint16 gearOne[2],gearTwo[2],gearThree[2];//直道，弯道
int pag;

////////////////图像来源/////////////////
extern char workMode[4];//主函数工作模式+imageShow

////////////////串口参数/////////////////
char ch;//串口命令接收位置
char getDataStation='F';//串口命令接收标志

////////////////拨码开关/////////////////
void switch_Init();
void data_Init();
////////////////OLED 屏幕/////////////////
void oled_Display();

//舵机
double servoKP;
double servoKD;
double d_servoKP_L;
double d_servoKD_L;
uint16 goalServoValue;
int16 servo_iError,servo_dError,servo_setPoint,servo_LastError;
extern uint16 g16_goalSteeringValue;//
void servo_Init();//舵机初始化
extern void servoPwmOut(int16 nextPoint);//打角量输出
//电机
int16 motorPICalc(int16 NextPoint);
int16 iError, iIncpid; //当前误差
void motor_Init();
void forward(uint32 MotorPWM);
void back(uint32 MotorPWM);
//按键部分
void keyConfig();//按键初始化
void PORTE_IRQHandler(void);
void key_handler(void);
//DIPSWITCH
void dipSwitch_server();
//串口
void uart_Init();
void uart_handler(void);
//编码器
void PIT0_IRQHandler(void);
void encoder_Init();
void dipSwitch_server2();
void dataManageInit();//初始化
extern void dataVisualization();//数据处理
extern void dataVisualizationConfig_Init();//dataVisualization配置函数
#endif 