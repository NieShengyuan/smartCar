/*   文件：图像逆透视变换
 *
 *   说明：①图像采集前对桶形变换和逆透视变换初始化，建立相应映射表
 *         ②采集完一场图像后，若调用IPMCorrect（）函数， CorrImg[120][160]存储逆透视变换后图像
 *           若调用BuketCorrect（）函数，CorrImg[120][160]存储桶形后图像
 *         ③所有初始化函数均放在程序初始部分执行!!!
 *
 *   方案：①搜线：先对原始图像搜线，然后根据已知边界初步确定中线，对于单边丢线情况对图像局部逆透视变换，
 *                得到正视图，然后搜线获得中线，再通过逆映射表得到原始图像中线
 *                最后利用最小二乘法对中线均匀化，便于处理。
 *         ②测距：已知图像坐标，根据图像坐标与实际坐标的关系，可算出相应世界坐标与车距离（原点为摄像头中心）
 *
 *            世界坐标(X,Y)与图像坐标(u,v)关系如下
 *            u = (0.0128*X-0.0007*Y-0.0463)/(0.0037*Y+1)/0.0365+80;
 *            v = (-0.007*Y+4.1192)/(0.0037*Y+1)/0.0365+60;
 * 
 *            X = (1.24*u-0.021*v-100)/(0.0028*v+0.017); 
 *            Y = (3.65*v-63.092)/(0.1103-0.0135*v);
 *
 *   注：***********************************e芯内部资料，不得外传**************************************
 */
   
#include "common.h" //山外common.h头文件
#include "IPM.h"

const double f = 0.00325;
const double dx = 0.0401,dy = 0.0401;
#define imagedeal_W       80
#define imagedeal_H       60
Site_t PMCorr[imagedeal_H][imagedeal_W];   //透视映射表，由原始图得到正视图
Site_t BuketCorr[imagedeal_H][imagedeal_W];  //桶形矫正映射表
Site_t IPMCorr[imagedeal_H][imagedeal_W];  //逆透视反矫正映射表，由正视图得到原始图

unsigned char CorrImg[imagedeal_H][imagedeal_W]; //矫正后图像数组，用于图像处理
                                  //桶形矫正和透视变换用的同一个数组


// 桶形矫正初始化，建立矫正表 
// k1 = -0.00001374; k2 = -0.00001057;  
     
void BuketCorrInit( float k1, float k2 ) //K1为X方向畸变参数，K2为Y方向畸变参数
{  
    uint8 imgWidth = 80;   // 获得摄像头图像尺寸  
    uint8 imgHeight = 60;  
  
    uint8 imgWd2 = imgWidth>>1;  
    uint8 imgHd2 = imgHeight>>1;  
  
    int it;  
    int jt;  
    int it2;  
    int jt2;  
  
    for( int i=0; i<imgHeight; i++ )  
    {  
        it = ( i + 1 ) - imgHd2; //  (i+1) 是其真正的图像坐标  
        for( int j=0; j<imgWidth; j++ )  
        {  
            float temp;  
  
            jt = ( j + 1 ) - imgWd2; // (j+1) 是其真正的图像坐标  
            temp = 1 + k1*it*it + k2*jt*jt; 
			
            it2 = (int)(temp * it);
            jt2 = (int)(temp * jt);  
  
            it2 = it2 + imgHd2 + 1;//注意数组越界
            jt2 = jt2 + imgWd2 + 1;  

            BuketCorr[i][j].x = jt2;  
            BuketCorr[i][j].y = it2;  
        }  
    }  
} 
  
void PMCorrInit(void)  //透视正变换初始化，建立正映射表
{
   int u,v;
   int x1,y1,i,j;
   double X,Y,m,n,a,b;
   unsigned char value; 
   
   
   for(v=0;v<imagedeal_H;v++)    //矫正后图像坐标(u,v)
   {
     for(u=0;u<imagedeal_W;u++)
     {
       
          X=(u-imagedeal_W/2)*dx/f; // 映射到世界坐标(X,Y)
          Y =(67-v)*dy/f;
        
          n = (0.0111*X+0.0005*Y+0.0456)/(0.0065*Y+1)/dx+imagedeal_W/2;//0.0035
          m = (-0.0044*Y+1.9785)/(0.0035*Y+1)/dy+imagedeal_H/2;  //映射到原始图像坐标(n,m)
          
          j = floor(n);   //floor() iar系统库函数
          i = floor(m);  //利用临界插值
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
            PMCorr[v][u].x = x1; //映射到数组
            PMCorr[v][u].y = y1;
          }
    
     }
     
   }
  
}

void IPMCorrInit(void) //逆透视映射初始化，建立反矫正表
{
   int u,v;
   int i,j,it,jt;
   double X,Y,m,n,a,b;
 
   
   for(v=0;v<imagedeal_H;v++) //%原始图像坐标(u,v)
    {
         for(u=0;u<imagedeal_W;u++)
         {
              X = (1.24*u-0.021*v-100)/(0.0028*v+0.017);//原始图像映射到世界坐标
              Y = (3.65*v-63.092)/(0.1103-0.0135*v); 
             
              n = X*f/dx+imagedeal_W/2;
              m = 70-Y*f/dy; //%映射到矫正图像坐标(n,m)
              
              j = floor(n);i = floor(m);  //%利用双线性插值法或者临近插值
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

// 镜头径向畸变校正  
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


void PMCorrect(unsigned char (*ImgOrigin)[imagedeal_W] ) //透视正变换，用于矫正每场采集图像
{
    int it,jt,m,n;
    int ImgTemp[imagedeal_H][imagedeal_W];
    BuketCorrect(ImgOrigin);      //先桶形映射
    /*for(m=0;m<imagedeal_H;m++)  //桶形变换后图像拷贝，用作逆透视映射
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

