/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *-------------------------------------------------------------------------------
     ���뿪��1--ͼ����ʾ����+Ĭ��������ʾ����
            2--����������ʾ����
 */
//���жϺ�PCLK���Ӹ� 150ŷ�����������˲�
#include "common.h"
#include "include.h" 
#include "IPM.h"
uint16 g16_goalSteeringValue;
//��������
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void PIT0_IRQHandler();
void system_Init();
void keyConfig();//������ʼ��
void ledStart();
uint8 img[CAMERA_H][CAMERA_W]; 
uint8 imgbuff[CAMERA_SIZE];
char workMode[4];
void  main(void)
{
    uint32 i;
    system_Init();
    //////////////��͸�ӱ任������ʼ��/////////////
    //BuketCorrInit(-0.00001374,-0.00001057);  // Ͱ�ν�����ʼ�������������� 
    //PMCorrInit();  //͸�����任��ʼ����������ӳ���
    //IPMCorrInit(); //��͸��ӳ���ʼ����������������
    while(1)
    { 
        camera_get_img();  //����ͷ��ȡͼ��
        img_extract(img,imgbuff,CAMERA_SIZE);  
        testImg();
        if(workMode[0]=='A')//switch1
        {
            OLED_PrintImage((uint8 *)img,60,80);
        }
        dataVisualization();
        PTB22_T= 1;
    }
   
}

//640
void system_Init()
{
    /************************ ���� K60 �����ȼ�  ***********************/
    NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);            //�������ȼ�����,4bit ��ռ���ȼ�,û�������ȼ�
    NVIC_SetPriority(UART0_RX_TX_IRQn,0);          //�������ȼ�
    NVIC_SetPriority(PORTA_IRQn,1);         //�������ȼ�
    NVIC_SetPriority(DMA0_DMA16_IRQn,2);          //�������ȼ�
    NVIC_SetPriority(PIT0_IRQn,3);          //�������ȼ�
    
    /************************ ����ͷ ��ʼ��  ***********************/
    camera_init(imgbuff);                                   //����ͷ��ʼ������ͼ��ɼ��� imgbuff ��ַ
    //�����жϷ�����
    set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //���� PORTA ���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_DMA16_VECTORn ,DMA0_IRQHandler);      //���� DMA0 ���жϷ�����Ϊ DMA0_IRQHandler
    lcd_init();
    LCD_CLS();
    gpio_init(PTD5,GPO,0); //beep
    gpio_init(PTB20,GPO,1);                         //��ʼ��LED3   ����
    gpio_init(PTB21,GPO,1);
    gpio_init(PTB22,GPO,1);
    gpio_init(PTB23,GPO,1);
    lcd_init();
    ledStart();
    /************************ ���ݴ���  **********************/
    dataVisualizationConfig_Init();
    
}


/*!
 *  @brief      PORTA�жϷ�����
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    //while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //���жϱ�־λ

    n = 29;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        camera_vsync();
    }
}

/*!
 *  @brief      DMA0�жϷ�����
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}

void ledStart()
{
    PTB20_OUT=0;PTB21_OUT=1;PTB22_OUT=1;PTB23_OUT=1;
    DELAY_MS(300);
    PTB20_OUT=1;PTB21_OUT=0;PTB22_OUT=1;PTB23_OUT=1;
    DELAY_MS(300);
    PTB20_OUT=1;PTB21_OUT=1;PTB22_OUT=0;PTB23_OUT=1;
    DELAY_MS(300);
    PTB20_OUT=1;PTB21_OUT=1;PTB22_OUT=1;PTB23_OUT=0;
    DELAY_MS(300);
    PTB20_OUT=1;PTB21_OUT=1;PTB22_OUT=1;PTB23_OUT=1;
}

