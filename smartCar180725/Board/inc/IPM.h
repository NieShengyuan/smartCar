#ifndef _IPM_H
#define _IPM_H

#define imagedeal_W       80
#define imagedeal_H       60

extern Site_t IPMCorr[imagedeal_H][imagedeal_W];   //透视变换映射表
extern Site_t PMCorr[imagedeal_H][imagedeal_W];    //逆透视变换映射表
extern Site_t BuketCorr[imagedeal_H][imagedeal_W]; //桶形矫正映射表
extern unsigned char CorrImg[imagedeal_H][imagedeal_W]; //矫正后图像数组

extern void BuketCorrInit( float k1, float k2 );
extern void PMCorrInit(void) ;//逆透视变换初始化，建立映射表
extern void IPMCorrInit(void);//逆透视映射表
extern void BuketCorrect(unsigned char (*ImgOrigin)[imagedeal_W]);
extern void PMCorrect(unsigned char (*ImgOrigin)[imagedeal_W] );//透视映射函数

#endif