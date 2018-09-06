/*   �ļ���ͼ����͸�ӱ任
 *
 *   ˵������ͼ��ɼ�ǰ��Ͱ�α任����͸�ӱ任��ʼ����������Ӧӳ���
 *         �ڲɼ���һ��ͼ���������IPMCorrect���������� CorrImg[120][160]�洢��͸�ӱ任��ͼ��
 *           ������BuketCorrect����������CorrImg[120][160]�洢Ͱ�κ�ͼ��
 *         �����г�ʼ�����������ڳ����ʼ����ִ��!!!
 *
 *   �����������ߣ��ȶ�ԭʼͼ�����ߣ�Ȼ�������֪�߽����ȷ�����ߣ����ڵ��߶��������ͼ��ֲ���͸�ӱ任��
 *                �õ�����ͼ��Ȼ�����߻�����ߣ���ͨ����ӳ���õ�ԭʼͼ������
 *                ���������С���˷������߾��Ȼ������ڴ���
 *         �ڲ�ࣺ��֪ͼ�����꣬����ͼ��������ʵ������Ĺ�ϵ���������Ӧ���������복���루ԭ��Ϊ����ͷ���ģ�
 *
 *            ��������(X,Y)��ͼ������(u,v)��ϵ����
 *            u = (0.0128*X-0.0007*Y-0.0463)/(0.0037*Y+1)/0.0365+80;
 *            v = (-0.007*Y+4.1192)/(0.0037*Y+1)/0.0365+60;
 * 
 *            X = (1.24*u-0.021*v-100)/(0.0028*v+0.017); 
 *            Y = (3.65*v-63.092)/(0.1103-0.0135*v);
 *
 *   ע��***********************************eо�ڲ����ϣ������⴫**************************************
 */
   
#include "common.h" //ɽ��common.hͷ�ļ�
#include "IPM.h"

const double f = 0.00325;
const double dx = 0.0401,dy = 0.0401;
#define imagedeal_W       80
#define imagedeal_H       60
Site_t PMCorr[imagedeal_H][imagedeal_W];   //͸��ӳ�����ԭʼͼ�õ�����ͼ
Site_t BuketCorr[imagedeal_H][imagedeal_W];  //Ͱ�ν���ӳ���
Site_t IPMCorr[imagedeal_H][imagedeal_W];  //��͸�ӷ�����ӳ���������ͼ�õ�ԭʼͼ

unsigned char CorrImg[imagedeal_H][imagedeal_W]; //������ͼ�����飬����ͼ����
                                  //Ͱ�ν�����͸�ӱ任�õ�ͬһ������


// Ͱ�ν�����ʼ�������������� 
// k1 = -0.00001374; k2 = -0.00001057;  
     
void BuketCorrInit( float k1, float k2 ) //K1ΪX������������K2ΪY����������
{  
    uint8 imgWidth = 80;   // �������ͷͼ��ߴ�  
    uint8 imgHeight = 60;  
  
    uint8 imgWd2 = imgWidth>>1;  
    uint8 imgHd2 = imgHeight>>1;  
  
    int it;  
    int jt;  
    int it2;  
    int jt2;  
  
    for( int i=0; i<imgHeight; i++ )  
    {  
        it = ( i + 1 ) - imgHd2; //  (i+1) ����������ͼ������  
        for( int j=0; j<imgWidth; j++ )  
        {  
            float temp;  
  
            jt = ( j + 1 ) - imgWd2; // (j+1) ����������ͼ������  
            temp = 1 + k1*it*it + k2*jt*jt; 
			
            it2 = (int)(temp * it);
            jt2 = (int)(temp * jt);  
  
            it2 = it2 + imgHd2 + 1;//ע������Խ��
            jt2 = jt2 + imgWd2 + 1;  

            BuketCorr[i][j].x = jt2;  
            BuketCorr[i][j].y = it2;  
        }  
    }  
} 
  
void PMCorrInit(void)  //͸�����任��ʼ����������ӳ���
{
   int u,v;
   int x1,y1,i,j;
   double X,Y,m,n,a,b;
   unsigned char value; 
   
   
   for(v=0;v<imagedeal_H;v++)    //������ͼ������(u,v)
   {
     for(u=0;u<imagedeal_W;u++)
     {
       
          X=(u-imagedeal_W/2)*dx/f; // ӳ�䵽��������(X,Y)
          Y =(67-v)*dy/f;
        
          n = (0.0111*X+0.0005*Y+0.0456)/(0.0065*Y+1)/dx+imagedeal_W/2;//0.0035
          m = (-0.0044*Y+1.9785)/(0.0035*Y+1)/dy+imagedeal_H/2;  //ӳ�䵽ԭʼͼ������(n,m)
          
          j = floor(n);   //floor() iarϵͳ�⺯��
          i = floor(m);  //�����ٽ��ֵ
          a = m-i;
          b = n-j;
          if(a<0.5)
          {
            y1 = i;
          }
          else
          {y1 = i+1;}
          
          if(b<0.5)
          {x1 = j;}
          else
          {x1 = j+1;}
          
          if(x1>=0&&x1<imagedeal_W&&y1>=0&&y1<imagedeal_H)
          {
            PMCorr[v][u].x = x1; //ӳ�䵽����
            PMCorr[v][u].y = y1;
          }
    
     }
     
   }
  
}

void IPMCorrInit(void) //��͸��ӳ���ʼ����������������
{
   int u,v;
   int i,j,it,jt;
   double X,Y,m,n,a,b;
 
   
   for(v=0;v<imagedeal_H;v++) //%ԭʼͼ������(u,v)
    {
         for(u=0;u<imagedeal_W;u++)
         {
              X = (1.24*u-0.021*v-100)/(0.0028*v+0.017);//ԭʼͼ��ӳ�䵽��������
              Y = (3.65*v-63.092)/(0.1103-0.0135*v); 
             
              n = X*f/dx+imagedeal_W/2;
              m = 70-Y*f/dy; //%ӳ�䵽����ͼ������(n,m)
              
              j = floor(n);i = floor(m);  //%����˫���Բ�ֵ�������ٽ���ֵ
              a = m-i;b = n-j;
            
             if(a<0.5)
               it = i;
             else
               it = i+1;
             
             if(b<0.5)
               jt = j;
             else
               jt = j+1;
             
             if(it>0&&it<imagedeal_H&&jt>0&&jt<imagedeal_W)
             {
               IPMCorr[v][u].x = jt;
               IPMCorr[v][u].y = it;
             }
            
           
         }
          
    }  
  
}

// ��ͷ�������У��  
void BuketCorrect(unsigned char (*ImgOrigin)[imagedeal_W])  
{  
    int it;  
    int jt;  
  
    for( int i=0; i<imagedeal_H; i++ )  
    {  
      
        for( int j=0; j<imagedeal_W; j++ )  
        {  
            it = BuketCorr[i][j].y;  
            jt = BuketCorr[i][j].x;  
            
            CorrImg[i][j] = ImgOrigin[it][jt];
        }  
    }  
}  


void PMCorrect(unsigned char (*ImgOrigin)[imagedeal_W] ) //͸�����任�����ڽ���ÿ���ɼ�ͼ��
{
    int it,jt,m,n;
    int ImgTemp[imagedeal_H][imagedeal_W];
    BuketCorrect(ImgOrigin);      //��Ͱ��ӳ��
    /*for(m=0;m<imagedeal_H;m++)  //Ͱ�α任��ͼ�񿽱���������͸��ӳ��
    {
       for(n=0;n<imagedeal_W;n++)
       {
           ImgTemp[m][n] = CorrImg[m][n];
       }
    }*/
    for( int i=0; i<imagedeal_H; i++ )  
    {  
      
        for( int j=0; j<imagedeal_W; j++ )  
        {  
            it = PMCorr[i][j].y;  
            jt = PMCorr[i][j].x;  
            
            CorrImg[i][j] = ImgOrigin[it][jt];
        }  
    }  
}

