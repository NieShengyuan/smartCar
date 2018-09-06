#ifndef __dataVisualization_H__
#define __dataVisualization__H__
////////////////���ݷ���״̬/////////////////
#define ERROR 0.001
int16 motorPiToComputerData[4];
int16 servoPdToComputerData[4];
char  SENDPIDDATA='G';//���ݷ���
char SENDSERVODATA='G';

////////////////��������Ԫ��ʹ�ܱ�־/////////////////
char circleEnable='C';
char obstaclesEnable='C';

////////////////������־λ/////////////////
char Fn[5];
//Fn[0]--��������-L-R-S
//Fn[1]--������ʾ����
//Fn[2]--
//Fn[3]--
//Fn[4]--Բ����־-L-R

////////////////PID/////////////////
double P_DATA=0;
double I_DATA=0;
int16 setSpeedMotor;
typedef struct PID
{	
  int SetPoint; //�趨Ŀ�� Desired Value
  long SumError; //����ۼ�
  double Proportion; //�������� Proportional Const
  double Integral; //���ֳ��� Integral Const
  double Derivative; //΢�ֳ��� Derivative Const
  int LastError; //Error[-1]
  int PrevError; //Error[-2]
} PID;
static PID sPID;
static PID *sptr = &sPID;

////////////////�ٶȲ���/////////////////
uint16 g16_goalSpeed;//�ٶȵ���
uint16 g16_setCoverSpeed;//����ٶ�
extern int getRowStart;//ǰհ
extern int getRowStartW;//���ǰհ
extern float getServoPram;//���ϵ��
extern uint8 antiVibrath;  //ֱ��������ϵ��
int WanDaoLAdd,WanDaoRAdd;
uint16 gearOne[2],gearTwo[2],gearThree[2];//ֱ�������
int pag;

////////////////ͼ����Դ/////////////////
extern char workMode[4];//����������ģʽ+imageShow

////////////////���ڲ���/////////////////
char ch;//�����������λ��
char getDataStation='F';//����������ձ�־

////////////////���뿪��/////////////////
void switch_Init();
void data_Init();
////////////////OLED ��Ļ/////////////////
void oled_Display();

//���
double servoKP;
double servoKD;
double d_servoKP_L;
double d_servoKD_L;
uint16 goalServoValue;
int16 servo_iError,servo_dError,servo_setPoint,servo_LastError;
extern uint16 g16_goalSteeringValue;//
void servo_Init();//�����ʼ��
extern void servoPwmOut(int16 nextPoint);//��������
//���
int16 motorPICalc(int16 NextPoint);
int16 iError, iIncpid; //��ǰ���
void motor_Init();
void forward(uint32 MotorPWM);
void back(uint32 MotorPWM);
//��������
void keyConfig();//������ʼ��
void PORTE_IRQHandler(void);
void key_handler(void);
//DIPSWITCH
void dipSwitch_server();
//����
void uart_Init();
void uart_handler(void);
//������
void PIT0_IRQHandler(void);
void encoder_Init();
void dipSwitch_server2();
void dataManageInit();//��ʼ��
extern void dataVisualization();//���ݴ���
extern void dataVisualizationConfig_Init();//dataVisualization���ú���
#endif 