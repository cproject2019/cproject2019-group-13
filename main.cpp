#include <graphics.h>                   //ͼ�ο�
#include <conio.h>                      //ͼ�ο�
#include <easyx.h>                      //ͼ�ο�
#include <Windows.h>
#include "function declaration.h"
#include "classical.h"
#include "play.h"
#include "create.h"
#include "scorePlay.h"


//������
int main()
{
	//��������
	musicList();
	while (1) {
		begin();

		//��ʼ��Ϸ
		while (1)
		{	int x = login();
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			if (x == 1)
			{
				while (1)
				{
					int y = select();
					if (y == 1)//ԭ��������
						create();
					else if (y == 2)//������Ŀ��
						classical();
					else if (y == 3)//���ɵ�����
						play();
					else//����
					{
						LPCTSTR s = _T("û�д�ѡ�");
						outtextxy(320 - textwidth(s) / 2, 200, s);
					}
				}
			}

			//��Ϸ���
			else if (x == 2) {
				introduction();
			}
		}
	}

	//��������
	destory_list(head);
	return 0;
}

void begin(void) {
	static IMAGE bkimg;
	static char k = 1;
	if (k == 1) {
		initgraph(640, 460);
		loadimage(&bkimg, _T("ͼƬ�ز�\\����.jpg"));
		k = 0;
	}
	cleardevice();
	putimage(0, 0, &bkimg);

	settextcolor(BLUE);
	setbkmode(TRANSPARENT);		        // �������ֱ���Ϊ͸��ɫ
	settextstyle(50, 0, _T("΢���ź�"));
	LPCTSTR s1 = _T("MAGIC");
	outtextxy(450, 200, s1);
	LPCTSTR s2 = _T("PIANO");
	outtextxy(400, 250, s2);
	getch();

	static IMAGE bkimg2;
	static char k2 = 1;
	if (k2 == 1) {
		loadimage(&bkimg2, _T("ͼƬ�ز�\\��ӭ.jpg"));
		k2 = 0;
	}
	putimage(0, 0, &bkimg2);
	PlaySound(TEXT("�����ز�\\Welcome.wav"), NULL, SND_FILENAME | SND_ASYNC);

	Sleep(500);

	//��������
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);		        // �������ֱ���Ϊ͸��ɫ
	settextstyle(40, 0, _T("����"));
	LPCTSTR s31 = _T("W");
	outtextxy(100, 70, s31);
	Sleep(50);
	LPCTSTR s32 = _T("E");
	outtextxy(125, 70, s32);
	Sleep(50);
	LPCTSTR s33 = _T("L");
	outtextxy(150, 70, s33);
	Sleep(50);
	LPCTSTR s34 = _T("C");
	outtextxy(175, 70, s34);
	Sleep(50);
	LPCTSTR s35 = _T("O");
	outtextxy(200, 70, s35);
	Sleep(50);
	LPCTSTR s36 = _T("M");
	outtextxy(225, 70, s36);
	Sleep(50);
	LPCTSTR s37 = _T("E");
	outtextxy(250, 70, s37);
	Sleep(50);
	LPCTSTR s38 = _T("T");
	outtextxy(300, 70, s38);
	Sleep(50);
	LPCTSTR s39 = _T("O");
	outtextxy(325, 70, s39);

	Sleep(200);

	setbkmode(TRANSPARENT);		        // �������ֱ���Ϊ͸��ɫ
	settextstyle(60, 0, _T("΢���ź�"));
	LPCTSTR s51 = _T("M");
	outtextxy(270, 150, s51);
	Sleep(200);
	LPCTSTR s52 = _T("A");
	outtextxy(310, 150, s52);
	Sleep(200);
	LPCTSTR s53 = _T("G");
	outtextxy(340, 150, s53);
	Sleep(200);
	LPCTSTR s54 = _T("I");
	outtextxy(375, 150, s54);
	Sleep(200);
	LPCTSTR s55 = _T("C");
	outtextxy(395, 150, s55);
	Sleep(200);
	LPCTSTR s56 = _T("P");
	outtextxy(450, 150, s56);
	Sleep(200);
	LPCTSTR s57 = _T("I");
	outtextxy(480, 150, s57);
	Sleep(200);
	LPCTSTR s58 = _T("A");
	outtextxy(500, 150, s58);
	Sleep(200);
	LPCTSTR s59 = _T("N");
	outtextxy(530, 150, s59);
	Sleep(200);
	LPCTSTR s510 = _T("O");
	outtextxy(565, 150, s510);

	Sleep(500);

	settextcolor(WHITE);
	setbkmode(TRANSPARENT);		        // �������ֱ���Ϊ͸��ɫ
	settextstyle(30, 0, _T("΢���ź�"));
	LPCTSTR s4 = _T("���������ʼ");
	outtextxy(450, 370, s4);
	getch();
}

int login(void) {
	static IMAGE bkimg;
	static char k = 1;
	if (k == 1) {
		loadimage(&bkimg, _T("ͼƬ�ز�\\��¼����ͼ.jpg"));
		k = 0;
	}
	cleardevice();
	putimage(0, 0, &bkimg);

	settextcolor(WHITE);
	setbkmode(TRANSPARENT);		        // �������ֱ���Ϊ͸��ɫ
	settextstyle(30, 0, _T("΢���ź�"));
	LPCTSTR s = _T("��S��  ��ʼ��Ϸ");
	outtextxy(320 - textwidth(s) / 2, 100, s);
	LPCTSTR e = _T("��ESC��  �˳���Ϸ");
	outtextxy(320 - textwidth(e) / 2, 200, e);
	LPCTSTR i = _T("��I��  ��Ϸ���");
	outtextxy(320 - textwidth(i) / 2, 150, i);
	int result = -1;
	char c;
	while (1) {
		if (_kbhit) {
			c = _getch();
			if (c == 's') {
				result = 1;
				break;
			}
			else if (c == 27) exit(0);
			else if (c == 'i') {
				result = 2;
				break;
			}
		}
	}
	return result;
}

int select(void) {
	static IMAGE bkimg;
	static char k = 1;
	if (k == 1) {
		loadimage(&bkimg, _T("ͼƬ�ز�\\ѡ�����.jpg"));
		k = 0;
	}
	cleardevice();
	putimage(-200, 0, &bkimg);

	settextcolor(WHITE);
	setbkmode(TRANSPARENT);		        // �������ֱ���Ϊ͸��ɫ
	settextstyle(30, 0, _T("΢���ź�"));
	LPCTSTR y = _T("��Y��  ԭ��������");
	outtextxy(320 - textwidth(y) / 2, 100, y);
	LPCTSTR j = _T("��J��  ������Ŀ��");
	outtextxy(320 - textwidth(j) / 2, 150, j);
	LPCTSTR t = _T("��T��  ���ɵ�����");
	outtextxy(320 - textwidth(t) / 2, 200, t);
	int result = -1;
	char c;
	while (1) {
		if (_kbhit) {
			c = _getch();
			if (c == 'y') {
				result = 1;
				break;
			}
			else if (c == 'j') {
				result = 2;
				break;
			}
			else if (c == 't') {
				result = 3;
				break;
			}
			else if (c == 'g') {
				result = 4;
				break;
			}
		}
	}
	return result;
}

void introduction(void) {
	cleardevice();
	IMAGE bkimg;
	loadimage(&bkimg, _T("ͼƬ�ز�\\��鱳��ͼ.jpg"));
	putimage(0, 0, &bkimg);

	setbkmode(TRANSPARENT);		        // �������ֱ���Ϊ͸��ɫ
	settextstyle(40, 0, _T("΢���ź�"));
	outtextxy(20, 20, _T("��Ϸ˵��"));

	settextstyle(30, 0, _T("΢���ź�"));
	LPCTSTR s = _T("����ϷΪ������Ϸ");
	outtextxy(320 - textwidth(s) / 2 - 10, 50, s);
	LPCTSTR s0 = _T("��Ҫ��Ϊ������Ŀ����ԭ����Ŀ�������ɵ�����");
	outtextxy(320 - textwidth(s0) / 2 - 10, 90, s0);
	LPCTSTR s1 = _T("������Ŀ�����������ֻ�������");
	outtextxy(320 - textwidth(s1) / 2 - 10, 130, s1);
	LPCTSTR s2 = _T("ԭ����Ŀ�����Լ���������");
	outtextxy(320 - textwidth(s2) / 2 - 10, 170, s2);
	LPCTSTR s3 = _T("���ɵ���������������");
	outtextxy(320 - textwidth(s3) / 2 - 10, 210, s3);

	LPCTSTR p1 = _T("������");
	outtextxy(320 - textwidth(p1) / 2, 270, p1);
	LPCTSTR p2= _T("ESC����������");
	outtextxy(320 - textwidth(p2) / 2 - 10, 300, p2);

	while (1) {
		if (_kbhit()) {
			char c = _getch();
			if (c == 27) break;
		}
	}
}