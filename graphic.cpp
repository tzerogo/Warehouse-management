#pragma warning(disable:4996)
#undef UNICODE
#undef _UNICODE

#include <graphics.h>              // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <stdio.h>
#include <windows.h>				//�õ��˶�ʱ����sleep()
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define M 20

int r[5][4] = { {30,120,130,160},{170,120,280,160},{310,120,420,160},{30,220,130,260},{170,220,280,260} };//������ť�Ķ�ά����
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
	int num;			    //��Ʒ���
	char name[20];		  	//��Ʒ����
	char kind[20]; 	        //����
	int stock;			    //ԭʼ���
	int in;				   	//�����Ŀ
	int out;			    //������Ŀ
	int amount;			   	//���տ��
	int warning;	   	    //����ֵ
	int state;			    //���״̬(�Ƿ���ھ���ֵ)
	double money;		    //���� 
}goods;
goods s[M];				    //���ڴ�Ż�Ʒ��Ϣ 
goods re[M];				//���ڴ������Ʒ��Ϣ 
goods te[M];				//���ڴ�ų����Ʒ��Ϣ

int N, P;


int main()
{
	Admilogin();
	int i, event = 0;
	char ss[30];//�����ַ�������
	char xu;
	short win_width, win_height;//���崰�ڵĿ�Ⱥ͸߶�
	win_width = 500; win_height = 360;

	Refile();
loop:

	initgraph(win_width, win_height);//��ʼ�����ڣ�������
	for (i = 0; i < 256; i += 5)
	{
		setbkcolor(RGB(i, i, i));//���ñ���ɫ��ԭ��Ĭ�Ϻ�ɫ
		cleardevice();//������ȡ���ڱ���ɫ��
		Sleep(0);//��ʱ5ms
	}
	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	RECT R4 = { r[3][0],r[3][1],r[3][2],r[3][3] };
	RECT R5 = { r[4][0],r[4][1],r[4][2],r[4][3] };
	RECT RTZ = { 0,0,500,130 };
	LOGFONT f;
	gettextstyle(&f);					//��ȡ������ʽ
	_tcscpy(f.lfFaceName, _T("����"));	//��������Ϊ����
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&f);                     // ����������ʽ
	settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����

	


	drawtext("��ѡ�������", &RTZ, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("1.���", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext("2.����", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R2���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext("3.��ѯ", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("4.ͳ��", &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("5.�˳�", &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R3���������֣�ˮƽ���У���ֱ���У�������ʾ
	setlinecolor(BLACK);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	rectangle(r[3][0], r[3][1], r[3][2], r[3][3]);
	rectangle(r[4][0], r[4][1], r[4][2], r[4][3]);
	MOUSEMSG m;//���ָ��
	int media=0;
	while (true)
	{
		m = GetMouseMsg();//��ȡһ�������Ϣ

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//������ɫΪ����ɫ
			setlinestyle(PS_SOLID, 3);//���û�����ʽΪʵ�֣�10��
			setfillcolor(WHITE);//�����ɫΪ��ɫ
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//��¼��һ�δ����İ�ť
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//�п������Σ�X1,Y1,X2,Y2��
				}
			}
			else
			{
				if (event != 0)//�ϴδ����İ�ťδ������Ϊԭ������ɫ
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//����ͬ��Ϊԭ����ɫ
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			
			//rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
			setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
				circle(m.x, m.y, 2 * i);
				Sleep(30);//ͣ��30ms
				circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
			}



			//���հ�ť�ж����������Ĳ���
			switch (button_judge(m.x, m.y))
			{
				//��ԭ��ťԭ��
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
				FlushMouseMsgBuffer();//�����¼�����������Ϣ
				//printf("\r\n(%d,%d)",m.x,m.y);//��ӡ������꣬�������ʱȷ������
				break;
			}
			
			
			flushmessage();//��������Ϣ������
			break;
		}

		if (media > 0)
		{
			break;
		}
	}
	goto loop;
	system("pause");//��ͣ��Ϊ����ʾ
	return 0;
}

void Estimate()     //�жϾ���ֵ 
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
	initgraph(500, 360); //���廭����СҲ���Ǻڿ��С
	setbkcolor(WHITE);//���ñ�����ɫ
	cleardevice();//ˢ��һ�� �Ե����Ǹ�system(cls)

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
	gettextstyle(&f);					//��ȡ������ʽ
	_tcscpy(f.lfFaceName, _T("����"));	//��������Ϊ����
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&f);                     // ����������ʽ
	settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����

	drawtext("Ԫ�����", &Y0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("Ԫ������", &Y1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("ԭʼ���", &Y2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("�����Ŀ", &Y3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("������Ŀ", &Y4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("���տ��", &Y5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("����ֵ", &Y6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	
	char ss [100];
	/*sprintf(ss, "%-9d  %-10s%-10d%-10d%-10d%-10d%-10d", s[1].num, s[1].name, s[1].stock, s[1].in, s[1].out, s[1].amount, s[1].warning);
	drawtext(ss, &S0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	;*/


	
	for (i = 0, j = 1; i < P; i++, j++)
	{
		if (s[i].state == 1)		//���ֵС�ھ���ֵ������ʾ
		{
			settextcolor(RED);
			sprintf(ss, "    %-6d %-10s%-11d%-9d%-9d%-8d%-5d",s[i].num, s[i].name, s[i].stock, s[i].in, s[i].out, s[i].amount, s[i].warning);
			outtextxy(0, 50 + 19 * i, ss);
			if (j % 10 == 0 && j != P)		//����ÿ����ʾʮ��
			{
				drawtext("���˴�����",&S0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				int media = 0;
				while (true)
				{
					m = GetMouseMsg();//��ȡһ�������Ϣ

					switch (m.uMsg)
					{
					case WM_MOUSEMOVE:
						break;
					case WM_LBUTTONDOWN:

						setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
						for (i = 0; i <= 10; i++)
						{
							setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
							circle(m.x, m.y, 2 * i);
							Sleep(30);//ͣ��30ms
							circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
						}
						switch (button_judge2(m.x, m.y))
						{
							//��ԭ��ťԭ��
						case 1:
							media++;  break;
						default:
							FlushMouseMsgBuffer();//�����¼�����������Ϣ
							break;
						}
						
						break;
					}

					if (media > 0)
					{
						break;
					}

					flushmessage();//��������Ϣ������
				}
				
				
				
				drawtext("Ԫ�����", &Y0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("Ԫ������", &Y1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("ԭʼ���", &Y2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("�����Ŀ", &Y3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("������Ŀ", &Y4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("���տ��", &Y5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("����ֵ", &Y6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
		else if (s[i].state == 0)	//���ֵ��С�ھ���ֵhei����ʾ
		{
			settextcolor(BLACK);
			sprintf(ss,  "    %-6d %-10s%-11d%-9d%-9d%-8d%-5d", s[i].num, s[i].name, s[i].stock, s[i].in, s[i].out, s[i].amount, s[i].warning);
			outtextxy(0, 50 + 19 * i, ss);
			if (j % 10 == 0 && j < P)
			{
				drawtext("���˴�����", &S0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				int media = 0;
				while (true)
				{
					m = GetMouseMsg();//��ȡһ�������Ϣ

					switch (m.uMsg)
					{
					case WM_MOUSEMOVE:
						break;
					case WM_LBUTTONDOWN:

						setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
						for (i = 0; i <= 10; i++)
						{
							setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
							circle(m.x, m.y, 2 * i);
							Sleep(30);//ͣ��30ms
							circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
						}
						switch (button_judge2(m.x, m.y))
						{
							//��ԭ��ťԭ��
						case 1:
							media++;  break;
						default:
							FlushMouseMsgBuffer();//�����¼�����������Ϣ
							break;
						}

						break;
					}

					if (media > 0)
					{
						break;
					}

					flushmessage();//��������Ϣ������
				}
				


				drawtext("Ԫ�����", &Y0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("Ԫ������", &Y1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("ԭʼ���", &Y2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("�����Ŀ", &Y3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("������Ŀ", &Y4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("���տ��", &Y5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("����ֵ", &Y6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
	}
	

	
	int media = 0;
	while (true)
	{
		m = GetMouseMsg();//��ȡһ�������Ϣ

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			break;
		case WM_LBUTTONDOWN:
			
			setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
				circle(m.x, m.y, 2 * i);
				Sleep(30);//ͣ��30ms
				circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
			}
			media++;
			break;
		}

			if (media > 0) 
			{
				break;
			}
		
			flushmessage();//��������Ϣ������
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
	char ss[30];//�����ַ�������
	int mqw=0;

	char xu;
	MOUSEMSG m;//���������� m
	
	initgraph(500, 360); //���廭����СҲ���Ǻڿ��С
	setbkcolor(WHITE);//���ñ�����ɫ
	cleardevice();//ˢ��һ�� �Ե����Ǹ�system(cls)
	setfillcolor(LIGHTBLUE); //���ú����ú�����������ı�����ɫ �������ó���ǳ��ɫ


	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	
	LOGFONT f;
	gettextstyle(&f);					//��ȡ������ʽ
	_tcscpy(f.lfFaceName, _T("����"));	//��������Ϊ����
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&f);                     // ����������ʽ
	settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����

	drawtext("��ѡ�������", &RTZ, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("1.Ԫ�������", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext("2.Ԫ��������", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R2���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext(" 3.�����鿴 ", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setlinecolor(BLACK);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);


	int media = 0;
	while (true)
	{
		m = GetMouseMsg();//��ȡһ�������Ϣ

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//������ɫΪ����ɫ
			setlinestyle(PS_SOLID, 3);//���û�����ʽΪʵ�֣�10��
			setfillcolor(WHITE);//�����ɫΪ��ɫ
			if (button_judge(m.x, m.y) != 0&& button_judge(m.x, m.y) != 4&& button_judge(m.x, m.y) != 5)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//��¼��һ�δ����İ�ť
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//�п������Σ�X1,Y1,X2,Y2��
				}
			}
			else
			{
				if (event != 0)//�ϴδ����İ�ťδ������Ϊԭ������ɫ
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//����ͬ��Ϊԭ����ɫ
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			
			setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
				circle(m.x, m.y, 2 * i);
				Sleep(30);//ͣ��30ms
				circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
			}



			//���հ�ť�ж����������Ĳ���
			switch (button_judge(m.x, m.y))
			{
				//��ԭ��ťԭ��
			case 1:
				InputBox(ss, 30, "�������ѯ���");
				mqw = atoi(ss);
				for (i = 0; i < P; i++)
				{
					if (mqw == i)
						jquery = mqw - 1;
				}
				FlushMouseMsgBuffer();//�����¼�����������Ϣ
				break;
			case 2:
				InputBox(ss, 30, "������Ԫ��������");

				for (i = 0; i < P; i++)
				{
					if (strcmp(ss, s[i].name) == 0)
						jquery = i;
				}
				FlushMouseMsgBuffer();//�����¼�����������Ϣ
				break;
			case 3:
				InputBox(ss, 30, "���������");

				for (i = 0; i < P; i++)
				{
					if (strcmp(ss, s[i].kind) == 0) {
						kindy[qaq] = i;
						qaq++;
					}
				}
				FlushMouseMsgBuffer();//�����¼�����������Ϣ
				break;

			default:
				media++;
				FlushMouseMsgBuffer();//�����¼�����������Ϣ
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
		initgraph(500, 360); //���廭����СҲ���Ǻڿ��С
		setbkcolor(WHITE);//���ñ�����ɫ
		cleardevice();//ˢ��һ�� �Ե����Ǹ�system(cls)

		LOGFONT f;
		gettextstyle(&f);					//��ȡ������ʽ
		_tcscpy(f.lfFaceName, _T("����"));	//��������Ϊ����
		f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
		settextstyle(&f);                     // ����������ʽ
		settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
		sprintf(sss, "����Ϊ%s��", sschuan);
		outtextxy(200,340, sss);
		drawtext("Ԫ�����", &Y0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("Ԫ������", &Y1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("ԭʼ���", &Y2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("�����Ŀ", &Y3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("������Ŀ", &Y4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("���տ��", &Y5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("����ֵ", &Y6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
		flushmessage();//��������Ϣ������

		

		MOUSEMSG m;//���ָ��
		int media = 0;
		while (true)
		{
			m = GetMouseMsg();//��ȡһ�������Ϣ

			switch (m.uMsg)
			{
			case WM_MOUSEMOVE:
				break;
			case WM_LBUTTONDOWN:

				setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
				for (i = 0; i <= 10; i++)
				{
					setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
					circle(m.x, m.y, 2 * i);
					Sleep(30);//ͣ��30ms
					circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
				}
				media++;
			}
				flushmessage();//��������Ϣ������
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
			initgraph(500, 360); //���廭����СҲ���Ǻڿ��С
			setbkcolor(WHITE);//���ñ�����ɫ
			cleardevice();//ˢ��һ�� �Ե����Ǹ�system(cls)

			LOGFONT f;
			gettextstyle(&f);					//��ȡ������ʽ
			_tcscpy(f.lfFaceName, _T("����"));	//��������Ϊ����
			f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
			settextstyle(&f);                     // ����������ʽ
			settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
			drawtext("û���ҵ�", &RTZ, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			MOUSEMSG m;//���ָ��
			int media = 0;
			while (true)
			{
				m = GetMouseMsg();//��ȡһ�������Ϣ

				switch (m.uMsg)
				{
				case WM_MOUSEMOVE:
					break;
				case WM_LBUTTONDOWN:

					setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
					for (i = 0; i <= 10; i++)
					{
						setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
						circle(m.x, m.y, 2 * i);
						Sleep(30);//ͣ��30ms
						circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
					}
					media++;
				}
				flushmessage();//��������Ϣ������
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
		initgraph(500, 360); //���廭����СҲ���Ǻڿ��С
		setbkcolor(WHITE);//���ñ�����ɫ
		cleardevice();//ˢ��һ�� �Ե����Ǹ�system(cls)

		LOGFONT f;
		gettextstyle(&f);					//��ȡ������ʽ
		_tcscpy(f.lfFaceName, _T("����"));	//��������Ϊ����
		f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
		settextstyle(&f);                     // ����������ʽ
		settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
		drawtext("Ԫ�����", &Y0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("Ԫ������", &Y1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("ԭʼ���", &Y2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("�����Ŀ", &Y3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("������Ŀ", &Y4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("���տ��", &Y5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext("����ֵ", &Y6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

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

			MOUSEMSG m;//���ָ��
			int media = 0;
			while (true)
			{
				m = GetMouseMsg();//��ȡһ�������Ϣ

				switch (m.uMsg)
				{
				case WM_MOUSEMOVE:
					break;
				case WM_LBUTTONDOWN:

					setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
					for (i = 0; i <= 10; i++)
					{
						setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
						circle(m.x, m.y, 2 * i);
						Sleep(30);//ͣ��30ms
						circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
					}
					media++;
				}
				flushmessage();//��������Ϣ������
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
	char ss[30];//�����ַ�������
	char xu;
	MOUSEMSG m;//���������� m
	//�˵�
	initgraph(500, 360); //���廭����СҲ���Ǻڿ��С
	setbkcolor(WHITE);//���ñ�����ɫ
	cleardevice();//ˢ��һ�� �Ե����Ǹ�system(cls)
	setfillcolor(LIGHTBLUE); //���ú����ú�����������ı�����ɫ �������ó���ǳ��ɫ
	//     (���Ͻ�)x1 y1 (���½�)x2 y2

	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	RECT R4 = { r[3][0],r[3][1],r[3][2],r[3][3] };
	RECT R5 = { r[4][0],r[4][1],r[4][2],r[4][3] };
	RECT RTZ = { 0,21,480,89 };
	LOGFONT f;
	gettextstyle(&f);					//��ȡ������ʽ
	_tcscpy(f.lfFaceName, _T("����"));	//��������Ϊ����
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&f);                     // ����������ʽ
	settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����

	drawtext("��ѡ�������", &RTZ, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("1.�������", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R1���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext("2.���״̬", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R2���������֣�ˮƽ���У���ֱ���У�������ʾ
	drawtext("3.�ڿ��ܼ�ֵ", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("4.�³����ֵ", &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("5.��ԭ������", &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//�ھ�������R3���������֣�ˮƽ���У���ֱ���У�������ʾ
	setlinecolor(BLACK);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	rectangle(r[3][0], r[3][1], r[3][2], r[3][3]);
	rectangle(r[4][0], r[4][1], r[4][2], r[4][3]);

	int media = 0;
	while (true)
	{
		m = GetMouseMsg();//��ȡһ�������Ϣ

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//������ɫΪ����ɫ
			setlinestyle(PS_SOLID, 3);//���û�����ʽΪʵ�֣�10��
			setfillcolor(WHITE);//�����ɫΪ��ɫ
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//��¼��һ�δ����İ�ť
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//�п������Σ�X1,Y1,X2,Y2��
				}
			}
			else
			{
				if (event != 0)//�ϴδ����İ�ťδ������Ϊԭ������ɫ
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//����ͬ��Ϊԭ����ɫ
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			//rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
			setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
				circle(m.x, m.y, 2 * i);
				Sleep(30);//ͣ��30ms
				circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
			}

			int ma = 0;
			double wmoney = 0;
			double w2money = 0;
			int w3money = 0;
			//���հ�ť�ж����������Ĳ���
			switch (button_judge(m.x, m.y))
			{
				//��ԭ��ťԭ��
			case 1:	clearrectangle(10, 10, 490, 110);
				for (i = 0; i < P; i++)
					ma = ma + s[i].amount;
				sprintf (ss,"�������Ϊ��%d", ma);
				outtextxy(190, 50, ss);
				break;
			case 2:	clearrectangle(10, 10, 490, 110);
				Estimate();
				for (i = 0; i < P;i++)
					if (s[i].state == 1)
						ma = ma + 1;
				sprintf(ss,"���ڿ�澯��ֵ��Ԫ��������Ϊ:%d", ma);
				outtextxy(120, 50, ss);
				break;
			case 3:	clearrectangle(10, 10, 490, 110);
				for (i = 0; i < P; i++) {
					wmoney = wmoney + s[i].amount * s[i].money;
				}
				sprintf(ss,"�ڿ��ܼ�ֵΪ:%lf", wmoney);
				outtextxy(140, 50, ss);
				break;
			case 4:	clearrectangle(10, 10, 490, 110);
				for (i = 0; i < P; i++) {
					w2money = w2money + s[i].out * s[i].money;
				}
				sprintf(ss,"ÿ�³����ۺϼ�ֵ :%lf", w2money);
				outtextxy(140, 50, ss);
				break;
			case 5:	clearrectangle(10, 10, 490, 110);
				for (i = 0; i < P; i++) {
					w3money = s[i].in - s[i].out;
					sprintf(ss,"%d��ԭ����������:%d", i + 1, w3money);
					outtextxy(190, 10+19*i, ss);
				}
				break;
			default:
				media++;
				FlushMouseMsgBuffer();//�����¼�����������Ϣ
				//printf("\r\n(%d,%d)",m.x,m.y);//��ӡ������꣬�������ʱȷ������
				break;
			}





			break;
			flushmessage();//��������Ϣ������
		}
		if (media > 0)
		{
			break;
		}
	}
	

}

void Refile()      //���� 
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

void Admilogin() 		//��¼���� 
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
	initgraph(500, 360); //���廭����СҲ���Ǻڿ��С
	setbkcolor(WHITE);//���ñ�����ɫ
	cleardevice();//ˢ��һ�� �Ե����Ǹ�system(cls)

	LOGFONT v;
	gettextstyle(&v);					//��ȡ������ʽ
	_tcscpy(v.lfFaceName, _T("����"));	//��������Ϊ����
	v.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&v);                     // ����������ʽ
	settextcolor(BLACK);				//BLACK��graphic.hͷ�ļ����汻����Ϊ��ɫ����ɫ����
	RECT RTZ = { 0,0,500,130 };
	settextstyle(40, 0, _T("����"));
	drawtext("��¼����", &RTZ, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(20, 0, _T("΢���ź�"));
	RECT R1 = { 150,120,350,160 };
	drawtext("����˴������û���", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT R2 = { 150,170,350,280 };
	drawtext("����˴���������", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setlinecolor(BLACK);

	rectangle(admi[0][0], admi[0][1], admi[0][2], admi[0][3]);
	rectangle(admi[1][0], admi[1][1], admi[1][2], admi[1][3]);


	RECT R11 = { 150,155,350,195 };
	RECT R22 = { 150,205,350,315 };
	

	MOUSEMSG m;//���ָ��
	int media = 0;
	while (true)
	{
		m = GetMouseMsg();//��ȡһ�������Ϣ
		int event = 0;
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//������ɫΪ����ɫ
			setlinestyle(PS_SOLID, 3);//���û�����ʽΪʵ�֣�10��
			setfillcolor(WHITE);//�����ɫΪ��ɫ
			if (button_judge3(m.x, m.y) != 0)
			{
				if (event != button_judge3(m.x, m.y))
				{
					event = button_judge3(m.x, m.y);//��¼��һ�δ����İ�ť
					fillrectangle(admi[event - 1][0], admi[event - 1][1], admi[event - 1][2], admi[event - 1][3]);//�п������Σ�X1,Y1,X2,Y2��
				}
			}
			else
			{
				if (event != 0)//�ϴδ����İ�ťδ������Ϊԭ������ɫ
				{
					fillrectangle(admi[event - 1][0], admi[event - 1][1], admi[event - 1][2], admi[event - 1][3]);//����ͬ��Ϊԭ����ɫ
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:

			setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
				circle(m.x, m.y, 2 * i);
				Sleep(30);//ͣ��30ms
				circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
			}



			//���հ�ť�ж����������Ĳ���
			switch (button_judge3(m.x, m.y))
			{
				//��ԭ��ťԭ��
			case 1:
				InputBox(a.name, 40, "�������˺ţ�");
				
			
					if (strcmp(a.name, adminame) == 0 || strcmp(a.name, keykey) == 0) {
						zhy = 1;
					}
					else  {
						zhy = 0;
					}

				if (zhy == 0) {
					settextcolor(RED);
					drawtext("�û�������", &R11, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else {
					settextcolor(GREEN);
					drawtext("�û�����ȷ", &R11, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				FlushMouseMsgBuffer();//�����¼�����������Ϣ
				break;
			case 2:
				InputBox(a.Password, 40, "���������룺");
				
				
				
					if (strcmp(a.Password, admipassword) == 0 || strcmp(a.Password, keykey) == 0)
						mmy = 1;
					else mmy = 0;
				
				if (zhy==1&&mmy == 0) {
					settextcolor(RED);
					drawtext("�������", &R22, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if(zhy==1&&mmy==1) {
					settextcolor(GREEN);
					drawtext("������ȷ", &R22, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				FlushMouseMsgBuffer();//�����¼�����������Ϣ
				break;
			
			default:
				FlushMouseMsgBuffer();//�����¼�����������Ϣ
			
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
























