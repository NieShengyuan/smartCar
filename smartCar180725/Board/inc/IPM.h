#ifndef _IPM_H
#define _IPM_H

#define imagedeal_W       80
#define imagedeal_H       60

extern Site_t IPMCorr[imagedeal_H][imagedeal_W];   //͸�ӱ任ӳ���
extern Site_t PMCorr[imagedeal_H][imagedeal_W];    //��͸�ӱ任ӳ���
extern Site_t BuketCorr[imagedeal_H][imagedeal_W]; //Ͱ�ν���ӳ���
extern unsigned char CorrImg[imagedeal_H][imagedeal_W]; //������ͼ������

extern void BuketCorrInit( float k1, float k2 );
extern void PMCorrInit(void) ;//��͸�ӱ任��ʼ��������ӳ���
extern void IPMCorrInit(void);//��͸��ӳ���
extern void BuketCorrect(unsigned char (*ImgOrigin)[imagedeal_W]);
extern void PMCorrect(unsigned char (*ImgOrigin)[imagedeal_W] );//͸��ӳ�亯��

#endif