#include "imageProcessPro.h"


//Ԥ�У������������޹أ�����
/*
uint16 preJudge_Direction(uint16 pJ_qishi)
{
    pJ_left=0,pJ_right=0,pJ_dat=0;
    for(int i=pJ_qishi;i<=48;i++)
    {
        if(blackRight[i]>(CAMERA_W-2)&&blackLeft[i]==0)
        {}
    }
}
//����Ч�У����������ұ�Ե������������
void getCenter()
{
    for(i=0;i<CAMERA_H;i++)//ͼ����Ĳ������г�ʼ��
    {}
    
    //�ҵ���ǰ2�е����ұ�Ե
    for(i=CAMERA_H-1;i>CAMERA_H-3;i--)
    {
        //�����
        for(j=CAMERA_W/2+10;j>1;j--)
        {
            if(img[i][j-1]==BLACK&&img[i][j]==BLACK&&img[i][j+1]==WHITE)//110
            {
                blackRight[i]=j;//�����1
            }
        }
        //���ұ�
        for(j=CAMERA_W/2-10;j<(CAMERA_H-1);j++)
        {
            if(img[i][j-1]==WHITE&&img[i][j]==BLACK&&img[i][j+1]==BLACK)//011
            {
                blackLeft[i]=j;//�����79
            }
        }
        //�õ��������ߣ�Ϊ��������ṩ�ο�
        if(blackLeft[i]>=2&&blackRight[i]<=78)//�ܱ�׼
        {
            center_Virtual[i]=(blackLeft+blackRight)/2;
        }
        else if(blackLeft[i]==1&&blackRight[i]<=78)//���δ�ҵ���ƫ��
        {
            center_Virtual[i]=0;//��ƫ&&�ޱ߽�����
        }
        else if(blackLeft[i]==1&&blackRight[i]<=78)//�ұ�δ�ҵ���ƫ��
        {
            center_Virtual[i]=80;//��ƫ&&�ޱ߽�����
        }
    }
    //��Զ���ο������ж����
    //��Ч�����ݴ���ʼ
    rightStart=blackRight[CAMERA_H-2]-3;
    rightEnd=blackRight[CAMERA_H-2]+3;
    leftStart=blackLeft[CAMERA_H-2]+3;
    leftEnd=blackLeft[CAMERA_H-2]-3;
    if(leftEnd<=0) 
        leftEnd=0;
    if(rightEnd>=CAMERA_W) 	
        rightEnd=CAMERA_W;
    
    //---->>>>>��ʼ����߽����Ч����
    //�ұ�
    for(i=CAMERA_H-3;i>=0;i--)
    {
        for(j=rightStart;j<rightEnd;j++)//find all right limit
        {
            if(rightEnd>=CAMERA_W)
                rightEnd=CAMERA_W;
            if(img[i][j-4]==WHITE&&img[i][j-1]==WHITE&&img[i][j]==BLACK&&img[i][j+1]==BLACK)//0111
            {
                blackRight[i]=j;
                rightStart=j-4;
                rightEnd=j+4;
                if(rightStart<=1) 	
                    rightStart=1;
                if(rightEnd>=CAMERA_W)
                    rightEnd=CAMERA_W;
                break;
            }
        }
    }
}



*/
















