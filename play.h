#pragma once
#include <stdio.h>
#include <Windows.h>
#include <graphics.h>                   //ͼ�ο�
#include <conio.h>                      //ͼ�ο�
#include <easyx.h>                      //ͼ�ο�

//�������� 
void play() {
	static IMAGE bkimg;
	static char k = 1;
	if (k == 1) 
	{
		loadimage(&bkimg, _T("ͼƬ�ز�\\���ɵ���.jpg"));
		k = 0;
	}
	putimage(-150, -100, &bkimg);
	settextstyle(30, 0, _T("΢���ź�"));
	setbkmode(TRANSPARENT);		        // �������ֱ���Ϊ͸��ɫ
	LPCTSTR y1 = _T("Q��U��  ���İ˶�");
	outtextxy(400, 100, y1);
	LPCTSTR y2 = _T("A��J��  ����˶�");
	outtextxy(400, 150, y2);
	LPCTSTR y3 = _T("Z��M��  �����˶�");
	outtextxy(400, 200, y3);

	settextstyle(25, 0, _T("΢���ź�"));
	LPCTSTR y = _T("��Esc���������˵�");
	outtextxy(10, 10, y);

	settextstyle(30, 0, _T("΢���ź�"));

	char voice;
	int height, dimension;
	while (1) {
		voice = getch();
		if (voice == 'q' || voice == 'w' || voice == 'e' || voice == 'r' || voice == 't' || voice == 'y' || voice == 'u')
			dimension = 4;
		else if (voice == 'a' || voice == 's' || voice == 'd' || voice == 'f' || voice == 'g' || voice == 'h' || voice == 'j')
			dimension = 5;
		else if (voice == 'z' || voice == 'x' || voice == 'c' || voice == 'v' || voice == 'b' || voice == 'n' || voice == 'm')
			dimension = 6;
		else
			dimension = -1;

		if (voice == 'q' || voice == 'a' || voice == 'z')
			voice = '1';
		else if (voice == 'w' || voice == 's' || voice == 'x')
			voice = '2';
		else if (voice == 'e' || voice == 'd' || voice == 'c')
			voice = '3';
		else if (voice == 'r' || voice == 'f' || voice == 'v')
			voice = '4';
		else if (voice == 't' || voice == 'g' || voice == 'b')
			voice = '5';
		else if (voice == 'y' || voice == 'h' || voice == 'n')
			voice = '6';
		else if (voice == 'u' || voice == 'j' || voice == 'm')
			voice = '7';
		else if (voice ==27)
			break;
		else
			voice = '-1';

		height = GET_VOICE_HEIGHT('1', voice, dimension);     //��ȡƵ�� 
		Beep(height, 500);                                    //���� 
	}
}