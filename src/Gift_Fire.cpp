#include <graphics.h>
#include <conio.h>
#include <iostream.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Mmsystem.h>
#pragma comment ( lib,"Winmm.lib")//加载Winmm.lib 库

#define NUM 13

 struct FIRE
{
	int r;//当前半径
	int x,y;//其开始绽放的坐标
	int cen_x,cen_y;//图片绽放中心
	int max_r;//最大半径
	int height,width;//图片高，宽
	int xy[240][240];//用来储存像素

	bool show;//绽放开关
	bool draw;//画图开关
	DWORD t1,t2,dt;//控制时间
}Fire[NUM];//烟花数组


struct BULLET
{
	int x,y;//开始发射点
	int xh,yh;//最高点坐标
	int height;//发射经历高度

	bool shoot;//发射开关
	DWORD t1,t2,dt;//控制时间
	IMAGE img[2];//图片数组，用来控制发射时的一明一暗
	byte n : 1;//n++
}bul[NUM];


/******************函数声明**********************************/
void Init(int i);
void Initxin();
void Load();
void Loadxin();
void Loadyuan();

void choose(DWORD& t1);
void shoot();
void show(DWORD* pMem);

void style1();
void xinyue(DWORD& ty);
void word(DWORD& tw);
void newyear(DWORD& tr);
void happy(DWORD& th);

void star();
void end();


/********************全局变量******************************/
int ny=800;
int nh=850;
int nw=850;
int nr=850;
int drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 55 };
int time1=100;
int time2=1000;
bool xiaochu=true;//是否随机清除点

/************************************************/
int main()
{
	srand(time(NULL));
	initgraph(1200,800);
    //播放音乐
	mciSendString("open 一次就好.mp3 alias 一次就好",0,0,0);
	mciSendString("play 一次就好 repeat ",0,0,0);//重复播放


    int xiao=2;//消除频率
    DWORD t1    =timeGetTime();
	DWORD t     =timeGetTime();
	DWORD ty    =timeGetTime();
	DWORD th    =timeGetTime();
	DWORD tw    =timeGetTime();
	DWORD tr    =timeGetTime();
	DWORD tn                  ;
	DWORD* pMem = GetImageBuffer();	


	for(int i=0;i<NUM;i++)
	{
		Init(i);
	}
	Load();
	BeginBatchDraw();//让图像连续移动
    star();//开始播放图片
    FlushBatchDraw();
	Sleep(3000);//程序停止运行
    

    while(!kbhit())//直到遇到按键退出
	{
		if(xiaochu)//随机消除点，制造消失效果
		{
			for(int i=1;i<=time2;i++)
			{
	        	for(int j=1;j<=xiao;j++)
				{
		        	int px=rand()%1200;
		        	int py=rand()%799;
		         	if(py<799)//让像素点变黑
		            	pMem[py * 1200 + px] = pMem[py * 1200 + px + 1] = BLACK;
				}
			}
		}
		/********************时间分段控制***************************/
		if((tn=timeGetTime())-t<70000) choose(t1);//随机烟花
		if((tn=timeGetTime())-t>75000&&(tn=timeGetTime())-t<75010)  style1();//变换形式
        if((tn=timeGetTime())-t>75010&&(tn=timeGetTime())-t<75015) //烟花开关
        for(i=0;i<NUM;i++)
		{
			bul[i].shoot   =true;
	    	putimage(bul[i].x ,bul[i].y	,&bul[i].img[bul[i].n] ,SRCINVERT);	
		}
        //时间差：集体上升时间
		if((tn=timeGetTime())-t>(80015)&&(tn=timeGetTime())-t<104995) 
		{
		   xiao=1;
		   xinyue(ty);//上升月
		}
		if((tn=timeGetTime())-t>104995&&(tn=timeGetTime())-t<105025)
		{
			Loadxin();//加载心形图案
			for(i=0;i<=5;i++)//使心形烟花绽放速度变快
			   drt[i]=5;
            for(i=6;i<=9;i++)
			   drt[i]=10;
			for(i=10;i<=16;i++)
			   drt[i]=20;
			xiaochu=true;//开始消除
			time1=500;//每隔time1时间段选择烟花
			time2=600;
		}
		if((tn=timeGetTime())-t>105025&&(tn=timeGetTime())-t<175010) choose(t1);	//随机烟花
		if((tn=timeGetTime())-t>180010&&(tn=timeGetTime())-t<180015)  style1();//变换形式
        if((tn=timeGetTime())-t>180015&&(tn=timeGetTime())-t<180019) //烟花开关
        for(i=0;i<NUM;i++)
		{
			bul[i].shoot   =true;
	    	putimage(bul[i].x ,bul[i].y	,&bul[i].img[bul[i].n] ,SRCINVERT);	
		}
		if((tn=timeGetTime())-t>190000&&(tn=timeGetTime())-t<225010)
            word(tw);        //文字图片上升
		if((tn=timeGetTime())-t>225010&&(tn=timeGetTime())-t<269010)
		{
			if((tn=timeGetTime())-t>225010&&(tn=timeGetTime())-t<228500)
			{
				xiaochu=true;//加快清除速度，清除上一个图片
				xiao=2;
			}
			if((tn=timeGetTime())-t>228500&&(tn=timeGetTime())-t<248500)
			{
				xiao=1;//减缓清除速度，播放下一个图片
				newyear(tr);
			}
			if((tn=timeGetTime())-t>248500&&(tn=timeGetTime())-t<251500)
				xiao=2;//加快清除速度，清除上一个图片
		    if((tn=timeGetTime())-t>251500&&(tn=timeGetTime())-t<269010)
			{
				xiao=1;//减缓清除速度，播放下一个图片
				happy(th);
			}		
		}
		if((tn=timeGetTime())-t>269010)  
		{
			nw=850;//重置word()函数里面的坐标以便循环		
			ny=800;//重置xinyue()函数里面的坐标以便循环
			nh=850;//重置happy()函数里面的坐标以便循环
			nr=850;//重置newyear()函数里面的坐标以便循环
			Loadyuan();//变换成圆形烟花
			xiao=2;//加快清除速率
			xiaochu=true;//打开消除开关
			t=tn;//更新计时器
		}
        shoot();//发射烟花
        show(pMem);//绽放烟花
		FlushBatchDraw();
	}


	end();//结束
	FlushBatchDraw();
	Sleep(5000);
	return 0;
}



void star()
{
	IMAGE fm;//定义储存图片
	loadimage(&fm,"star.jpg",1024,768);//将图片加载进去
	putimage(3,3,&fm,SRCINVERT);//将图片输出
}


void Init(int i)//初始化烟花数据
{
	int r[13] = { 120, 120, 155, 123, 130, 147, 138, 138, 130, 135, 140, 132, 155 };
	int x[13] = { 120, 120, 110, 117, 110, 93,  102, 102, 110, 105, 100, 108, 110 };
	int y[13] = { 120, 120, 85,  118, 120, 103, 105, 110, 110, 120, 120, 104, 85  };
	Fire[i].x     =0;
	Fire[i].y     =0;
	Fire[i].r     =0;
	Fire[i].cen_x =x[i];
	Fire[i].cen_y =y[i];
	Fire[i].max_r =r[i];
	Fire[i].height=240;
	Fire[i].width =240;
	Fire[i].show  =false;
	Fire[i].t1    =timeGetTime();
	Fire[i].draw  =false;
	Fire[i].dt    =5;


	bul[i].x           =0;
	bul[i].y           =0;
	bul[i].height      =0;
	bul[i].xh          =0;
	bul[i].yh          =0;
	bul[i].dt          =rand()%4+4;
	bul[i].shoot       =false;
	bul[i].n           =0;
	bul[i].t1          =timeGetTime();
}



void Initxin()//加载心形图案数据
{
	int r[NUM] = { 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 };
	int x[NUM] = { 106, 116, 115, 114, 118, 160,  120, 120, 123, 105, 100, 111, 119  };
	int y[NUM] = { 94,   91, 79,  98,   88, 104,   95, 94  , 134, 120, 120, 77 , 101  };
	
	for(int i=0;i<13;i++)
	{
		Fire[i].cen_x =x[i];
    	Fire[i].cen_y =y[i];
    	Fire[i].max_r =r[i];
	}
}





void Load()//把图片加载进数组
{

	Loadyuan();//加载圆形
    /*************************************************/
	IMAGE sm;

	loadimage(&sm,"shoot.jpg",200,50);//加载发射图片
	for(int i=0;i<NUM;i++)
	{
		SetWorkingImage(&sm);

	   	int n=rand()%5;

		getimage(&bul[i].img[0],n*20,0,20,50);
		getimage(&bul[i].img[1],(n+5)*20,0,20,50);
	}
    SetWorkingImage();
}

void Loadyuan()
{
	IMAGE fm,gm;
	loadimage(&fm,"flower.jpg",3120,240);
	for(int i=0;i<NUM;i++)
	{
		SetWorkingImage(&fm);
		getimage(&gm,i*240,0,240,240);
		SetWorkingImage(&gm);
		for(int a=0;a<240;a++)
			for(int b=0;b<240;b++)
				Fire[i].xy[a][b]=getpixel(a,b);
	}
	SetWorkingImage();
}

void Loadxin()
{
	IMAGE fm,gm;
	char  c1[100];
	for(int i=0;i<NUM;i++)
	{
		sprintf( c1, "xin%d.jpg", i );//利用字符串表示相片名称	
        loadimage(&fm,c1,240,240);//加载像片
		SetWorkingImage(&fm);//设置工作域
		for(int a=0;a<240;a++)
			for(int b=0;b<240;b++)
				Fire[i].xy[a][b]=getpixel(a,b);//把每个像素点利用数组储存
	}
	SetWorkingImage();//设置工作域为全部
}






void choose(DWORD& t1)
{
	DWORD t2=timeGetTime();
	/***************有时间限制*****************/
	if(t2-t1>time1)
	{
		int n=rand()%20;

		if(n<NUM&&bul[n].shoot==false&&Fire[n].show==false)//选择绽放完毕的烟花进行发射
		{
			bul[n].x       =rand()%1200;
			bul[n].y       =rand()%100+600;
			bul[n].xh      =bul[n].x;
			bul[n].yh      =rand()%400;
			bul[n].height  =bul[n].y-bul[n].yh;
			bul[n].shoot   =true;    
			putimage(bul[n].x ,bul[n].y	,&bul[n].img[bul[n].n] ,SRCINVERT);
		}                          
		t1=t2;
	}
}


void shoot()
{
	for(int i=0;i<NUM;i++)
	{
		bul[i].t2=timeGetTime();//时间延时控制上升速度
		/*******************有时间限制*************************/
		if(bul[i].t2-bul[i].t1>bul[i].dt&&bul[i].shoot)
		{
			putimage(bul[i].x ,bul[i].y	,&bul[i].img[bul[i].n] ,SRCINVERT);
			
			
			if(bul[i].y>bul[i].yh)//未到达最高点时把n进行变换，坐标进行移动
			{
				bul[i].n++;
				bul[i].y -=5;
			}


			putimage(bul[i].x ,bul[i].y	,&bul[i].img[bul[i].n] ,SRCINVERT);
			
			
			if((bul[i].y-bul[i].yh)*4<=bul[i].height)//当其离最高点1/4距离时，减缓上升速度
				bul[i].dt=rand()%4+10;
			                                           
			                                                    
			if(bul[i].y<=bul[i].yh)//当到达最高点时，进行赋值
			{
				putimage(bul[i].x ,bul[i].y	,&bul[i].img[bul[i].n] ,SRCINVERT);
				Fire[i].x=bul[i].xh+10;
				Fire[i].y=bul[i].yh;
				Fire[i].show=true;//开关打开
				bul[i].shoot=false;//shoot开关关闭
			}
			bul[i].t1=bul[i].t2;//计时器归零
		}
	}
}



void show(DWORD* pMem)
{
    for(int i=0;i<NUM;i++)
	{
		/***************有时间限制***********************/
		Fire[i].t2=timeGetTime();
	/***********************来控制bool draw****************************/
		if(Fire[i].t2-Fire[i].t1>Fire[i].dt&&Fire[i].show==true)
		{
			if(Fire[i].r<Fire[i].max_r)//判断其半径是否超过最大半径
			{
				Fire[i].r++;
				Fire[i].dt   =drt[Fire[i].r/10];
				Fire[i].draw =true;
			}
			else//如果超过，停止画圆
			{
				Fire[i].draw=false;
				Init(i);
			}
			Fire[i].t1=Fire[i].t2;
		}
       /*****************无时间限制****************************/
		if(Fire[i].draw)
		{
			for(double a=0;a<=6.28;a+=0.01)//一圈一圈的输出
			{
				int x1=(int)(Fire[i].cen_x+Fire[i].r*cos(a));
			    int y1=(int)(Fire[i].cen_y+Fire[i].r*sin(a));
			    if(x1>0&&x1<Fire[i].width&&y1>0&&y1<Fire[i].height)
				{
		     		int b = Fire[i].xy[x1][y1] & 0xff;//blue蓝色，所对应的像素点 
			     	int g = ( Fire[i].xy[x1][y1] >> 8 ) & 0xff;//green绿色，所对应的像素点 
		    		int r = ( Fire[i].xy[x1][y1] >> 16 );   //red红色    对应的大小 
      
		    		int xx=(int)(Fire[i].x+Fire[i].r*cos(a));
			     	int yy=(int)(Fire[i].y+Fire[i].r*sin(a));
                    //太暗的点不输出
			        if(r>0x20&&r>0x20&&g>0x20&&xx>0&&xx<1200&&yy>0&&yy<800)//不输出暗色点
			   		pMem[yy*1200+xx]=BGR(Fire[i].xy[x1][y1]);
				}
				
			}
			Fire[i].draw=false;
		}
	}
}

/************************心形图案的发射坐标******************************/
void style1()
{
	DWORD tx1=timeGetTime();//心形坐标
	int x[NUM] = { 60, 75, 91, 100, 95, 75, 60, 45, 25, 15, 25, 41, 60 };
	int y[NUM] = { 65, 53, 40, 22, 5, 4, 20, 4, 5, 22, 40, 53, 65 };
	for(int i=0;i<NUM;i++)//把发射坐标赋给相应的烟花
	{	
    	bul[i].x       =x[i]*10-90;//发射点的横坐标
	    bul[i].y       =(y[i]+60)*10;//发射点的纵坐标
	    bul[i].xh      =bul[i].x;//最高点横坐标
        bul[i].yh      =y[i]*10;//最高点纵坐标
        bul[i].height  =bul[i].y-bul[i].yh;//高度一样
	}
}
/*********************上升月*********************/
void xinyue(DWORD& tx)
{
	DWORD t1=timeGetTime();
	IMAGE fm ,gm;
	/**************加载图片*****************/
	loadimage(&fm,"xinstar.jpg",500,284);
	loadimage(&gm,"for you.jpg",547,167);
	if(t1-tx>18)//上升1像素的时间间隔
	{  
		if(ny>=10)
		{//显示图片
			putimage(598,ny,&fm,SRCINVERT);
			putimage(100,ny+250,&gm,SRCINVERT);
			ny -=1;//每次移动1个像素
    		putimage(598,ny,&fm,SRCINVERT);
			putimage(100,ny+250,&gm,SRCINVERT);
		}
		else  xiaochu=false;//取消消除屏幕点
		tx=t1;
	}
}

/**********************加载qq1.jpg**********************/
void word(DWORD& tw)
{
	DWORD t1=timeGetTime();
	IMAGE fm,pm,jm;
	loadimage(&fm,"qq1.jpg",240,240);
	loadimage(&pm,"qq2.jpg",240,240);
	loadimage(&jm,"my word1.jpg",697,198);
	if(t1-tw>18)
	{  
		if(nw>=10)
		{
			putimage(780,nw,&fm,SRCINVERT);
			putimage(30,nw,&pm,SRCINVERT);
			putimage(150,nw+400,&jm,SRCINVERT);
			nw -=1;
    		putimage(780,nw,&fm,SRCINVERT);
			putimage(30,nw,&pm,SRCINVERT);
			putimage(150,nw+400,&jm,SRCINVERT);
		}
		else 
			xiaochu=false;
		tw=t1;
	}
}

/*******************加载new year.jpg*****************************/
void newyear(DWORD& tr)
{
	DWORD t1=timeGetTime();
	IMAGE fm;
	loadimage(&fm,"new year.jpg",611,151);
	if(t1-tr>18)
	{  
		if(nr>=10)
		{
			putimage(250,nr,&fm,SRCINVERT);
			nr -=1;
    		putimage(250,nr,&fm,SRCINVERT);
		}
		tr=t1;
	}
}

/*******************加载happy2016.jpg*********************/
void happy(DWORD& th)
{
	DWORD t1=timeGetTime();
	IMAGE fm;
	loadimage(&fm,"happy2016.jpg",658,142);
	if(t1-th>20)
	{  
		if(nh>=100)
		{
			putimage(250,nh,&fm,SRCINVERT);
			nh -=1;
    		putimage(250,nh,&fm,SRCINVERT);
		}
		th=t1;
	}
}

void end()
{
	IMAGE fm;
	loadimage(&fm,"end.jpg",1024,768);
	putimage(3,3,&fm,SRCINVERT);
}
