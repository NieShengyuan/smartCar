#include "include.h"
#include "dataVisualization.h"
int Rnum;
extern uint16 aaa ;
uint16 spdDat1,spdDat2;//ͣ��ʱ��ʱ���ٶ�

int d_outcircleGiveValue_Left;// 16 
int d_inCircleValueL;// 23
void dataVisualization()
{
    if('T'==getDataStation)//�жϽ����־
    {
        getDataStation='F';//��λ��'T'or'F'��
        switch(ch)
        {
        case 'P': printf("P-");servoKP=servoKP+0.01;printf("%d\n",servoKP*100);break;
        case 'p': printf("p-");servoKP=servoKP-0.01;printf("%d\n",servoKP*100);break;
        case 'I': printf("P-");servoKP=servoKP+0.1;printf("%d\n",servoKP*100);break;
        case 'i': printf("p-");servoKP=servoKP-0.1;printf("%d\n",servoKP*100);break;
        
        case 'M': printf("I-");servoKD=servoKD+0.01;printf("%d\n",servoKD*100);break;//������ٶ�
        case 'm': printf("I-");servoKD=servoKD-0.01;printf("%d\n",servoKD*100);break;
        
        
        case 'Q': printf("Q");getRowStartW+=1;printf("-getRowStart %d\n",getRowStartW);break;//ǰհ
        case 'q': printf("q");getRowStartW-=1;printf("-getRowStart %d\n",getRowStartW);break;
        case 'J': printf("J");getServoPram=getServoPram+0.1;printf("-getServoPram %f\n",getServoPram);break;//���ϵ��
        case 'j': printf("j");getServoPram=getServoPram-0.1;printf("-getServoPram %f\n",getServoPram);break;
        case 'Z': printf("Z");g16_goalSpeed=g16_goalSpeed+5;printf("-g16_goalSpeed %d\n",g16_goalSpeed);break;//���ϵ��
        case 'z': printf("z");g16_goalSpeed=g16_goalSpeed-5;printf("-g16_goalSpeed %d\n",g16_goalSpeed);break;
        case 'W': printf("get Wandao+ ");g16_setCoverSpeed=g16_setCoverSpeed+5;printf("%d\n",g16_setCoverSpeed);break;//����ٶ�
        case 'w': printf("get Wandao- ");g16_setCoverSpeed=g16_setCoverSpeed-5;printf("%d\n",g16_setCoverSpeed); break;
       // case 'M': printf("MotorSpeed+ ");g16_goalSpeed=g16_goalSpeed+5;printf("%d\n",g16_goalSpeed);break;//������ٶ�
        //case 'm': printf("MotorSpeed- ");g16_goalSpeed=g16_goalSpeed-5;printf("%d\n",g16_goalSpeed);break;
        case 'G': printf("GO--");printf("%d\n",g16_goalSpeed);break;//����
        case 'S': printf("---STOP---\n");spdDat1=g16_setCoverSpeed;g16_setCoverSpeed=0;spdDat2=g16_goalSpeed;g16_goalSpeed=0;ftm_pwm_duty(FTM0, FTM_CH2, 0);ftm_pwm_duty(FTM0, FTM_CH3, 0); while(ch!='G');break;//���ֹͣ
        case 'K': printf("Gear One ");g16_goalSpeed=gearOne[0];g16_setCoverSpeed=gearOne[1];printf("%d\n",gearOne);break;
        case 'N': printf("Gear Two ");g16_goalSpeed=gearTwo[0];g16_setCoverSpeed=gearTwo[1];printf("%d\n",gearTwo);break;
        case 'R': printf("Gear Three ");g16_goalSpeed=gearThree[0];g16_setCoverSpeed=gearThree[1];printf("%d\n",gearThree);break;
        
        case 'A': printf("F1-->");d_inCircleValueL+=1;printf("d_inCircleValueL=%d\n",d_inCircleValueL);break;//F1
        case 'a': printf("F2-->");d_inCircleValueL-=1;printf("d_inCircleValueL=%d\n",d_inCircleValueL);break;//F2
        case 'B': printf("F3-->");d_outcircleGiveValue_Left+=1;printf("d_outcircleGiveValue_Left=%d\n",d_outcircleGiveValue_Left);break;//F3
        case 'b': printf("F4-->");d_outcircleGiveValue_Left-=1;printf("d_outcircleGiveValue_Left=%d\n",d_outcircleGiveValue_Left);break;//F4
        case 'C': printf("F5-");Rnum+=1;printf("Rnum=%d\n",Rnum);break;//F5
        case 'c': printf("F6-");Rnum-=1;printf("Rnum=%d\n",Rnum);break;//F6
        
        }
    }
    
}

//ABab
//CDcd
//EFef
//HIhi
//JKjk
//LMlm
//NOno
//PQ
//
//
//SG

void dataManageInit()
{
    /////////////////////////���޸Ĳ���/////////////////////////////////////////
    servoKP=3.88;//ԭͼ��
    servoKD=0.05;
    d_inCircleValueL=20;//ԽС����Բ��Խ��
    d_outcircleGiveValue_Left=14;//ԽС����Բ��Խ��
    
    Rnum=1;
    ////��ֵԽ��Խ����///
    WanDaoLAdd=25;
    WanDaoRAdd=28;
    //////////////////////////////////////////////////////////////////

    //ǰհ
    getRowStart=18; //18//22 //25//28//40���޸�
    getRowStartW=20;//20//���ʱǰհֵ���޸�
    //���ϵ��
    getServoPram=6.0;//11.0;//13.0//3.5//
    antiVibrath=40;   //����ϵ��45

    //ֱ���ٶ�
    gearOne[0]=0;
    gearTwo[0]=165;
    gearThree[0]=190;
    //����ٶ�
    gearOne[1]=0;
    gearTwo[1]=150;
    gearThree[1]=165;
    //PID_Init();
    //i1=380;
    //double servoKP,servoKD;
    
    d_servoKP_L=3.83;
    d_servoKD_L=0.0;
    printf("\n\n------>finsh<------\n\n");
    
    P_DATA=13.8;
    I_DATA=0.0;

    
    dipSwitch_server();
    dipSwitch_server2();
    /////////////////��ʼ��ʱ��ӡ��Ϣ/////////////////////////////////////////
    printf("\nF1-F2-d_inCircleValueL=%d\n",d_inCircleValueL);
    printf("\nF3-F4-d_outcircleGiveValue_Left=%d\n",d_outcircleGiveValue_Left);
    printf("\ng16_goalSpeed=%d\n",g16_goalSpeed);
    printf("\ng16_setCoverSpeed=%d\n",g16_setCoverSpeed);
    printf("\nqianzhan=%d\n",getRowStartW);
}
/////////////////////�ٶȿ���///////////////////
void dipSwitch_server2()
{
     //3
    if (0==PTC6_IN)
    {
        oled_Display();
    }
    //4
    if (0==PTC7_IN)
    {
        getRowStart=23; //18//22 //25//28//40���޸�
    getRowStartW=24;//20//���ʱǰհֵ���޸�
    
        g16_goalSpeed=240;
        g16_setCoverSpeed=230;
    }
  

    //5
    if (0==PTC8_IN)//
    {
       getRowStart=18; //18//22 //25//28//40���޸�
    getRowStartW=20;//20//���ʱǰհֵ���޸�
        g16_goalSpeed=250;
        g16_setCoverSpeed=240;
        
    }
    
    //6
    if (0==PTC9_IN)//
    {
        g16_goalSpeed=270;
        g16_setCoverSpeed=270;
    }
}
/////////////ͼ����Ϣ��ʾ//////////////////////
void dipSwitch_server()
{
    if(0==PTC4_IN)//1��ʾ����
    {
        workMode[0]='A';//ͼ����ʾ
        Fn[2]='A';//ͼ�����ݻ��ߴ���
        Fn[1]='A'; //������ʾ  
    }
    else
    {
        workMode[0]='B';Fn[2]='B';Fn[1]='B';
    }
    /////////2yuanhuan//////////////////////
    if (0==PTC5_IN)//
    {
        circleEnable='O'; //
 
    }
    else 
        circleEnable='C';
    //--------------------------
   
    
   
}

//PID
void IncPIDInit(void)	
{
  sptr->SumError = 0;
  sptr->LastError = 0; //Error[-1]
  sptr->PrevError = 0; //Error[-2]
  sptr->Proportion = P_DATA; //�������� Proportional Const
  sptr->Integral =   I_DATA; //���ֳ���Integral Const
}
int16 motorPICalc(int16 NextPoint)	
{
    if('S'==Fn[0])
    {
        iError = g16_goalSpeed - NextPoint; //ֱ��
        setSpeedMotor=g16_goalSpeed;
    }
    else
    {
        iError = g16_setCoverSpeed - NextPoint; //��������
        setSpeedMotor=g16_setCoverSpeed;
    }
    
    
  iIncpid = P_DATA * iError //E[k]��
	- I_DATA * sptr->LastError; //E[k��1]��;
  sptr->PrevError = sptr->LastError;//�洢�������´μ���
  sptr->LastError = iError;
  return(iIncpid+g16_goalSpeed);//��������ֵ
}
void setmotorspeed(int16 setspeed)
{
  if(setspeed>900)
    setspeed=900;
  if(setspeed<-750)
    setspeed=-750;
  motorPiToComputerData[3]=setspeed;//�������ռ�ձ�
  if(setspeed>=0)
  {   
      forward(setspeed);
  }
  else
  {
        back(-setspeed);
  }
}
//-------------------------------------------------------------------

//--<�������
void servoPwmOut(int16 nextPoint) 
{//input g16_goalSteeringValue 
    //ʹ�ò�ͬ��pid
    
    goalServoValue = 540-servoKP*nextPoint - servoKD*servo_LastError;//������
    servo_LastError=nextPoint;
    //goalServoValue=nextPoint;
    
    if(goalServoValue<440)
    {
        goalServoValue=440;
    }
    else if(goalServoValue>640)
    {
        goalServoValue=640;
    }
    if(goalServoValue-540>50)
    {
        Fn[0]='R';
        //PTD5_OUT=1;
    }
    else if(goalServoValue-540<-50)
    {
        Fn[0]='L';
        //PTD5_OUT=1;
    } 
    ftm_pwm_duty(FTM2, FTM_CH0,0.01*goalServoValue);

    if('F'==SENDSERVODATA)
    {
        servoPdToComputerData[0]=nextPoint+540;//��ǰת��
        servoPdToComputerData[1]=goalServoValue;//���������
        servoPdToComputerData[2]=servo_LastError+540;//ƫ��
        servoPdToComputerData[3]=540;//
        vcan_sendware((int16_t *)servoPdToComputerData,sizeof(servoPdToComputerData));
    }
}
void servo_Init()
{
    ftm_pwm_init(FTM2, FTM_CH0,50.000,50,FTM2_CH0_PIN);
    printf("\n servo init--success\n");
}//-->
    
//--<�������
void motor_Init()
{
    gpio_init (PTE27, GPI,1);    //��ʼ�� 
    PTE27_OUT = 0;
    ftm_pwm_init(FTM0,FTM_CH3,10000,1000,FTM0_CH3_PIN);//A6  
    ftm_pwm_init(FTM0,FTM_CH4,10000,1000,FTM0_CH4_PIN);//A7 
    ftm_pwm_duty(FTM0,FTM_CH3,0);       //
    ftm_pwm_duty(FTM0,FTM_CH4,0);       //
    printf("\n motor init--success\n");
    /*
    GND
    A7
    A6
    E27   EN INB INA GND*/
    //��ɫ ��ɫ
    
}
void forward(uint32 MotorPWM)
{
    if(MotorPWM>=900)MotorPWM=900;//�޷�
    ftm_pwm_duty(FTM0, FTM_CH3, 0);
    ftm_pwm_duty(FTM0, FTM_CH4, MotorPWM*0.1);   
}
void back(uint32 MotorPWM)
{
    if(MotorPWM>=900)MotorPWM=900;//�޷�
    ftm_pwm_duty(FTM0, FTM_CH3, MotorPWM*0.1);
    ftm_pwm_duty(FTM0, FTM_CH4, 0);  
}//-->

//--<������ʼ����ʼ
void keyConfig()
{//�����ж�����
    port_init(PTE24, ALT1 | IRQ_FALLING | PULLUP );          //��ʼ�� PTD7 �ܽţ����ù���ΪGPIO ���½��ش����жϣ���������    
    port_init(PTE25, ALT1 | IRQ_FALLING | PULLUP );
    port_init(PTE26, ALT1 | IRQ_FALLING | PULLUP );
    port_init(PTE27, ALT1 | IRQ_FALLING | PULLUP );
    set_vector_handler(PORTE_VECTORn ,PORTE_IRQHandler);    //����PORTE���жϷ�����Ϊ PORTE_IRQHandler    
    enable_irq (PORTE_IRQn);                                //ʹ��PORTE�ж�
    printf("\n key init--success\n");
}
void key_handler(void) 
{//�ҳ���Ҫ�����������˴����д���
    if(0==PTE24_IN){pag=pag+1;}
    if(0==PTE25_IN){pag=pag-1;}
    if(0==PTE26_IN){P_DATA=P_DATA+1.01;printf("MP%d",P_DATA*100);}
    if(0==PTE27_IN){P_DATA=P_DATA-0.01;printf("MP%d",P_DATA*100);}
}
void PORTE_IRQHandler(void)
{//�����ж�����
    if(0==PTE24_IN){DELAY_MS(10);if(0==PTE24_IN){PORT_FUNC(E,24,key_handler);PORTE_ISFR  = (1 << 24);}}
    if(0==PTE25_IN){DELAY_MS(10);if(0==PTE25_IN){PORT_FUNC(E,25,key_handler);PORTE_ISFR  = (1 << 25);}}
    if(0==PTE26_IN){DELAY_MS(10);if(0==PTE26_IN){PORT_FUNC(E,26,key_handler);PORTE_ISFR  = (1 << 26);}}
    if(0==PTE27_IN){DELAY_MS(10);if(0==PTE27_IN){PORT_FUNC(E,27,key_handler);PORTE_ISFR  = (1 << 27);}}
}//-->������ʼ������

//���ڲ���
void uart_Init()
{
    set_vector_handler(UART0_RX_TX_VECTORn + VCAN_PORT*2,uart_handler);    
    uart_rx_irq_en (VCAN_PORT);
    printf("\n uart init--success\n");
}
void uart_handler(void)
{if(uart_query(VCAN_PORT) == 1){uart_getchar(VCAN_PORT, &ch);}getDataStation = 'T';}

void encoder_Init()
{
    ftm_quad_init(FTM1,FTM_PS_1,FTM1_QDPHA_PIN,FTM1_QDPHB_PIN); //FTM1 ���������ʼ�� 
    pit_init_ms(PIT0, 20);                                 //��ʼ��PIT0����ʱʱ��Ϊ�� 500ms    
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϷ�����Ϊ PIT0_IRQHandler    
    enable_irq (PIT0_IRQn); 
    printf("\n encoder init--success\n");
}
//����������
void PIT0_IRQHandler(void)    
{    
    
    int16 val;
    val = ftm_quad_get(FTM1);          //��ȡFTM �������� ��������(������ʾ������)    
    ftm_quad_clean(FTM1);    
    setmotorspeed(motorPICalc(val));
    
    if(SENDPIDDATA=='F')
    { 
    motorPiToComputerData[0]=setSpeedMotor;//�趨������
    motorPiToComputerData[1]=motorPICalc(val);//�������ռ�ձ�
    motorPiToComputerData[2]=val;//��ǰ������
    vcan_sendware((int16_t *)motorPiToComputerData,sizeof(motorPiToComputerData));
    }  
    
    
    PIT_Flag_Clear(PIT0);       //���жϱ�־λ    
}


void dataVisualizationConfig_Init()//dataVisualization���ú���
{
    
    switch_Init();
    uart_Init();//���ڳ�ʼ��
    motor_Init();//�����ʼ��
    servo_Init();//�����ʼ�� 
    keyConfig();//������ʼ��
    encoder_Init();
    dataManageInit();//���ݳ�ʼ��
    IncPIDInit();
    
}
void switch_Init()
{
    gpio_init(PTC4,GPI,1);
    gpio_init(PTC5,GPI,1);
    gpio_init(PTC6,GPI,1);
    gpio_init(PTC7,GPI,1);
    gpio_init(PTC8,GPI,1);
    gpio_init(PTC9,GPI,1);
}