#include <graphics.h>
#include <conio.h>
#include <iostream.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Mmsystem.h>
#pragma comment ( lib,"Winmm.lib")//����Winmm.lib ��

#define NUM 13

 struct FIRE
{
	int r;//��ǰ�뾶
	int x,y;//�俪ʼ���ŵ�����
	int cen_x,cen_y;//ͼƬ��������
	int max_r;//���뾶
	int height,width;//ͼƬ�ߣ���
	int xy[240][240];//������������

	bool show;//���ſ���
	bool draw;//��ͼ����
	DWORD t1,t2,dt;//����ʱ��
}Fire[NUM];//�̻�����


struct BULLET
{
	int x,y;//��ʼ�����
	int xh,yh;//��ߵ�����
	int height;//���侭���߶�

	bool shoot;//���俪��
	DWORD t1,t2,dt;//����ʱ��
	IMAGE img[2];//ͼƬ���飬�������Ʒ���ʱ��һ��һ��
	byte n : 1;//n++
}bul[NUM];


/******************��������**********************************/
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


/********************ȫ�ֱ���******************************/
int ny=800;
int nh=850;
int nw=850;
int nr=850;
int drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 55 };
int time1=100;
int time2=1000;
bool xiaochu=true;//�Ƿ���������

/************************************************/
int main()
{
	srand(time(NULL));
	initgraph(1200,800);
    //��������
	mciSendString("open һ�ξͺ�.mp3 alias һ�ξͺ�",0,0,0);
	mciSendString("play һ�ξͺ� repeat ",0,0,0);//�ظ�����


    int xiao=2;//����Ƶ��
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
	BeginBatchDraw();//��ͼ�������ƶ�
    star();//��ʼ����ͼƬ
    FlushBatchDraw();
	Sleep(3000);//����ֹͣ����
    

    while(!kbhit())//ֱ�����������˳�
	{
		if(xiaochu)//��������㣬������ʧЧ��
		{
			for(int i=1;i<=time2;i++)
			{
	        	for(int j=1;j<=xiao;j++)
				{
		        	int px=rand()%1200;
		        	int py=rand()%799;
		         	if(py<799)//�����ص���
		            	pMem[py * 1200 + px] = pMem[py * 1200 + px + 1] = BLACK;
				}
			}
		}
		/********************ʱ��ֶο���***************************/
		if((tn=timeGetTime())-t<70000) choose(t1);//����̻�
		if((tn=timeGetTime())-t>75000&&(tn=timeGetTime())-t<75010)  style1();//�任��ʽ
        if((tn=timeGetTime())-t>75010&&(tn=timeGetTime())-t<75015) //�̻�����
        for(i=0;i<NUM;i++)
		{
			bul[i].shoot   =true;
	    	putimage(bul[i].x ,bul[i].y	,&bul[i].img[bul[i].n] ,SRCINVERT);	
		}
        //ʱ����������ʱ��
		if((tn=timeGetTime())-t>(80015)&&(tn=timeGetTime())-t<104995) 
		{
		   xiao=1;
		   xinyue(ty);//������
		}
		if((tn=timeGetTime())-t>104995&&(tn=timeGetTime())-t<105025)
		{
			Loadxin();//��������ͼ��
			for(i=0;i<=5;i++)//ʹ�����̻������ٶȱ��
			   drt[i]=5;
            for(i=6;i<=9;i++)
			   drt[i]=10;
			for(i=10;i<=16;i++)
			   drt[i]=20;
			xiaochu=true;//��ʼ����
			time1=500;//ÿ��time1ʱ���ѡ���̻�
			time2=600;
		}
		if((tn=timeGetTime())-t>105025&&(tn=timeGetTime())-t<175010) choose(t1);	//����̻�
		if((tn=timeGetTime())-t>180010&&(tn=timeGetTime())-t<180015)  style1();//�任��ʽ
        if((tn=timeGetTime())-t>180015&&(tn=timeGetTime())-t<180019) //�̻�����
        for(i=0;i<NUM;i++)
		{
			bul[i].shoot   =true;
	    	putimage(bul[i].x ,bul[i].y	,&bul[i].img[bul[i].n] ,SRCINVERT);	
		}
		if((tn=timeGetTime())-t>190000&&(tn=timeGetTime())-t<225010)
            word(tw);        //����ͼƬ����
		if((tn=timeGetTime())-t>225010&&(tn=timeGetTime())-t<269010)
		{
			if((tn=timeGetTime())-t>225010&&(tn=timeGetTime())-t<228500)
			{
				xiaochu=true;//�ӿ�����ٶȣ������һ��ͼƬ
				xiao=2;
			}
			if((tn=timeGetTime())-t>228500&&(tn=timeGetTime())-t<248500)
			{
				xiao=1;//��������ٶȣ�������һ��ͼƬ
				newyear(tr);
			}
			if((tn=timeGetTime())-t>248500&&(tn=timeGetTime())-t<251500)
				xiao=2;//�ӿ�����ٶȣ������һ��ͼƬ
		    if((tn=timeGetTime())-t>251500&&(tn=timeGetTime())-t<269010)
			{
				xiao=1;//��������ٶȣ�������һ��ͼƬ
				happy(th);
			}		
		}
		if((tn=timeGetTime())-t>269010)  
		{
			nw=850;//����word()��������������Ա�ѭ��		
			ny=800;//����xinyue()��������������Ա�ѭ��
			nh=850;//����happy()��������������Ա�ѭ��
			nr=850;//����newyear()��������������Ա�ѭ��
			Loadyuan();//�任��Բ���̻�
			xiao=2;//�ӿ��������
			xiaochu=true;//����������
			t=tn;//���¼�ʱ��
		}
        shoot();//�����̻�
        show(pMem);//�����̻�
		FlushBatchDraw();
	}


	end();//����
	FlushBatchDraw();
	Sleep(5000);
	return 0;
}



void star()
{
	IMAGE fm;//���崢��ͼƬ
	loadimage(&fm,"star.jpg",1024,768);//��ͼƬ���ؽ�ȥ
	putimage(3,3,&fm,SRCINVERT);//��ͼƬ���
}


void Init(int i)//��ʼ���̻�����
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



void Initxin()//��������ͼ������
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





void Load()//��ͼƬ���ؽ�����
{

	Loadyuan();//����Բ��
    /*************************************************/
	IMAGE sm;

	loadimage(&sm,"shoot.jpg",200,50);//���ط���ͼƬ
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
		sprintf( c1, "xin%d.jpg", i );//�����ַ�����ʾ��Ƭ����	
        loadimage(&fm,c1,240,240);//������Ƭ
		SetWorkingImage(&fm);//���ù�����
		for(int a=0;a<240;a++)
			for(int b=0;b<240;b++)
				Fire[i].xy[a][b]=getpixel(a,b);//��ÿ�����ص��������鴢��
	}
	SetWorkingImage();//���ù�����Ϊȫ��
}






void choose(DWORD& t1)
{
	DWORD t2=timeGetTime();
	/***************��ʱ������*****************/
	if(t2-t1>time1)
	{
		int n=rand()%20;

		if(n<NUM&&bul[n].shoot==false&&Fire[n].show==false)//ѡ��������ϵ��̻����з���
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
		bul[i].t2=timeGetTime();//ʱ����ʱ���������ٶ�
		/*******************��ʱ������*************************/
		if(bul[i].t2-bul[i].t1>bul[i].dt&&bul[i].shoot)
		{
			putimage(bul[i].x ,bul[i].y	,&bul[i].img[bul[i].n] ,SRCINVERT);
			
			
			if(bul[i].y>bul[i].yh)//δ������ߵ�ʱ��n���б任����������ƶ�
			{
				bul[i].n++;
				bul[i].y -=5;
			}


			putimage(bul[i].x ,bul[i].y	,&bul[i].img[bul[i].n] ,SRCINVERT);
			
			
			if((bul[i].y-bul[i].yh)*4<=bul[i].height)//��������ߵ�1/4����ʱ�����������ٶ�
				bul[i].dt=rand()%4+10;
			                                           
			                                                    
			if(bul[i].y<=bul[i].yh)//��������ߵ�ʱ�����и�ֵ
			{
				putimage(bul[i].x ,bul[i].y	,&bul[i].img[bul[i].n] ,SRCINVERT);
				Fire[i].x=bul[i].xh+10;
				Fire[i].y=bul[i].yh;
				Fire[i].show=true;//���ش�
				bul[i].shoot=false;//shoot���عر�
			}
			bul[i].t1=bul[i].t2;//��ʱ������
		}
	}
}



void show(DWORD* pMem)
{
    for(int i=0;i<NUM;i++)
	{
		/***************��ʱ������***********************/
		Fire[i].t2=timeGetTime();
	/***********************������bool draw****************************/
		if(Fire[i].t2-Fire[i].t1>Fire[i].dt&&Fire[i].show==true)
		{
			if(Fire[i].r<Fire[i].max_r)//�ж���뾶�Ƿ񳬹����뾶
			{
				Fire[i].r++;
				Fire[i].dt   =drt[Fire[i].r/10];
				Fire[i].draw =true;
			}
			else//���������ֹͣ��Բ
			{
				Fire[i].draw=false;
				Init(i);
			}
			Fire[i].t1=Fire[i].t2;
		}
       /*****************��ʱ������****************************/
		if(Fire[i].draw)
		{
			for(double a=0;a<=6.28;a+=0.01)//һȦһȦ�����
			{
				int x1=(int)(Fire[i].cen_x+Fire[i].r*cos(a));
			    int y1=(int)(Fire[i].cen_y+Fire[i].r*sin(a));
			    if(x1>0&&x1<Fire[i].width&&y1>0&&y1<Fire[i].height)
				{
		     		int b = Fire[i].xy[x1][y1] & 0xff;//blue��ɫ������Ӧ�����ص� 
			     	int g = ( Fire[i].xy[x1][y1] >> 8 ) & 0xff;//green��ɫ������Ӧ�����ص� 
		    		int r = ( Fire[i].xy[x1][y1] >> 16 );   //red��ɫ    ��Ӧ�Ĵ�С 
      
		    		int xx=(int)(Fire[i].x+Fire[i].r*cos(a));
			     	int yy=(int)(Fire[i].y+Fire[i].r*sin(a));
                    //̫���ĵ㲻���
			        if(r>0x20&&r>0x20&&g>0x20&&xx>0&&xx<1200&&yy>0&&yy<800)//�������ɫ��
			   		pMem[yy*1200+xx]=BGR(Fire[i].xy[x1][y1]);
				}
				
			}
			Fire[i].draw=false;
		}
	}
}

/************************����ͼ���ķ�������******************************/
void style1()
{
	DWORD tx1=timeGetTime();//��������
	int x[NUM] = { 60, 75, 91, 100, 95, 75, 60, 45, 25, 15, 25, 41, 60 };
	int y[NUM] = { 65, 53, 40, 22, 5, 4, 20, 4, 5, 22, 40, 53, 65 };
	for(int i=0;i<NUM;i++)//�ѷ������긳����Ӧ���̻�
	{	
    	bul[i].x       =x[i]*10-90;//�����ĺ�����
	    bul[i].y       =(y[i]+60)*10;//������������
	    bul[i].xh      =bul[i].x;//��ߵ������
        bul[i].yh      =y[i]*10;//��ߵ�������
        bul[i].height  =bul[i].y-bul[i].yh;//�߶�һ��
	}
}
/*********************������*********************/
void xinyue(DWORD& tx)
{
	DWORD t1=timeGetTime();
	IMAGE fm ,gm;
	/**************����ͼƬ*****************/
	loadimage(&fm,"xinstar.jpg",500,284);
	loadimage(&gm,"for you.jpg",547,167);
	if(t1-tx>18)//����1���ص�ʱ����
	{  
		if(ny>=10)
		{//��ʾͼƬ
			putimage(598,ny,&fm,SRCINVERT);
			putimage(100,ny+250,&gm,SRCINVERT);
			ny -=1;//ÿ���ƶ�1������
    		putimage(598,ny,&fm,SRCINVERT);
			putimage(100,ny+250,&gm,SRCINVERT);
		}
		else  xiaochu=false;//ȡ��������Ļ��
		tx=t1;
	}
}

/**********************����qq1.jpg**********************/
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

/*******************����new year.jpg*****************************/
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

/*******************����happy2016.jpg*********************/
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
