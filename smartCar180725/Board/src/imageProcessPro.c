#include "imageProcessPro.h"


//预判，与最终中线无关！！！
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
//求有效行，并且求左右边缘，最终求中心
void getCenter()
{
    for(i=0;i<CAMERA_H;i++)//图像处理的参数进行初始化
    {}
    
    //找到最前2行的左右边缘
    for(i=CAMERA_H-1;i>CAMERA_H-3;i--)
    {
        //找左边
        for(j=CAMERA_W/2+10;j>1;j--)
        {
            if(img[i][j-1]==BLACK&&img[i][j]==BLACK&&img[i][j+1]==WHITE)//110
            {
                blackRight[i]=j;//最边是1
            }
        }
        //找右边
        for(j=CAMERA_W/2-10;j<(CAMERA_H-1);j++)
        {
            if(img[i][j-1]==WHITE&&img[i][j]==BLACK&&img[i][j+1]==BLACK)//011
            {
                blackLeft[i]=j;//最边是79
            }
        }
        //得到虚拟中线，为后面决策提供参考
        if(blackLeft[i]>=2&&blackRight[i]<=78)//很标准
        {
            center_Virtual[i]=(blackLeft+blackRight)/2;
        }
        else if(blackLeft[i]==1&&blackRight[i]<=78)//左边未找到，偏左
        {
            center_Virtual[i]=0;//左偏&&无边界特征
        }
        else if(blackLeft[i]==1&&blackRight[i]<=78)//右边未找到，偏右
        {
            center_Virtual[i]=80;//右偏&&无边界特征
        }
    }
    //最远处参考数据判断完毕
    //有效行数据处理开始
    rightStart=blackRight[CAMERA_H-2]-3;
    rightEnd=blackRight[CAMERA_H-2]+3;
    leftStart=blackLeft[CAMERA_H-2]+3;
    leftEnd=blackLeft[CAMERA_H-2]-3;
    if(leftEnd<=0) 
        leftEnd=0;
    if(rightEnd>=CAMERA_W) 	
        rightEnd=CAMERA_W;
    
    //---->>>>>开始计算边界和有效行数
    //右边
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
















