/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *-------------------------------------------------------------------------------
     拨码开关1--图像显示控制+默认数据显示控制
            2--其他数据显示控制
 */
//场中断和PCLK都加个 150欧下拉电阻来滤波
#include "common.h"
#include "include.h" 
#include "IPM.h"
uint16 g16_goalSteeringValue;
//函数声明
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void PIT0_IRQHandler();
void system_Init();
void keyConfig();//按键初始化
void ledStart();
uint8 img[CAMERA_H][CAMERA_W]; 
uint8 imgbuff[CAMERA_SIZE];
char workMode[4];
void  main(void)
{
    uint32 i;
    system_Init();
    //////////////逆透视变换参数初始化/////////////
    //BuketCorrInit(-0.00001374,-0.00001057);  // 桶形矫正初始化，建立矫正表 
    //PMCorrInit();  //透视正变换初始化，建立正映射表
    //IPMCorrInit(); //逆透视映射初始化，建立反矫正表
    while(1)
    { 
        camera_get_img();  //摄像头获取图像
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
    /************************ 配置 K60 的优先级  ***********************/
    NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);            //设置优先级分组,4bit 抢占优先级,没有亚优先级
    NVIC_SetPriority(UART0_RX_TX_IRQn,0);          //配置优先级
    NVIC_SetPriority(PORTA_IRQn,1);         //配置优先级
    NVIC_SetPriority(DMA0_DMA16_IRQn,2);          //配置优先级
    NVIC_SetPriority(PIT0_IRQn,3);          //配置优先级
    
    /************************ 摄像头 初始化  ***********************/
    camera_init(imgbuff);                                   //摄像头初始化，把图像采集到 imgbuff 地址
    //配置中断服务函数
    set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);    //设置 PORTA 的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA0_DMA16_VECTORn ,DMA0_IRQHandler);      //设置 DMA0 的中断服务函数为 DMA0_IRQHandler
    lcd_init();
    LCD_CLS();
    gpio_init(PTD5,GPO,0); //beep
    gpio_init(PTB20,GPO,1);                         //初始化LED3   ，灭
    gpio_init(PTB21,GPO,1);
    gpio_init(PTB22,GPO,1);
    gpio_init(PTB23,GPO,1);
    lcd_init();
    ledStart();
    /************************ 数据处理  **********************/
    dataVisualizationConfig_Init();
    
}


/*!
 *  @brief      PORTA中断服务函数
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
    uint8  n;    //引脚号
    uint32 flag;

    //while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //清中断标志位

    n = 29;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        camera_vsync();
    }
}

/*!
 *  @brief      DMA0中断服务函数
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

