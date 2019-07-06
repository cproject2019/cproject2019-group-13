#pragma once
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#define random() (rand())
#pragma comment(lib,"Winmm.lib")


int score = 0;         //�ܵ÷�
int comboscore = 0;    //��ǰcombo
int maxcomboscore = 0; //�������
int good_flag = 0;     //�Ƿ���ʾ GOOD ͼƬ
int restart = 0;       //�Ƿ����¿�ʼ��Ϸ


//���ͼƬ
void myoutimg(my_img* my, IMAGE *yanma)
{
	if (yanma == NULL)
	{
		// �ָ�����
		putimage(my->x, my->y, &my->before);
	}
	else
	{
		int w = my->img.getwidth();  	// ��ȡͼƬռ�õĿ��
		int h = my->img.getheight();	// ��ȡͼƬռ�õĸ߶�
		getimage(&my->before, my->x, my->y, w, h);		  // ��������
		// ͼƬ���
		putimage(my->x, my->y, yanma, SRCAND);
		putimage(my->x, my->y, &my->img, SRCPAINT);
	}
}

//��ʼ����Ϸ����
void static_game() {
	//ͼƬ���
	static IMAGE bkimg;         //����ͼ
	static my_img combo;        //combo����ͼ
	static my_img maxcombo;     //maxcombo����ͼ
	static IMAGE combo_mask;    //combo����ͼ

	static char UseForInitialOnlyOnce = 1;  //ֻ��ʼ��һ��
	if (UseForInitialOnlyOnce == 1) {
		UseForInitialOnlyOnce = 0;
		loadimage(&bkimg, _T("ͼƬ�ز�\\��������.jpg"));
		loadimage(&combo.img, _T("ͼƬ�ز�\\combo.jpg"));
		loadimage(&maxcombo.img, _T("ͼƬ�ز�\\combo.jpg"));
		combo.y = 370;   combo.x = 80 + 13;         //combo����ͼ����
		maxcombo.y = 370;   maxcombo.x = 420 + 13;  //maxcombo����ͼ����
	}
	putimage(0, 0, &bkimg);

	myoutimg(&combo, &combo_mask);                //���ƻ����������ͼƬ
	myoutimg(&maxcombo, &combo_mask);

	setcolor(WHITE);
	setbkmode(TRANSPARENT);		        // �������ֱ���Ϊ͸��ɫ
	settextstyle(22, 0, _T("΢���ź�"));
	outtextxy(195 + 16, 0, _T("������D��      �ҹ����J��"));
	settextstyle(25, 0, _T("΢���ź�"));
	outtextxy(10, 10, _T("�˳���ESC��"));
}

//������Ϸ�ڵĶ�̬��Ϣ
void Update() {
	//ͼƬ���:
	static my_img gd;        //goodͼƬ�ṹ
	static IMAGE gd1;        //good����ͼ
	static char UseForInitialOnlyOnce = 1;  //ֻ��ʼ��һ��
	if (UseForInitialOnlyOnce == 1) {
		loadimage(&gd.img, _T("ͼƬ�ز�\\good.jpg"));
		loadimage(&gd1, _T("ͼƬ�ز�\\good����ͼ.jpg"));
		UseForInitialOnlyOnce = 0;
		gd.x = 89; gd.y = 300;
	}
	if (good_flag) {
		myoutimg(&gd, &gd1);
		good_flag--;
	}


	//�������:

	//�÷����
	settextstyle(23, 0, _T("΢���ź�"));     //��������
	settextcolor(YELLOW);					 // ����������ɫΪ��ɫ
	setbkmode(TRANSPARENT);					 // �������ֱ���Ϊ͸��ɫ	
	outtextxy(500, 100, _T("Score:"));
	TCHAR s[5];								 //�������飬��������ַ���
	_stprintf(s, _T("%d"), score);			 //������scoreת�����ַ���
	outtextxy(560, 100, s);	                 //���ַ��������������

											 //��ǰcombo���
	settextstyle(21, 0, _T("΢���ź�"));     //��������
	settextcolor(RED);						 // ����������ɫΪ��ɫ
	setbkmode(TRANSPARENT);					 // �������ֱ���Ϊ͸��ɫ
	outtextxy(115 + 4, 395, _T("Combo"));
	TCHAR s1[5];							 //�������飬��������ַ���
	_stprintf(s1, _T("%d"), comboscore);     //������comboscoreת�����ַ���
	outtextxy(130 + 10, 420, s1);            //���ַ��������������

											 //����������										 
	settextcolor(RED);						 // ����������ɫΪ��ɫ
	setbkmode(TRANSPARENT);					 // �������ֱ���Ϊ͸��ɫ
	outtextxy(438, 395, _T("MAX combo"));
	TCHAR s2[5];							 //�������飬��������ַ���
	_stprintf(s2, _T("%d"), maxcomboscore);  //������maxcomboscoreת�����ַ���
	outtextxy(130 + 340 + 15, 420, s2);        //���ַ��������������
}

//˫���
void track(int isR, int isL) {
	static my_img diamond_left[5];  //��������ˮ������������
	static my_img diamond_right[5]; //�����ҹ��ˮ������������
	static IMAGE diamond_mask;      //ˮ��������ͼ
	//��ʼ��								
	static char UseForInitialOnlyOnce = 1; //ֻ��ʼ��һ��
	if (UseForInitialOnlyOnce == 1)
		for (int i = 0; i < 5; i++) {
			loadimage(&diamond_left[i].img, _T("ͼƬ�ز�\\ˮ����.jpg"));  //70 x 18
			diamond_left[i].flag = 0;
			diamond_left[i].x = 184 + 19 + 14;
			diamond_left[i].isgetd = 0;
			loadimage(&diamond_right[i].img, _T("ͼƬ�ز�\\ˮ����.jpg"));  //70 x 18
			diamond_right[i].flag = 0;
			diamond_right[i].x = 184 + 145 + 14;
			diamond_right[i].isgetd = 0;
			loadimage(&diamond_mask, _T("ͼƬ�ز�\\ˮ��������ͼ.jpg"));  //70 x 18
			UseForInitialOnlyOnce = 0;
		}
	static int p = 0;  //p����������ɵ��ٶ�


	if (isL == 1) {
		for (int i = 0; i < 5; i++) {
			if (diamond_left[i].flag == 0) {
				diamond_left[i].flag = 1;                            //������ʾ
				diamond_left[i].y = 76;								 //�����������ʼ��
				break;												 //ֻ����һ��
			}

		}
	}
	if (isR == 1) {
		for (int i = 0; i < 5; i++) {
			if (diamond_right[i].flag == 0) {
				p = 0;
				diamond_right[i].flag = 1;							 //������ʾ
				diamond_right[i].y = 76; 							 //�����������ʼ��
				break;												 //ֻ����һ��
			}
		}
	}

	//ˮ�������䣬�ֱ������ҹ������ȫ���ƣ���Ϊ����
	for (int i = 0; i < 5; i++) {
		if (diamond_left[i].flag == 1) {            //����ʾ�Ĳ�����
													//�÷�����
			if (diamond_left[i].isgetd == 0 && diamond_left[i].y >= 420 & diamond_left[i].y < 427) {
				if (GetAsyncKeyState(0x44) & 0x8000) {       //�� d ��
					score += 10;                               //�ӷ�
					comboscore++;                            //��ǰcombo+1
					diamond_left[i].isgetd = 1;              //�÷ֺ����ˮ���������ٱ��÷�
					good_flag = 30;							 //������ʾ GOOD
				}
			}
			//δ���ף����ˮ����
			if (diamond_left[i].y < 427) {
				myoutimg(&diamond_left[i], &diamond_mask);
			}
			//���ף�������Ϣ
			else {
				if (diamond_left[i].isgetd == 0) {
					comboscore = 0;            //����ˮ����δ���÷֣���ǰcombo����
				}
				diamond_left[i].flag = 0;      //������ʾ
				diamond_left[i].isgetd = 0;    //���÷�����
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (diamond_right[i].flag == 1) {            //����ʾ�Ĳ�����
													 //�÷�����
			if (diamond_right[i].isgetd == 0 && diamond_right[i].y >= 420 & diamond_right[i].y < 427) {
				if (GetAsyncKeyState(0x4A) & 0x8000) {       //�� j ��
					score += 10;                       //�ӷ�
					comboscore++;
					diamond_right[i].isgetd = 1;        //�÷ֺ����ˮ���������ٱ��÷�
					good_flag = 30;
				}
			}
			//δ���ף����ˮ����
			if (diamond_right[i].y < 427) {
				myoutimg(&diamond_right[i], &diamond_mask);
			}
			else {
				if (diamond_right[i].isgetd == 0) {
					comboscore = 0;
				}
				diamond_right[i].flag = 0;
				diamond_right[i].isgetd = 0;
			}
		}
	} //�����ҹ������ȫ����

	if (comboscore > maxcomboscore) {
		maxcomboscore = comboscore;    //�����������
	}

	//��ʱ
	Sleep(10);
	FlushBatchDraw();                  //������ͼ

									   //�ָ�ԭ״����ˮ�������䣬�ֱ������ҹ������ȫ����
	for (int i = 0; i < 5; i++) {
		if (diamond_left[i].flag == 1) {
			if (diamond_left[i].y < 427) {
				myoutimg(&diamond_left[i], NULL);  //�ָ�ԭ״
				diamond_left[i].y += 4;               //ˮ��������
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (diamond_right[i].flag == 1) {
			if (diamond_right[i].y < 427) {
				myoutimg(&diamond_right[i], NULL);
				diamond_right[i].y += 4;
			}
		}
	}
}

//�������ܵ�ʵ��
int UpdateWithInput(void) {
	int flag = -1;
	if (_kbhit()) {
		char c = _getch();
		if (c == 27) {                             //27->ESC��
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);//�ر�����
			return 1;
		}
	}
	return flag;
}