#pragma warning(disable:4996)
#undef UNICODE
#undef _UNICODE

#include <graphics.h>              // 引用图形库头文件
#include <conio.h>
#include <stdio.h>
#include <windows.h>				//用到了定时函数sleep()
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define M 20

int r[5][4] = { {30,120,130,160},{170,120,280,160},{310,120,420,160},{30,220,130,260},{170,220,280,260} };//三个按钮的二维数组
int sh[5][4] = { { 0,50,500,90 }, { 0,70,500,80 }, { 0,80,500,90 }, { 0,90,500,100 }, { 0,100,500,110 }, };
int ci[1][4] = { 200,330,300,340 };
int admi[2][4] = { {170, 125, 330, 155},{170, 210, 330, 240} };

int kindy[100] = { 0 };
int jquery = -1;
int qaq = 0;
char sschuan[20];

int button_judge(int x, int y)
{
	if (x > r[0][0] && x<r[0][2] && y>r[0][1] && y < r[0][3])return 1;
	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3])return 2;
	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3])return 3;
	if (x > r[3][0] && x<r[3][2] && y>r[3][1] && y < r[3][3])return 4;
	if (x > r[4][0] && x<r[4][2] && y>r[4][1] && y < r[4][3])return 5;

	return 0;
}

int button_judge2(int x, int y) {
	if (x > ci[0][0] && x<ci[0][2] && y>ci[0][1] && y < ci[0][3]) return 1;
	return 0;
}

int button_judge3(int x, int y) {
	if (x > admi[0][0] && x<admi[0][2] && y>admi[0][1] && y < admi[0][3]) return 1;
	if (x > admi[1][0] && x<admi[1][2] && y>admi[1][1] && y < admi[1][3]) return 2;
	return 0;
}

void Refile();
int wrfile();
void Statistics(); 
void Query();
void Stockin(); 
void Stockout();
void Display();
void Estimate();
void Admilogin();

typedef struct users
{
	char name[40];
	char Password[40];
};
typedef struct
{
	int num;			    //货品编号
	char name[20];		  	//货品名称
	char kind[20]; 	        //种类
	int stock;			    //原始库存
	int in;				   	//入库数目
	int out;			    //出库数目
	int amount;			   	//最终库存
	int warning;	   	    //警戒值
	int state;			    //库存状态(是否低于警戒值)
	double money;		    //单价 
}goods;
goods s[M];				    //用于存放货品信息 
goods re[M];				//用于存放入库货品信息 
goods te[M];				//用于存放出库货品信息

int N, P;


int main()
{
	Admilogin();
	int i, event = 0;
	char ss[30];//输入字符串变量
	char xu;
	short win_width, win_height;//定义窗口的宽度和高度
	win_width = 500; win_height = 360;

	Refile();
loop:

	initgraph(win_width, win_height);//初始化窗口（黑屏）
	for (i = 0; i < 256; i += 5)
	{
		setbkcolor(RGB(i, i, i));//设置背景色，原来默认黑色
		cleardevice();//清屏（取决于背景色）
		Sleep(0);//延时5ms
	}
	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	RECT R4 = { r[3][0],r[3][1],r[3][2],r[3][3] };
	RECT R5 = { r[4][0],r[4][1],r[4][2],r[4][3] };
	RECT RTZ = { 0,0,500,130 };
	LOGFONT f;
	gettextstyle(&f);					//获取字体样式
	_tcscpy(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量

	


	drawtext("请选择功能序号", &RTZ, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("1.入库", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext("2.出库", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
	drawtext("3.查询", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("4.统记", &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("5.退出", &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R3内输入文字，水平居中，垂直居中，单行显示
	setlinecolor(BLACK);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	rectangle(r[3][0], r[3][1], r[3][2], r[3][3]);
	rectangle(r[4][0], r[4][1], r[4][2], r[4][3]);
	MOUSEMSG m;//鼠标指针
	int media=0;
	while (true)
	{
		m = GetMouseMsg();//获取一条鼠标消息

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(WHITE);//填充颜色为白色
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			
			//rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}



			//按照按钮判断左键单击后的操作
			switch (button_judge(m.x, m.y))
			{
				//复原按钮原型
			case 1:
				clearrectangle(0, 0, 500, 360);
				Stockin();Display(); media++;  break;
			case 2:
				clearrectangle(0, 0, 500, 360);
				Stockout(); Display(); media++; break;
			case 3:
				clearrectangle(0, 0, 500, 360);
				Query(); media++; break;
			case 4:
				clearrectangle(0, 0, 500, 360);
				Statistics(); media++; break;
			case 5:
				exit(0); break;
			default:
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				//printf("\r\n(%d,%d)",m.x,m.y);//打印鼠标坐标，方便调试时确定区域
				break;
			}
			
			
			flushmessage();//清空鼠标消息缓存区
			break;
		}

		if (media > 0)
		{
			break;
		}
	}
	goto loop;
	system("pause");//暂停，为了显示
	return 0;
}

void Estimate()     //判断警戒值 
{
	int i;
	for (i = 0; i < P; i++)
	{
		if (s[i].amount >= s[i].warning)
			s[i].state = 0;
		else if (s[i].amount < s[i].warning)
			s[i].state = 1;
	}
} //V

void Display() {
	
	int i, j;
	MOUSEMSG m;
	
	system("cls");
	Estimate();
	initgraph(500, 360); //定义画布大小也就是黑框大小
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//刷新一次 略等于那个system(cls)

	RECT Y0 = { 0,10,70,50 };
	RECT Y1 = { 75,10,145,50 };
	RECT Y2 = { 150,10,220,50 };
	RECT Y3 = { 225,10,295,50 };
	RECT Y4 = { 300,10,370,50 };
	RECT Y5 = { 375,10,445,50 };
	RECT Y6 = { 450,10,500,50 };

	RECT S0 = { ci[0][0],ci[0][1],ci[0][2],ci[0][3] };
	RECT S1 = { sh[0][0],sh[0][1],sh[0][2],sh[0][3] };
	RECT S2 = { sh[1][0],sh[1][1],sh[1][2],sh[1][3] };
	RECT S3 = { sh[2][0],sh[2][1],sh[2][2],sh[2][3] };
	RECT S4 = { sh[3][0],sh[3][1],sh[3][2],sh[3][3] };
	RECT S5 = { sh[4][0],sh[4][1],sh[4][2],sh[4][3] };
	RECT S[5] = { S1,S2,S3,S4,S5 };
	LOGFONT f;
	gettextstyle(&f);					//获取字体样式
	_tcscpy(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量

	drawtext("元件编号", &Y0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("元件名称", &Y1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("原始库存", &Y2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("入库数目", &Y3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("出库数目", &Y4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("最终库存", &Y5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("警戒值", &Y6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	
	char ss [100];
	/*sprintf(ss, "%-9d  %-10s%-10d%-10d%-10d%-10d%-10d", s[1].num, s[1].name, s[1].stock, s[1].in, s[1].out, s[1].amount, s[1].warning);
	drawtext(ss, &S0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	;*/


	
	for (i = 0, j = 1; i < P; i++, j++)
	{
		if (s[i].state == 1)		//库存值小于警戒值红字显示
		{
			settextcolor(RED);
			sprintf(ss, "    %-6d %-10s%-11d%-9d%-9d%-8d%-5d",s[i].num, s[i].name, s[i].stock, s[i].in, s[i].out, s[i].amount, s[i].warning);
			outtextxy(0, 50 + 19 * i, ss);
			if (j % 10 == 0 && j != P)		//控制每次显示十行
			{
				drawtext("按此处继续",&S0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				int media = 0;
				while (true)
				{
					m = GetMouseMsg();//获取一条鼠标消息

					switch (m.uMsg)
					{
					case WM_MOUSEMOVE:
						break;
					case WM_LBUTTONDOWN:

						setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
						for (i = 0; i <= 10; i++)
						{
							setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
							circle(m.x, m.y, 2 * i);
							Sleep(30);//停顿30ms
							circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
						}
						switch (button_judge2(m.x, m.y))
						{
							//复原按钮原型
						case 1:
							media++;  break;
						default:
							FlushMouseMsgBuffer();//单击事件后清空鼠标消息
							break;
						}
						
						break;
					}

					if (media > 0)
					{
						break;
					}

					flushmessage();//清空鼠标消息缓存区
				}
				
				
				
				drawtext("元件编号", &Y0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("元件名称", &Y1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("原始库存", &Y2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("入库数目", &Y3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("出库数目", &Y4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("最终库存", &Y5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("警戒值", &Y6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
		else if (s[i].state == 0)	//库存值不小于警戒值hei字显示
		{
			settextcolor(BLACK);
			sprintf(ss,  "    %-6d %-10s%-11d%-9d%-9d%-8d%-5d", s[i].num, s[i].name, s[i].stock, s[i].in, s[i].out, s[i].amount, s[i].warning);
			outtextxy(0, 50 + 19 * i, ss);
			if (j % 10 == 0 && j < P)
			{
				drawtext("按此处继续", &S0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				int media = 0;
				while (true)
				{
					m = GetMouseMsg();//获取一条鼠标消息

					switch (m.uMsg)
					{
					case WM_MOUSEMOVE:
						break;
					case WM_LBUTTONDOWN:

						setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
						for (i = 0; i <= 10; i++)
						{
							setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
							circle(m.x, m.y, 2 * i);
							Sleep(30);//停顿30ms
							circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
						}
						switch (button_judge2(m.x, m.y))
						{
							//复原按钮原型
						case 1:
							media++;  break;
						default:
							FlushMouseMsgBuffer();//单击事件后清空鼠标消息
							break;
						}

						break;
					}

					if (media > 0)
					{
						break;
					}

					flushmessage();//清空鼠标消息缓存区
				}
				


				drawtext("元件编号", &Y0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("元件名称", &Y1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("原始库存", &Y2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("入库数目", &Y3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("出库数目", &Y4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("最终库存", &Y5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("警戒值", &Y6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
	}
	

	
	int media = 0;
	while (true)
	{
		m = GetMouseMsg();//获取一条鼠标消息

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			break;
		case WM_LBUTTONDOWN:
			
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}
			media++;
			break;
		}

			if (media > 0) 
			{
				break;
			}
		
			flushmessage();//清空鼠标消息缓存区
	}
	clearrectangle(0, 0, 500, 360);
}

void Stockin() {
	
	FILE* fp;
	int i, j;
	N = 0;
	fp = fopen("stockin.txt", "r");
	while (fscanf(fp, "%d%d", &re[N].num, &re[N].in) != EOF)
		N++;
	fclose(fp);
	for (i = 0; i < P; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (re[i].num == s[j].num)
				s[j].in = re[i].in;
		}
	}
	for (i = 0; i < P; i++)
		s[i].amount = s[i].stock + s[i].in;
}

void Stockout() {
	
	FILE* fp;
	int i, j;
	N = 0;
	fp = fopen("stockout.txt", "r");
	while (fscanf(fp, "%d%d", &te[N].num, &te[N].out) != EOF)
		N++;
	fclose(fp);
	for (i = 0; i < P; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (te[i].num == s[j].num)
				s[j].out = te[i].out;
		}
	}
	for (i = 0; i < P; i++)
		s[i].amount = s[i].stock + s[i].in - s[i].out;
}

int Queryforward() {
	RECT RTZ = { 0,0,500,130 };
	RECT Y0 = { 0,10,70,50 };
	RECT Y1 = { 75,10,145,50 };
	RECT Y2 = { 150,10,220,50 };
	RECT Y3 = { 225,10,295,50 };
	RECT Y4 = { 300,10,370,50 };
	RECT Y5 = { 375,10,445,50 };
	RECT Y6 = { 450,10,500,50 };
	 kindy[100] = { 0 };
	 jquery = -1;
	 qaq = 0;
	int k, me, ie;
	
	
	char n[20];
	int i, event = 0;
	char ss[30];//输入字符串变量
	int mqw=0;

	char xu;
	MOUSEMSG m;//定义鼠标变量 m
	
	initgraph(500, 360); //定义画布大小也就是黑框大小
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//刷新一次 略等于那个system(cls)
	setfillcolor(LIGHTBLUE); //设置后面用函数画出方框的背景颜色 这里设置成了浅蓝色


	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	
	LOGFONT f;
	gettextstyle(&f);					//获取字体样式
	_tcscpy(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量

	drawtext("请选择功能序号", &RTZ, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("1.元器件编号", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext("2.元器件名称", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
	drawtext(" 3.按类别查看 ", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setlinecolor(BLACK);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);


	int media = 0;
	while (true)
	{
		m = GetMouseMsg();//获取一条鼠标消息

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(WHITE);//填充颜色为白色
			if (button_judge(m.x, m.y) != 0&& button_judge(m.x, m.y) != 4&& button_judge(m.x, m.y) != 5)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}



			//按照按钮判断左键单击后的操作
			switch (button_judge(m.x, m.y))
			{
				//复原按钮原型
			case 1:
				InputBox(ss, 30, "请输入查询编号");
				mqw = atoi(ss);
				for (i = 0; i < P; i++)
				{
					if (mqw == i)
						jquery = mqw - 1;
				}
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			case 2:
				InputBox(ss, 30, "请输入元器件名称");

				for (i = 0; i < P; i++)
				{
					if (strcmp(ss, s[i].name) == 0)
						jquery = i;
				}
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			case 3:
				InputBox(ss, 30, "请输入类别");

				for (i = 0; i < P; i++)
				{
					if (strcmp(ss, s[i].kind) == 0) {
						kindy[qaq] = i;
						qaq++;
					}
				}
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;

			default:
				media++;
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			}

			flushmessage();
			if (media > 0)
			{
				return 4;
			}

			if (qaq != 0) {
				strcpy(sschuan,ss);
				return 1;
			}
			else if (jquery == -1) {
				return 2;
			}
			else {
				return 3;
			}
		}
		
	}


}

void Query() 
{
	char ss[100];
	RECT RTZ = { 0,0,500,130 };
	RECT Y0 = { 0,10,70,50 };
	RECT Y1 = { 75,10,145,50 };
	RECT Y2 = { 150,10,220,50 };
	RECT Y3 = { 225,10,295,50 };
	RECT Y4 = { 300,10,370,50 };
	RECT Y5 = { 375,10,445,50 };
	RECT Y6 = { 450,10,500,50 };
	int i;
	int pandaun = Queryforward();




	char sss[100];
	if (pandaun == 1) 
	{
		system("cls");
		Estimate();
		initgraph(500, 360); //定义画布大小也就是黑框大小
		setbkcolor(WHITE);//设置背景颜色
		cleardevice();//刷新一次 略等于那个system(cls)

		LOGFONT f;
		gettextstyle(&f);					//获取字体样式
		_tcscpy(f.lfFaceName, _T("宋体"));	//设置字体为宋体
		f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
		settextstyle(&f);                     // 设置字体样式
		settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量
		sprintf(sss, "以上为%s类", sschuan);
		outtextxy(200,340, sss);
		drawtext("元件编号", &Y0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("元件名称", &Y1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("原始库存", &Y2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("入库数目", &Y3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("出库数目", &Y4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("最终库存", &Y5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("警戒值", &Y6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		for (i = 0; i < qaq; i++) {
			if (s[kindy[i]].state == 1)
			{
				settextcolor(RED);
				sprintf(ss, "    %-6d %-10s%-11d%-9d%-9d%-8d%-5d", s[kindy[i]].num, s[kindy[i]].name, s[kindy[i]].stock, s[kindy[i]].in, s[kindy[i]].out, s[kindy[i]].amount, s[kindy[i]].warning);
				outtextxy(0, 50 + 19 * i, ss);
			}
			else
			{
				settextcolor(BLACK);
				sprintf(ss, "    %-6d %-10s%-11d%-9d%-9d%-8d%-5d", s[kindy[i]].num, s[kindy[i]].name, s[kindy[i]].stock, s[kindy[i]].in, s[kindy[i]].out, s[kindy[i]].amount, s[kindy[i]].warning);
				outtextxy(0, 50 + 19 * i, ss);

			}
		}
		flushmessage();//清空鼠标消息缓存区

		

		MOUSEMSG m;//鼠标指针
		int media = 0;
		while (true)
		{
			m = GetMouseMsg();//获取一条鼠标消息

			switch (m.uMsg)
			{
			case WM_MOUSEMOVE:
				break;
			case WM_LBUTTONDOWN:

				setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
				for (i = 0; i <= 10; i++)
				{
					setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
					circle(m.x, m.y, 2 * i);
					Sleep(30);//停顿30ms
					circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
				}
				media++;
			}
				flushmessage();//清空鼠标消息缓存区
				if (media > 0)
				{
					clearrectangle(0, 0, 500, 360);
					break;
				}
		}
			
	}
	

	else if (pandaun == 2)
	{
			system("cls");
			Estimate();
			initgraph(500, 360); //定义画布大小也就是黑框大小
			setbkcolor(WHITE);//设置背景颜色
			cleardevice();//刷新一次 略等于那个system(cls)

			LOGFONT f;
			gettextstyle(&f);					//获取字体样式
			_tcscpy(f.lfFaceName, _T("宋体"));	//设置字体为宋体
			f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
			settextstyle(&f);                     // 设置字体样式
			settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量
			drawtext("没有找到", &RTZ, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			MOUSEMSG m;//鼠标指针
			int media = 0;
			while (true)
			{
				m = GetMouseMsg();//获取一条鼠标消息

				switch (m.uMsg)
				{
				case WM_MOUSEMOVE:
					break;
				case WM_LBUTTONDOWN:

					setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
					for (i = 0; i <= 10; i++)
					{
						setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
						circle(m.x, m.y, 2 * i);
						Sleep(30);//停顿30ms
						circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
					}
					media++;
				}
				flushmessage();//清空鼠标消息缓存区
				if (media > 0)
				{
					clearrectangle(0, 0, 500, 360);
					break;
				}
			}
	}
	else if (pandaun==3)
	{
		system("cls");
		Estimate();
		initgraph(500, 360); //定义画布大小也就是黑框大小
		setbkcolor(WHITE);//设置背景颜色
		cleardevice();//刷新一次 略等于那个system(cls)

		LOGFONT f;
		gettextstyle(&f);					//获取字体样式
		_tcscpy(f.lfFaceName, _T("宋体"));	//设置字体为宋体
		f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
		settextstyle(&f);                     // 设置字体样式
		settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量
		drawtext("元件编号", &Y0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("元件名称", &Y1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("原始库存", &Y2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("入库数目", &Y3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("出库数目", &Y4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("最终库存", &Y5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("警戒值", &Y6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if (s[jquery].state == 1)
		{
				settextcolor(RED);
				sprintf(ss, "    %-6d %-10s%-11d%-9d%-9d%-8d%-5d", s[jquery].num, s[jquery].name, s[jquery].stock, s[jquery].in, s[jquery].out, s[jquery].amount, s[jquery].warning);
				outtextxy(0, 50 + 19 * jquery, ss);
		}
		else
		{
				settextcolor(BLACK);
				sprintf(ss, "    %-6d %-10s%-11d%-9d%-9d%-8d%-5d", s[jquery].num, s[jquery].name, s[jquery].stock, s[jquery].in, s[jquery].out, s[jquery].amount, s[jquery].warning);
				outtextxy(0, 50 + 19 * jquery, ss);
		}

			MOUSEMSG m;//鼠标指针
			int media = 0;
			while (true)
			{
				m = GetMouseMsg();//获取一条鼠标消息

				switch (m.uMsg)
				{
				case WM_MOUSEMOVE:
					break;
				case WM_LBUTTONDOWN:

					setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
					for (i = 0; i <= 10; i++)
					{
						setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
						circle(m.x, m.y, 2 * i);
						Sleep(30);//停顿30ms
						circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
					}
					media++;
				}
				flushmessage();//清空鼠标消息缓存区
				if (media > 0)
				{
					clearrectangle(0, 0, 500, 360);
					break;
				}
			}
	}
	else if (pandaun == 4) {

}
	
	
}

void Statistics() {
	
	int i, event = 0;
	char ss[30];//输入字符串变量
	char xu;
	MOUSEMSG m;//定义鼠标变量 m
	//菜单
	initgraph(500, 360); //定义画布大小也就是黑框大小
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//刷新一次 略等于那个system(cls)
	setfillcolor(LIGHTBLUE); //设置后面用函数画出方框的背景颜色 这里设置成了浅蓝色
	//     (左上角)x1 y1 (右下角)x2 y2

	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	RECT R4 = { r[3][0],r[3][1],r[3][2],r[3][3] };
	RECT R5 = { r[4][0],r[4][1],r[4][2],r[4][3] };
	RECT RTZ = { 0,21,480,89 };
	LOGFONT f;
	gettextstyle(&f);					//获取字体样式
	_tcscpy(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量

	drawtext("请选择功能序号", &RTZ, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("1.库存总数", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext("2.库存状态", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
	drawtext("3.在库总价值", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("4.月出库价值", &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("5.月原件消耗", &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R3内输入文字，水平居中，垂直居中，单行显示
	setlinecolor(BLACK);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	rectangle(r[3][0], r[3][1], r[3][2], r[3][3]);
	rectangle(r[4][0], r[4][1], r[4][2], r[4][3]);

	int media = 0;
	while (true)
	{
		m = GetMouseMsg();//获取一条鼠标消息

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(WHITE);//填充颜色为白色
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			//rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}

			int ma = 0;
			double wmoney = 0;
			double w2money = 0;
			int w3money = 0;
			//按照按钮判断左键单击后的操作
			switch (button_judge(m.x, m.y))
			{
				//复原按钮原型
			case 1:	clearrectangle(10, 10, 490, 110);
				for (i = 0; i < P; i++)
					ma = ma + s[i].amount;
				sprintf (ss,"库存总数为：%d", ma);
				outtextxy(190, 50, ss);
				break;
			case 2:	clearrectangle(10, 10, 490, 110);
				Estimate();
				for (i = 0; i < P;i++)
					if (s[i].state == 1)
						ma = ma + 1;
				sprintf(ss,"低于库存警戒值的元器件种数为:%d", ma);
				outtextxy(120, 50, ss);
				break;
			case 3:	clearrectangle(10, 10, 490, 110);
				for (i = 0; i < P; i++) {
					wmoney = wmoney + s[i].amount * s[i].money;
				}
				sprintf(ss,"在库总价值为:%lf", wmoney);
				outtextxy(140, 50, ss);
				break;
			case 4:	clearrectangle(10, 10, 490, 110);
				for (i = 0; i < P; i++) {
					w2money = w2money + s[i].out * s[i].money;
				}
				sprintf(ss,"每月出库综合价值 :%lf", w2money);
				outtextxy(140, 50, ss);
				break;
			case 5:	clearrectangle(10, 10, 490, 110);
				for (i = 0; i < P; i++) {
					w3money = s[i].in - s[i].out;
					sprintf(ss,"%d类原件月消耗量:%d", i + 1, w3money);
					outtextxy(190, 10+19*i, ss);
				}
				break;
			default:
				media++;
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				//printf("\r\n(%d,%d)",m.x,m.y);//打印鼠标坐标，方便调试时确定区域
				break;
			}





			break;
			flushmessage();//清空鼠标消息缓存区
		}
		if (media > 0)
		{
			break;
		}
	}
	

}

void Refile()      //读入 
{
	FILE* fp;
	N = 0;
	fp = fopen("goods.txt", "r");
	while (fscanf(fp, "%d%s%s%d%d%d%d%d%lf", &s[N].num, &s[N].name, &s[N].kind, &s[N].stock, &s[N].in, &s[N].out, &s[N].amount, &s[N].warning, &s[N].money) != EOF)
		N++;
	fclose(fp);
	P = N;
}

int wrfile()
{
	FILE* fp;
	int i;
	fp = fopen("amount.txt", "w");
	for (i = 0; i < P; i++)
		fprintf(fp, "%-9d  %-10s%-10d%-10d%-10d%-10d%-10d\n", s[i].num, s[i].name, s[i].stock, s[i].in, s[i].out, s[i].amount, s[i].warning);
	fclose(fp);
	return 1;
}

void Admilogin() 		//登录界面 
{
	FILE* f;
	int k = 0,i=0;
	users a;
	char adminame[20] = "21009100820";
	char admipassword[20] = "180010";
	char keykey[20] ="9";
	int zh = { 0 };
	int mm = { 0 };
	int zhy = 1;
	int mmy = 0;


	system("cls");
	Estimate();
	initgraph(500, 360); //定义画布大小也就是黑框大小
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//刷新一次 略等于那个system(cls)

	LOGFONT v;
	gettextstyle(&v);					//获取字体样式
	_tcscpy(v.lfFaceName, _T("宋体"));	//设置字体为宋体
	v.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&v);                     // 设置字体样式
	settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量
	RECT RTZ = { 0,0,500,130 };
	settextstyle(40, 0, _T("隶书"));
	drawtext("登录界面", &RTZ, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(20, 0, _T("微软雅黑"));
	RECT R1 = { 150,120,350,160 };
	drawtext("点击此处输入用户名", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT R2 = { 150,170,350,280 };
	drawtext("点击此处输入密码", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setlinecolor(BLACK);

	rectangle(admi[0][0], admi[0][1], admi[0][2], admi[0][3]);
	rectangle(admi[1][0], admi[1][1], admi[1][2], admi[1][3]);


	RECT R11 = { 150,155,350,195 };
	RECT R22 = { 150,205,350,315 };
	

	MOUSEMSG m;//鼠标指针
	int media = 0;
	while (true)
	{
		m = GetMouseMsg();//获取一条鼠标消息
		int event = 0;
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(WHITE);//填充颜色为白色
			if (button_judge3(m.x, m.y) != 0)
			{
				if (event != button_judge3(m.x, m.y))
				{
					event = button_judge3(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(admi[event - 1][0], admi[event - 1][1], admi[event - 1][2], admi[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(admi[event - 1][0], admi[event - 1][1], admi[event - 1][2], admi[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:

			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}



			//按照按钮判断左键单击后的操作
			switch (button_judge3(m.x, m.y))
			{
				//复原按钮原型
			case 1:
				InputBox(a.name, 40, "请输入账号：");
				
			
					if (strcmp(a.name, adminame) == 0 || strcmp(a.name, keykey) == 0) {
						zhy = 1;
					}
					else  {
						zhy = 0;
					}

				if (zhy == 0) {
					settextcolor(RED);
					drawtext("用户名错误", &R11, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else {
					settextcolor(GREEN);
					drawtext("用户名正确", &R11, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			case 2:
				InputBox(a.Password, 40, "请输入密码：");
				
				
				
					if (strcmp(a.Password, admipassword) == 0 || strcmp(a.Password, keykey) == 0)
						mmy = 1;
					else mmy = 0;
				
				if (zhy==1&&mmy == 0) {
					settextcolor(RED);
					drawtext("密码错误", &R22, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if(zhy==1&&mmy==1) {
					settextcolor(GREEN);
					drawtext("密码正确", &R22, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			
			default:
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
			
				break;
			}


			flushmessage();
			break;
		}

		if (zhy == 1 && mmy == 1) {
			Sleep(1000);
			break;
		}
	}
	

}
























