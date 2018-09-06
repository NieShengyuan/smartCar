#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include 用户自定义的头文件
 */
#include  "MK66_wdog.h"
#include  "MK66_gpio.h"     //IO口操作
#include  "MK66_uart.h"     //串口
#include  "MK66_i2c.h"      //I2C
#include  "MK66_spi.h"      //SPI
#include  "MK66_rtc.h"      //RTC
#include  "MK66_adc.h"      //ADC
#include  "MK66_dma.h"      //DMA
#include  "MK66_sdhc.h"     //SDHC
#include  "VCAN_LED.H"          //LED
#include  "VCAN_KEY.H"          //KEY
#include  "VCAN_RTC_count.h"    //RTC 时间转换
#include  "VCAN_camera.h"       //摄像头总头文件
#include  "ff.h"                //FatFs
#include  "vcan_img2sd.h"       //存储图像到sd卡一个文件
#include  "vcan_sd_app.h"       //SD卡应用（显示sd看上图片固件）
#include  "VCAN_computer.h"     //多功能调试助手
#include  "enter.h"
#include "oled.h"


#endif  //__INCLUDE_H__
