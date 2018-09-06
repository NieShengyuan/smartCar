#include "common.h"
#include "include.h"
#include "imageProcess.h"

//////////////////////////////////////////////

//#define d_outcircleGiveValue_Right 16
//#define d_inCircleValueR 23

////////////////障碍物参数/////////////////////
#define obstaclesL (-9)
#define obstaclesR (2)
void testImg()
{
    getCenter();
}

/*************************************************************************
*  函数名称：getCenter
*  功能说明：对ROW（50）到10行数据跟边
*  参数说明：无
*  输出参数：每行左边界，中心值，右边界
*  修改时间：2018-6-17    
*************************************************************************/
void getCenter()
{//图像跟边，得出的数据后续处理
    int i,j,m;
    
    //数据初始化
    for(i=0;i<60;i++)
    {
        getOneSideResultL[i]=black_left[i]=black_leftP[i]=0;
        getOneSideResultR[i]=black_right[i]=black_rightP[i]=CAMERA_W-1;
        center_virtual[i]=center[i]=CAMERA_W/2;
        
        center_virtual_left[i]=center_virtual_right[i]=CAMERA_W/2;
        center_preJudge[i]=center_preJudge_left[i]=center_preJudge_right[i]=0;
    }
    lostLeftPos=lostRightPos=0;
    lostLeftNum=lostRightNum=0;
    topLostPos=0;
    lostStartPos=lostEndPos=0;
    lostLimitFlag=0;
    turnPointPosLeft=turnPointPosRight=turnPointNumLeft=turnPointNumRight=0;
    bTw=0;
    toLeftNum=toRightNum=0;
    //get 参考边缘
    i=ROW+1;//
    for(j=CAMERA_W/2+20;j>1;j--)
    {
        if(img[i][j-1]==BLACK && img[i][j] == BLACK && img[i][j+1]==WHITE)//1100
        {
            black_left[i]=j;break;
        } 
    }
    for(j=CAMERA_W/2-20;j<CAMERA_W-1;j++)//0011
    {
        if(img[i][j-1]==WHITE && img[i][j] == WHITE && img[i][j+1]==BLACK)
        {
            black_right[i]=j;break;
        } 
    }
    //对基准数据作出修改
    
    if(black_left[i]==0 && black_right[i]==CAMERA_W-1)
    {
        i=rowEnd-1;
        for(j=CAMERA_W/2+10;j>1;j--)
        {
            if(img[i][j-1]==BLACK && img[i][j] == BLACK && img[i][j+1]==WHITE)//1100
            {
                black_left[i]=j;break;
            } 
        }
        for(j=CAMERA_W/2-10;j<CAMERA_W-1;j++)//0011
        {
            if(img[i][j-1]==WHITE && img[i][j] == WHITE && img[i][j+1]==BLACK)
            {
                black_right[i]=j;break;
            } 
        }
    }
    //对基准数据作出评价
    CENTER_virtual=center_virtual[i]=(black_left[i]+black_right[i])/2;
    
    //基准搜索结束
    //---------------------------确定搜索起始点----------------------------------------
    left_start=center_virtual[i];
    left_end=0;
    right_start=center_virtual[i];
    right_end=79;
    
    for(i=ROW;i>10;i-=1)//15
    {
        //找左边
        for(j=left_start;j>left_end;j--)//10X0
        {
            if(img[i][j]==BLACK && img[i][j+1] == WHITE && img[i][j+3]==WHITE)
            {//找到左边界
                black_left[i]=j;
                leftPosGetFlag=1;
                break;
            }  
        }
        
        //找右边
        for(j=right_start;j<right_end;j++)//0X01
        {
            if(img[i][j-3]==WHITE && img[i][j-1] == WHITE && img[i][j]==BLACK)
            {//
                black_right[i]=j;
                rightPosGetFlag=1;
                break;
            }
        }
        
        if(black_left[i]>=5 && black_right[i]<=74)//两边都找得到0-79
        {
            center_virtual[i]=(black_left[i]+black_right[i])/2;
        }
        //左边丢线
        else if(black_left[i]<5 && black_right[i]<74)
        {
            //get丢边坐标和丢边数量
            if(black_right[i]-half_Width_deal>0)
            {
                center_virtual[i]=black_right[i]-half_Width_deal;
            }
            else 
            {
                center_virtual[i]=0;
            }
            
            //lostLimitFlagLeft=1;//丢线标志
        }
        //右边丢线
        else if(black_left[i]>5 && black_right[i]>74)
        {
            //get丢边坐标和丢边数量
            if(black_left[i]+half_Width_deal<79)
            {
                center_virtual[i]=black_left[i]+half_Width_deal;
            }
            else 
            {
                center_virtual[i]=79;
            }
            //lostLimitFlagRight=1;//丢线标志
        }
        
        //对丢边做出评价
        //以上一个中心
        left_start=center_virtual[i];
        left_end=0;
        right_start=center_virtual[i];
        right_end=79;
    }
    
    
    //-------------------------------------------------------------------------------------------------------------------- 
    centureOut();
    showImgData(); 
    
}

//----------------------------------------------
//对中心的评价，到底是直接改变中心值好，还是补线再计算
//----------------------------------------------
void centureOut()
{
    turnPointNumLeft=getLostSideNum(ROW,getRowStart,'L');
    turnPointNumRight=getLostSideNum(ROW,getRowStart,'R');
    
    //最前边标志行
    //20左右最好
    turnPointPos_StartLeft=getLostSideStartRow(turnPointPosLeft,'L');//getSide_forHorizontal(ROW,10,'L');//
    turnPointPos_StartRight=getLostSideStartRow(turnPointPosRight,'R');//getSide_forHorizontal(ROW,10,'R');//
    
    if('A'==Fn[1])//数据显示
    {
        //Display_2_1(turnPointNumLeft,80,0);
        //Display_2_1(turnPointNumRight,100,0);
        
        
        //Display_2_1(turnPointPos_StartLeft,80,2);
        //Display_2_1(turnPointPos_StartRight,100,2);
        
        //Display_2_1(black_right[45]-black_left[45],80,4);
        //Display_2_1(black_right[45]-black_right[44],100,4);
        //Display_2_1(turnPointPosRight,100,4);
        //Display_2_0(toRightLineNum(Rnum,45,'L'),80,6);
        Display_2_1(Rnum,110,6);
        
        for(int j=40;j<60;j+=2)
        {
            imgAddDot(turnPointPos_StartLeft,j,0);
        }
        for(int j=40;j<80;j++)
        {
            imgAddDot(turnPointPosLeft,j,0);
        }
        for(int j=40;j>20;j-=2)
        {
            imgAddDot(turnPointPos_StartRight,j,0);
        }
        for(int i=60;i>0;i--)
        {
            imgAddDot(i,getOneSideResultL[i]+2,0);//圆环
        }
    }
    
    //------------------------------------搜边完成-----------------------------------------------
    
    if(turnPointNumLeft>3 && turnPointNumRight<3)//左拐
    {
        //PTD5_OUT=1;
        Fn[0]='L';
        PTB23_OUT= 0;//PTB20_OUT= 1;
    }
    else if(turnPointNumLeft<3 && turnPointNumRight>3)//右拐
    {
        Fn[0]='R';        
        //PTD5_OUT=1;
        PTB20_OUT= 0;//PTB23_OUT= 1;
    }
    else if(turnPointNumLeft<3 && turnPointNumRight<3)
    {
        Fn[0]='S';
        //中心原本在一条线上，发生突变则为障碍物
        PTB23_OUT= 1;PTB20_OUT= 1;   // PTD5_OUT=0;
    }
    ////////////////////////弯道处理///////////////////////////////////////
    
    if('L'==Fn[0] || 'R'==Fn[0])
    {
        centure=0;
        for(int i=getRowStartW+10;i>getRowStartW;i--)//Rnum
        { 
            centure+=center_virtual[i];
        }
        centure/=10;//PTD5_OUT=1;
    }
    else 
    {
        centure=0;
        for(int i=rowEnd;i>rowEnd-10;i--)
        {
            centure+=center_virtual[i];
        }
        centure/=10;//PTD5_OUT=0;
    }
    ///////////////////////////////圆环处理///////////////////////////////////////
    if(circleEnable=='O')
    {
        dealCircle();
    }
    
    //    if(obstaclesEnable=='O')
    //    {
    //        //getObstacles();//自带避障属性
    //    }
    
    ////////////////////////////对弯道时赛车在外圈时作出评价////////////////////////////////
    
    if(black_right[30]<40&& Fn[0]=='L' 
       )//|| getLostSideNum(ROW,getRowStart,'L')>(ROW-getRowStart-2) && getLostSideNum(ROW,getRowStart,'R')==0)//25弯道补偿幅度-<修改此处防止弯道冲出>-
    {
        centure-=WanDaoLAdd;//PTD5_OUT=1;
    }
    else if(black_left[30]>40 && Fn[0]=='R'
            )//|| getLostSideNum(ROW,getRowStart,'L')==0 && getLostSideNum(ROW,getRowStart,'R')>(ROW-getRowStart-2))//25弯道补偿幅度-<修改此处防止弯道冲出>-
    {
        centure+=WanDaoRAdd;//PTD5_OUT=1;//25
    }
    
    
    servoPwmOut((int16)(CENTURE+2- centure));//1//obstaclesErr//-4
}
///////////////////////////////圆环处理方法：条件逐步逼近/////////////////////////////////////
//检测进圆环 circleTo_Left_Flag=1  circleTo_Left_Flag1Num=30
//延时进入圆环 circleTo_Left_Flag=2  持续检测右边线并补线
//再次检测到  circleTo_Left_Flag=3   circleTo_Left_Flag2Num=60  补线保持不进入圆环
void dealCircle()
{  
    int resu;
    if(turnPointNumLeft>8 && turnPointNumRight<8 //丢边特征(弯道圆环等)Rnum
       //0725---15-->
       && getLineInfo('L')==1 && absGet(black_right[getRowStart]-60)<20 && absGet(black_right[getRowStart+2]-60)<20//直线度特征与15
           && toTurnLineNum(18,45,'L')<(-2) //最重要特征    
               )
    {
        //printf("%d<<<\n",toTurnLineNum(18,45,'L'));//此处值的大小可以判断出圆环的大小
        //PTD5_OUT=1;//确认是左环
        if(circleTo_Left_Flag==0)
        {
            Fn[4]='L';
            circleTo_Left_Flag=1;//进圆环标志
            circleTo_Left_Flag1Num=20;
        }
        //第二次看到，准备出环
        else if(circleTo_Left_Flag==2)
        {
            circleTo_Left_Flag=3;//出圆环标志
            circleTo_Left_Flag2Num=40;
        }
        
    }
    else if(turnPointNumLeft<8 && turnPointNumRight>10 && getLineInfo('R')==2//取消右环识别 
            && absGet(black_left[getRowStart]-30)<20 && absGet(black_left[getRowStart+2]-30)<20//直线度特征
                && toTurnLineNum(18,45,'R')<(-2)
                    )
    {
        if(circleTo_Right_Flag==0)
        {
            PTD5_OUT=1;
            //printf("%d>>>\n",toTurnLineNum(18,45,'R'));
            Fn[4]='R';//
            circleTo_Right_Flag=1;//进圆环标志
            circleTo_Right_Flag1Num=20;
        }
        //第二次看到，准备出环
        else if(circleTo_Right_Flag==2)
        {
            circleTo_Right_Flag=3;//出圆环标志
            circleTo_Right_Flag2Num=40;
        }
        
    }
    
    ///////////////////////入圆环过程延迟补线//随时在圆环补线///////////////////////
    if(Fn[4]=='L' || circleTo_Left_Flag==1)
    {
        centure=0;
        for(int i=28;i>18;i--)
        {
            if(black_left[i]>40)  black_left[i]=10;
            if(black_left[i]<5 && black_right[i]<74)
            {
                //get丢边坐标和丢边数量
                center_virtual[i]=black_left[i]+d_inCircleValueL;//入弯系数
            }
            else
                center_virtual[i]= (black_right[i]+black_left[i])/2;
            centure+=center_virtual[i];
        }
        centure/=10;
    }
    if(Fn[4]=='R' || circleTo_Right_Flag==100)
    {
        centure=0;
        for(int i=28;i>18;i--)
        {
            if(black_right[i]<60)  black_right[i]=70;
            if(black_left[i]>5 && black_right[i]>74)
            {
                //get丢边坐标和丢边数量
                center_virtual[i]=black_right[i]-Rnum;//d_inCircleValueR;//入弯系数d_inCircleValueR
            }
            else
                center_virtual[i]= (black_right[i]+black_left[i])/2;
            centure+=center_virtual[i];        
        }
        centure/=10;
        
    }//条件不成立时认为进入圆环
    
    
    ////////////////////圆环进入成功,进入持续检测出环口并补线状态/////////////
    if(circleTo_Left_Flag1Num==0 && circleTo_Left_Flag==1)
    {
        circleTo_Left_Flag=2;//成为等待出圆环状态
    }
    if(circleTo_Right_Flag1Num==0 && circleTo_Right_Flag==1)
    {
        circleTo_Right_Flag=2;//成为等待出圆环状态
    }
    //////////////////随时出圆环补线出去////////////////////////
    if(circleTo_Left_Flag==2)
    {
        centure=0;
        for(int i=32;i>22;i--)
        {
            if(black_right[i]-black_left[i]>half_Width[i]*2+15)//认为不合规范,出口？
            {
                black_right[i]=black_left[i]+half_Width[i]*2+d_outcircleGiveValue_Left;//在出口补线
                
            }
            center_virtual[i]= (black_right[i]+black_left[i])/2;
            centure+=center_virtual[i];
        }
        centure/=10;
        //printf("2-right bxz\n");
    } 
    //////////////////随时出圆环补线出去////////////////////////
    if(circleTo_Right_Flag==2)
    {
        centure=0;
        for(int i=32;i>22;i--)
        {
            if(black_right[i]-black_left[i]>half_Width[i]*2+15)//认为不合规范,出口？
            {
                black_left[i]=black_right[i]-half_Width[i]*2-d_outcircleGiveValue_Left;//在出口补线
                
            }
            center_virtual[i]= (black_right[i]+black_left[i])/2;
            centure+=center_virtual[i];
        }
        centure/=10;
        //printf("2-right bxz\n");
    } 
    ///////////////////////出圆环状态结束,入口补线直行///////////////////////
    if(circleTo_Left_Flag==3 || circleTo_Left_Flag2Num>0)
    {
        centure=0;
        for(int i=28;i>18;i--)
        {
            black_left[i]=black_right[i]-half_Width[i]*2;
            center_virtual[i]= (black_right[i]+black_left[i])/2;
            centure+=center_virtual[i];
        }
        centure/=10;
        
    }
    if(circleTo_Right_Flag==3 || circleTo_Right_Flag2Num>0)//出圆环状态结束,入口补线直行
    {
        centure=0;
        for(int i=28;i>18;i--)
        {
            black_right[i]=black_left[i]+half_Width[i]*2;
            center_virtual[i]= (black_right[i]+black_left[i])/2;
            centure+=center_virtual[i];
        }
        centure/=10;
        
    }
    if(circleTo_Left_Flag==3 && circleTo_Left_Flag2Num==0)//出圆环状态结束,直行
    {
        circleTo_Left_Flag=0;//出圆环完成
        //printf("\noutCircle<%d>\n",centure);
        Fn[4]='S';
        //centure=40;
    }
    if(circleTo_Right_Flag==3 && circleTo_Right_Flag2Num==0)//出圆环状态结束,直行
    {
        circleTo_Right_Flag=0;//出圆环完成
        //printf("\noutCircle<%d>\n",centure);
        Fn[4]='S';
        //centure=40;
    }
    
    if(circleTo_Left_Flag>0 || circleTo_Left_Flag>0)
    {
        PTD5_OUT=1;
    }
    else
        PTD5_OUT=0;
    
    if(circleTo_Left_Flag1Num>0 )
    {
        circleTo_Left_Flag1Num--;
        //printf("--%d--\n",circleTo_Left_Flag);
    }
    if(circleTo_Left_Flag2Num>0 )
    {
        circleTo_Left_Flag2Num--;
        //printf("--%d--\n",circleTo_Left_Flag);
    }
    if(circleTo_Right_Flag1Num>0 )
    {
        circleTo_Right_Flag1Num--;
        //printf("--%d--\n",circleTo_Left_Flag);
    }
    if(circleTo_Right_Flag2Num>0 )
    {
        circleTo_Right_Flag2Num--;
        //printf("--%d--\n",circleTo_Left_Flag);
    }
    
}

int followOneside(char dir)
{
    //由圆环条件触发，输入方向，输出重新搜线后的顶底值（按单边趋势搜索，0或79截止）
    //边界数据保存在getOneSideResult[60]
    if('L'==dir)//leftCircle
    {
        int j=40;
        
        for(;j>0;j--)
        {
            if(img[46][j+2]==WHITE && img[46][j+1]==WHITE && img[46][j]==BLACK)//100
            {
                getOneSideResultL[46]=j;
                break;
            }
        }
        if(getOneSideResultL[46]<4)
        {
            getOneSideResultL[46]=0;
        }
        j=20;
        
        for(int i=45;i>20;i--)//找边缘
        {
            for(;j>0;j--)
            {
                if(img[i][j+2]==WHITE && img[i][j+1]==WHITE && img[i][j]==BLACK)//100
                {
                    getOneSideResultL[i]=j;
                    break;
                }
            }
            if(getOneSideResultL[46]<4)
            {
                j=getOneSideResultL[i]+15;//下次的数据是上次的偏移一定值
            }
            else
            {
                return i;break;
            }
        }
    }
}


int getLostTopPosition(char dir)
{
    //对虚拟中线向上搜索，考虑到虚拟中线偏至一个方向，且在30行以下会使单片机认为是中心
    //也使用于转弯时的补偿
    int tt;
    if('L'==dir)
    {
        for(int i=45;i>20;i--)
        {
            if(center_virtual[i]<5)
            {
                tt=i;//找到中线偏向最左边的极限
                break;
            }
        }
        return tt;
    }
    else if('R'==dir)
    {
        for(int i=45;i>20;i--)
        {
            if(center_virtual[i]>75)
            {
                tt=i;//找到中线偏向最左边的极限
                break;
            }
        }
        return tt;
    }
}


////////////////////////////对边线类型作出评价//////////////////////////////////
//类直线返回1
//yuanhuan
int getLineInfo(char dir)
{
    int t=0;
    if('L'==dir)
    {
        if(absGet(black_right[ROW]-black_right[getRowStart])<35//边沿直线倾斜度35
           && ((black_right[(int)(ROW/2-getRowStart/2)]-black_right[getRowStart])-(black_right[ROW]-black_right[(int)(ROW/2-getRowStart/2)]))<24//20  absGet
               //&&((black_right[(int)(ROW/2-getRowStart/2)]-black_right[getRowStart]) >= (black_right[ROW]-black_right[(int)(ROW/2-getRowStart/2)])*0.8)
               //&&((black_right[(int)(ROW/2-getRowStart/2)]-black_right[getRowStart]) <= (black_right[ROW]-black_right[(int)(ROW/2-getRowStart/2)])*1.3)
               )
        {
            //继续加限制条件
            for(int i=46;i>18;i--)//右边往右偏
            {
                if(black_right[i-1]>black_right[i]+2)
                    t++;
            }
            //printf("t<%d>\n",t);
            if(t>2)
                return 0;
            else
                return 1;
            
        }
        
    }
    else if('R'==dir)
    {
        if(((black_left[getRowStart]-black_left[ROW])<35) && ((black_left[getRowStart]-black_left[ROW])>0)//边沿直线倾斜度35
           && ((black_left[getRowStart]-black_left[(int)(ROW/2-getRowStart/2)])-(black_left[(int)(ROW/2-getRowStart/2)]-black_left[ROW]))<20//20
               )
        {
            for(int i=46;i>18;i--)//zuo边往zuo偏
            {
                if(black_left[i]>black_left[i-1]+2)
                    t++;
            }
            //printf("t<%d>\n",t);
            if(t>2)
                return 0;
            else
                return 1;
        }
    }
}
int toTurnLineNum(int st,int fi,char dir)
{
    int t=0;
    if('L'==dir)
    {
        for(int i=fi;i>st;i--)
        {
            if((black_left[i-1]-black_left[i])>0)
            {
                t++;//turn right
            }
            else if((black_left[i-1]-black_left[i])<0)
            {
                t--;
            }
        }
        return t;
    }
    else if('R'==dir)
    {
        for(int i=fi;i>st;i--)
        {
            if((black_right[i]-black_right[i-1])>0)
            {
                t++;//turn right
            }
            else if((black_right[i]-black_right[i-1])<0)
            {
                t--;
            }
        }
        return t;
    }
}

//得出指定区间丢边数量指定区间（以基准行46数据为边界）
//输出数据-turnPointNumLeft,turnPointNumRight
int getLostSideNum(int startL,int finshL,char dir)//46-10
{
    //get 46-10的丢边数量
    int tpnL=0,tpnR=0;
    if('L'==dir)//确保不在边上
    {
        for(int i=startL;i>finshL;i--)
        {
            if(img[i][black_left[ROW]]==WHITE && img[i-1][black_left[ROW]]==WHITE)
                tpnL++;
            else if(img[i][black_left[ROW]]==WHITE && img[i-1][black_left[ROW]]==BLACK)
                break;
        }
        return tpnL;
    }
    else if('R'==dir)
    {
        for(int i=startL;i>finshL;i--)
        {
            if(img[i][black_right[ROW]]==WHITE && img[i-1][black_right[ROW]]==WHITE)
                tpnR++;
            else if(img[i][black_right[ROW]]==WHITE && img[i-1][black_right[ROW]]==BLACK)
                break;
        }
        return tpnR;
    } 
}
//传入数据为丢边最底层行和方向，计算出起始行
//输出到边界topLostPos =getLostSideStartRow()
int getLostSideStartRow(int startL,char dir)
{
    int tlp=0;
    //getSide_forHorizontal(ROW,10,dir);
    if('L'==dir)
    {
        int lp=black_right[ROW]-44;
        if(lp<0)  lp=0;
        for(int i=ROW;i>8;i--)
        {
            if(img[i][lp]==WHITE && img[i-1][lp]==BLACK )//0011
            {
                tlp=i;break;
            }
        }
        return tlp;
    }
    else if('R'==dir)
    {
        int lp=black_left[ROW]+44;
        if(lp>79)  lp=79;
        for(int i=ROW;i>8;i--)
        {
            if(img[i][lp]==WHITE && img[i-1][lp]==BLACK )//0011
            {
                tlp=i;break;
            }
        }
        return tlp;
    }
}

void showImgData()
{
    if(Fn[2]=='A')//switch5
    {
        for(int i=0;i<80;i+=2)//横线
        {
            imgAddDot(9,i,0);//最远处
            //imgAddDot(lostStartPos,i,0);//最远处
            //imgAddDot(lostEndPos,i,0);//最远处
            //imgAddDot(incision_right_row,i,0);//
            imgAddDot(Rnum,i,0);//
            imgAddDot(29,i,0);
            imgAddDot(45,i,0);
            /*imgAddDot(10-1,i,0);
            imgAddDot(20-1,i,0);
            imgAddDot(30-1,i,0);
            imgAddDot(40-1,i,0);
            imgAddDot(50-1,i,0);*/
        }
        for(int i=0;i<60;i+=1)//竖线
        {//识别的边线和中线
            
            imgAddDot(i,black_left[i]+2,0);
            imgAddDot(i,center_virtual[i],0);
            imgAddDot(i,black_right[i]-2,0);
            imgAddDot(i,black_left[ROW+1],0);//丢边范围
            imgAddDot(i,black_right[ROW-1],0);
            imgAddDot(i,Rnum,0);
            /*imgAddDot(i,10-1,0);
            imgAddDot(i,20-1,0);
            imgAddDot(i,30-1,0);
            imgAddDot(i,40-1,0);
            imgAddDot(i,50-1,0);
            imgAddDot(i,60-1,0);
            imgAddDot(i,70-1,0);*/
        }
    }
    
    //oled_Show_Data(pag);  
}

//---------------------------------------------------------------------------------

int getSlope(int a,int b,int h)//斜率计算
{
    return (int)(a-b)/h;
}
int absGet(int16 a)
{
    if(a>=0)
        return a;
    else
        return -a;
}
void curveFitting(char cf)//曲线拟合
{
    switch(cf)
    {
        case 'L':{};break;//直道
        case 'B':{};break;//障碍
        case 'R':{};break;//弯道
        case 'C':{};break;//圆环
        case 'A':{};break;//十字
        default:break;
    }
}



//================///==============///=================///============///=============//
void imgAddDot(int h,int w,int a)//找中线时画点函数
{
    if(0==a)
    {
        if(BLACK==img[h][w])
            img[h][w]=WHITE;
        else
            img[h][w]=BLACK;
    }
    else if(1==a)
    {
        if(BLACK==CorrImg[h][w])
            CorrImg[h][w]=WHITE;
        else
            CorrImg[h][w]=BLACK;
    }
}

void imgAddLine()
{    
    for(int j=0;j<80;j=j+1)
    {
        if(BLACK==img[3][j])
            img[3][j]=WHITE;
        else
            img[3][j]=BLACK;
        
        if(BLACK==img[30][j])
            img[30][j]=WHITE;
        else
            img[30][j]=BLACK;
        
        if(BLACK==img[50][j])
            img[50][j]=WHITE;
        else
            img[50][j]=BLACK;
    }
    for(int j=0;j<50;j=j+1)
    {
        if(BLACK==img[j][20])
            img[j][20]=WHITE;
        else
            img[j][20]=BLACK;
        
        if(BLACK==img[j][50])
            img[j][50]=WHITE;
        else
            img[j][50]=BLACK;
    }
}

