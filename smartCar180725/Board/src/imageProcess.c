#include "common.h"
#include "include.h"
#include "imageProcess.h"

//////////////////////////////////////////////

//#define d_outcircleGiveValue_Right 16
//#define d_inCircleValueR 23

////////////////�ϰ������/////////////////////
#define obstaclesL (-9)
#define obstaclesR (2)
void testImg()
{
    getCenter();
}

/*************************************************************************
*  �������ƣ�getCenter
*  ����˵������ROW��50����10�����ݸ���
*  ����˵������
*  ���������ÿ����߽磬����ֵ���ұ߽�
*  �޸�ʱ�䣺2018-6-17    
*************************************************************************/
void getCenter()
{//ͼ����ߣ��ó������ݺ�������
    int i,j,m;
    
    //���ݳ�ʼ��
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
    //get �ο���Ե
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
    //�Ի�׼���������޸�
    
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
    //�Ի�׼������������
    CENTER_virtual=center_virtual[i]=(black_left[i]+black_right[i])/2;
    
    //��׼��������
    //---------------------------ȷ��������ʼ��----------------------------------------
    left_start=center_virtual[i];
    left_end=0;
    right_start=center_virtual[i];
    right_end=79;
    
    for(i=ROW;i>10;i-=1)//15
    {
        //�����
        for(j=left_start;j>left_end;j--)//10X0
        {
            if(img[i][j]==BLACK && img[i][j+1] == WHITE && img[i][j+3]==WHITE)
            {//�ҵ���߽�
                black_left[i]=j;
                leftPosGetFlag=1;
                break;
            }  
        }
        
        //���ұ�
        for(j=right_start;j<right_end;j++)//0X01
        {
            if(img[i][j-3]==WHITE && img[i][j-1] == WHITE && img[i][j]==BLACK)
            {//
                black_right[i]=j;
                rightPosGetFlag=1;
                break;
            }
        }
        
        if(black_left[i]>=5 && black_right[i]<=74)//���߶��ҵõ�0-79
        {
            center_virtual[i]=(black_left[i]+black_right[i])/2;
        }
        //��߶���
        else if(black_left[i]<5 && black_right[i]<74)
        {
            //get��������Ͷ�������
            if(black_right[i]-half_Width_deal>0)
            {
                center_virtual[i]=black_right[i]-half_Width_deal;
            }
            else 
            {
                center_virtual[i]=0;
            }
            
            //lostLimitFlagLeft=1;//���߱�־
        }
        //�ұ߶���
        else if(black_left[i]>5 && black_right[i]>74)
        {
            //get��������Ͷ�������
            if(black_left[i]+half_Width_deal<79)
            {
                center_virtual[i]=black_left[i]+half_Width_deal;
            }
            else 
            {
                center_virtual[i]=79;
            }
            //lostLimitFlagRight=1;//���߱�־
        }
        
        //�Զ�����������
        //����һ������
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
//�����ĵ����ۣ�������ֱ�Ӹı�����ֵ�ã����ǲ����ټ���
//----------------------------------------------
void centureOut()
{
    turnPointNumLeft=getLostSideNum(ROW,getRowStart,'L');
    turnPointNumRight=getLostSideNum(ROW,getRowStart,'R');
    
    //��ǰ�߱�־��
    //20�������
    turnPointPos_StartLeft=getLostSideStartRow(turnPointPosLeft,'L');//getSide_forHorizontal(ROW,10,'L');//
    turnPointPos_StartRight=getLostSideStartRow(turnPointPosRight,'R');//getSide_forHorizontal(ROW,10,'R');//
    
    if('A'==Fn[1])//������ʾ
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
            imgAddDot(i,getOneSideResultL[i]+2,0);//Բ��
        }
    }
    
    //------------------------------------�ѱ����-----------------------------------------------
    
    if(turnPointNumLeft>3 && turnPointNumRight<3)//���
    {
        //PTD5_OUT=1;
        Fn[0]='L';
        PTB23_OUT= 0;//PTB20_OUT= 1;
    }
    else if(turnPointNumLeft<3 && turnPointNumRight>3)//�ҹ�
    {
        Fn[0]='R';        
        //PTD5_OUT=1;
        PTB20_OUT= 0;//PTB23_OUT= 1;
    }
    else if(turnPointNumLeft<3 && turnPointNumRight<3)
    {
        Fn[0]='S';
        //����ԭ����һ�����ϣ�����ͻ����Ϊ�ϰ���
        PTB23_OUT= 1;PTB20_OUT= 1;   // PTD5_OUT=0;
    }
    ////////////////////////�������///////////////////////////////////////
    
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
    ///////////////////////////////Բ������///////////////////////////////////////
    if(circleEnable=='O')
    {
        dealCircle();
    }
    
    //    if(obstaclesEnable=='O')
    //    {
    //        //getObstacles();//�Դ���������
    //    }
    
    ////////////////////////////�����ʱ��������Ȧʱ��������////////////////////////////////
    
    if(black_right[30]<40&& Fn[0]=='L' 
       )//|| getLostSideNum(ROW,getRowStart,'L')>(ROW-getRowStart-2) && getLostSideNum(ROW,getRowStart,'R')==0)//25�����������-<�޸Ĵ˴���ֹ������>-
    {
        centure-=WanDaoLAdd;//PTD5_OUT=1;
    }
    else if(black_left[30]>40 && Fn[0]=='R'
            )//|| getLostSideNum(ROW,getRowStart,'L')==0 && getLostSideNum(ROW,getRowStart,'R')>(ROW-getRowStart-2))//25�����������-<�޸Ĵ˴���ֹ������>-
    {
        centure+=WanDaoRAdd;//PTD5_OUT=1;//25
    }
    
    
    servoPwmOut((int16)(CENTURE+2- centure));//1//obstaclesErr//-4
}
///////////////////////////////Բ���������������𲽱ƽ�/////////////////////////////////////
//����Բ�� circleTo_Left_Flag=1  circleTo_Left_Flag1Num=30
//��ʱ����Բ�� circleTo_Left_Flag=2  ��������ұ��߲�����
//�ٴμ�⵽  circleTo_Left_Flag=3   circleTo_Left_Flag2Num=60  ���߱��ֲ�����Բ��
void dealCircle()
{  
    int resu;
    if(turnPointNumLeft>8 && turnPointNumRight<8 //��������(���Բ����)Rnum
       //0725---15-->
       && getLineInfo('L')==1 && absGet(black_right[getRowStart]-60)<20 && absGet(black_right[getRowStart+2]-60)<20//ֱ�߶�������15
           && toTurnLineNum(18,45,'L')<(-2) //����Ҫ����    
               )
    {
        //printf("%d<<<\n",toTurnLineNum(18,45,'L'));//�˴�ֵ�Ĵ�С�����жϳ�Բ���Ĵ�С
        //PTD5_OUT=1;//ȷ������
        if(circleTo_Left_Flag==0)
        {
            Fn[4]='L';
            circleTo_Left_Flag=1;//��Բ����־
            circleTo_Left_Flag1Num=20;
        }
        //�ڶ��ο�����׼������
        else if(circleTo_Left_Flag==2)
        {
            circleTo_Left_Flag=3;//��Բ����־
            circleTo_Left_Flag2Num=40;
        }
        
    }
    else if(turnPointNumLeft<8 && turnPointNumRight>10 && getLineInfo('R')==2//ȡ���һ�ʶ�� 
            && absGet(black_left[getRowStart]-30)<20 && absGet(black_left[getRowStart+2]-30)<20//ֱ�߶�����
                && toTurnLineNum(18,45,'R')<(-2)
                    )
    {
        if(circleTo_Right_Flag==0)
        {
            PTD5_OUT=1;
            //printf("%d>>>\n",toTurnLineNum(18,45,'R'));
            Fn[4]='R';//
            circleTo_Right_Flag=1;//��Բ����־
            circleTo_Right_Flag1Num=20;
        }
        //�ڶ��ο�����׼������
        else if(circleTo_Right_Flag==2)
        {
            circleTo_Right_Flag=3;//��Բ����־
            circleTo_Right_Flag2Num=40;
        }
        
    }
    
    ///////////////////////��Բ�������ӳٲ���//��ʱ��Բ������///////////////////////
    if(Fn[4]=='L' || circleTo_Left_Flag==1)
    {
        centure=0;
        for(int i=28;i>18;i--)
        {
            if(black_left[i]>40)  black_left[i]=10;
            if(black_left[i]<5 && black_right[i]<74)
            {
                //get��������Ͷ�������
                center_virtual[i]=black_left[i]+d_inCircleValueL;//����ϵ��
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
                //get��������Ͷ�������
                center_virtual[i]=black_right[i]-Rnum;//d_inCircleValueR;//����ϵ��d_inCircleValueR
            }
            else
                center_virtual[i]= (black_right[i]+black_left[i])/2;
            centure+=center_virtual[i];        
        }
        centure/=10;
        
    }//����������ʱ��Ϊ����Բ��
    
    
    ////////////////////Բ������ɹ�,��������������ڲ�����״̬/////////////
    if(circleTo_Left_Flag1Num==0 && circleTo_Left_Flag==1)
    {
        circleTo_Left_Flag=2;//��Ϊ�ȴ���Բ��״̬
    }
    if(circleTo_Right_Flag1Num==0 && circleTo_Right_Flag==1)
    {
        circleTo_Right_Flag=2;//��Ϊ�ȴ���Բ��״̬
    }
    //////////////////��ʱ��Բ�����߳�ȥ////////////////////////
    if(circleTo_Left_Flag==2)
    {
        centure=0;
        for(int i=32;i>22;i--)
        {
            if(black_right[i]-black_left[i]>half_Width[i]*2+15)//��Ϊ���Ϲ淶,���ڣ�
            {
                black_right[i]=black_left[i]+half_Width[i]*2+d_outcircleGiveValue_Left;//�ڳ��ڲ���
                
            }
            center_virtual[i]= (black_right[i]+black_left[i])/2;
            centure+=center_virtual[i];
        }
        centure/=10;
        //printf("2-right bxz\n");
    } 
    //////////////////��ʱ��Բ�����߳�ȥ////////////////////////
    if(circleTo_Right_Flag==2)
    {
        centure=0;
        for(int i=32;i>22;i--)
        {
            if(black_right[i]-black_left[i]>half_Width[i]*2+15)//��Ϊ���Ϲ淶,���ڣ�
            {
                black_left[i]=black_right[i]-half_Width[i]*2-d_outcircleGiveValue_Left;//�ڳ��ڲ���
                
            }
            center_virtual[i]= (black_right[i]+black_left[i])/2;
            centure+=center_virtual[i];
        }
        centure/=10;
        //printf("2-right bxz\n");
    } 
    ///////////////////////��Բ��״̬����,��ڲ���ֱ��///////////////////////
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
    if(circleTo_Right_Flag==3 || circleTo_Right_Flag2Num>0)//��Բ��״̬����,��ڲ���ֱ��
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
    if(circleTo_Left_Flag==3 && circleTo_Left_Flag2Num==0)//��Բ��״̬����,ֱ��
    {
        circleTo_Left_Flag=0;//��Բ�����
        //printf("\noutCircle<%d>\n",centure);
        Fn[4]='S';
        //centure=40;
    }
    if(circleTo_Right_Flag==3 && circleTo_Right_Flag2Num==0)//��Բ��״̬����,ֱ��
    {
        circleTo_Right_Flag=0;//��Բ�����
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
    //��Բ���������������뷽������������ߺ�Ķ���ֵ������������������0��79��ֹ��
    //�߽����ݱ�����getOneSideResult[60]
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
        
        for(int i=45;i>20;i--)//�ұ�Ե
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
                j=getOneSideResultL[i]+15;//�´ε��������ϴε�ƫ��һ��ֵ
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
    //�����������������������ǵ���������ƫ��һ����������30�����»�ʹ��Ƭ����Ϊ������
    //Ҳʹ����ת��ʱ�Ĳ���
    int tt;
    if('L'==dir)
    {
        for(int i=45;i>20;i--)
        {
            if(center_virtual[i]<5)
            {
                tt=i;//�ҵ�����ƫ������ߵļ���
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
                tt=i;//�ҵ�����ƫ������ߵļ���
                break;
            }
        }
        return tt;
    }
}


////////////////////////////�Ա���������������//////////////////////////////////
//��ֱ�߷���1
//yuanhuan
int getLineInfo(char dir)
{
    int t=0;
    if('L'==dir)
    {
        if(absGet(black_right[ROW]-black_right[getRowStart])<35//����ֱ����б��35
           && ((black_right[(int)(ROW/2-getRowStart/2)]-black_right[getRowStart])-(black_right[ROW]-black_right[(int)(ROW/2-getRowStart/2)]))<24//20  absGet
               //&&((black_right[(int)(ROW/2-getRowStart/2)]-black_right[getRowStart]) >= (black_right[ROW]-black_right[(int)(ROW/2-getRowStart/2)])*0.8)
               //&&((black_right[(int)(ROW/2-getRowStart/2)]-black_right[getRowStart]) <= (black_right[ROW]-black_right[(int)(ROW/2-getRowStart/2)])*1.3)
               )
        {
            //��������������
            for(int i=46;i>18;i--)//�ұ�����ƫ
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
        if(((black_left[getRowStart]-black_left[ROW])<35) && ((black_left[getRowStart]-black_left[ROW])>0)//����ֱ����б��35
           && ((black_left[getRowStart]-black_left[(int)(ROW/2-getRowStart/2)])-(black_left[(int)(ROW/2-getRowStart/2)]-black_left[ROW]))<20//20
               )
        {
            for(int i=46;i>18;i--)//zuo����zuoƫ
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

//�ó�ָ�����䶪������ָ�����䣨�Ի�׼��46����Ϊ�߽磩
//�������-turnPointNumLeft,turnPointNumRight
int getLostSideNum(int startL,int finshL,char dir)//46-10
{
    //get 46-10�Ķ�������
    int tpnL=0,tpnR=0;
    if('L'==dir)//ȷ�����ڱ���
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
//��������Ϊ������ײ��кͷ��򣬼������ʼ��
//������߽�topLostPos =getLostSideStartRow()
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
        for(int i=0;i<80;i+=2)//����
        {
            imgAddDot(9,i,0);//��Զ��
            //imgAddDot(lostStartPos,i,0);//��Զ��
            //imgAddDot(lostEndPos,i,0);//��Զ��
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
        for(int i=0;i<60;i+=1)//����
        {//ʶ��ı��ߺ�����
            
            imgAddDot(i,black_left[i]+2,0);
            imgAddDot(i,center_virtual[i],0);
            imgAddDot(i,black_right[i]-2,0);
            imgAddDot(i,black_left[ROW+1],0);//���߷�Χ
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

int getSlope(int a,int b,int h)//б�ʼ���
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
void curveFitting(char cf)//�������
{
    switch(cf)
    {
        case 'L':{};break;//ֱ��
        case 'B':{};break;//�ϰ�
        case 'R':{};break;//���
        case 'C':{};break;//Բ��
        case 'A':{};break;//ʮ��
        default:break;
    }
}



//================///==============///=================///============///=============//
void imgAddDot(int h,int w,int a)//������ʱ���㺯��
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

