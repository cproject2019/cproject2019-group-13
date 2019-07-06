#pragma once
#include <stdio.h>                      //�ļ�
#include <graphics.h>                   //ͼ�ο�
#include <conio.h>                      //ͼ�ο�
#include <easyx.h>                      //ͼ�ο�
#include <windows.h>
#include <string.h>

void create(void)
{
	static IMAGE bkimg;
	static char k = 1;
	int c1=0;
	if (k == 1) {
		loadimage(&bkimg, _T("ͼƬ�ز�\\ԭ����Ŀ.jpg"));
		k = 0;
	}
	cleardevice();
	putimage(0, 0, &bkimg);
	setbkmode(TRANSPARENT);		        // �������ֱ���Ϊ͸��ɫ

	LPCTSTR x = _T("������ԭ�����ļ����ƣ���[.cmusic]��β��");
	outtextxy(320 - textwidth(x) / 2, 180, x);
	settextstyle(25, 0, _T("΢���ź�"));
	LPCTSTR y = _T("��Esc���������˵�");
	outtextxy(10, 10, y);
	char filePath[100];
	int index = 0;
	settextstyle(30, 0, _T("����"));
	while (1)
	{
		TCHAR c = getch();
		if (c == 13)
			break;
		else if (c == 27) {
			c1 = 1;
			break;
		}
		else if (c == 8) {
			//�ж��˸�����±�-1
			index--;
			loadimage(&bkimg, _T("ͼƬ�ز�\\ԭ����Ŀ.jpg"));
			putimage(0, 0, &bkimg);
			setbkmode(TRANSPARENT);		        // �������ֱ���Ϊ͸��ɫ
			settextstyle(30, 0, _T("΢���ź�"));
			LPCTSTR x = _T("������ԭ�����ļ����ƣ���[.cmusic]��β��");
			outtextxy(320 - textwidth(x) / 2, 180, x);
			//��ԭ��������Ϣ
			for (int inner_i = 0; inner_i < index; inner_i++) {
				settextstyle(30, 0, _T("����"));
				outtextxy(250 + 15 * inner_i, 250, filePath[inner_i]);
			}
			continue;
		}
		outtextxy(250 + 15 * index, 250, c);
		filePath[index] = c;
		index++;
	}
	if (c1 == 1)
		return;
	filePath[index] = '\0';
	settextstyle(30, 0, _T("΢���ź�"));

	//���ļ�
	FILE *aimFile;
	aimFile = fopen(filePath, "w");
	c1=write(aimFile);
	if (c1 == 1)
		return;
	fclose(aimFile);
	aimFile = fopen(filePath, "r");

	run(aimFile);
	fclose(aimFile);
}

#define DEFAULT_VOICE_LENGTH 750
//Ƶ�ʶ��ձ� 
long VOICE_LIST[] = { 261, 277, 293, 311, 329, 349, 369, 392, 415, 440, 466, 493 };

int VOICE_LENGTH_INPUT = 0;

//������Ϣ�ṹ��
typedef struct {

	int voiceDimension;     //�˶� �磺�߰˶� �� �� 0123 4 5678��ʾ (4 ��ʾ�������ڣ� ΪĬ�ϣ�
	int voiceLength;        //����
	int voiceIsHasLen;      //����������
	char voiceHeigh[2];     //���� ��:1\2\3\4\5\6\7

} VoiceStruct;

int write(FILE *aimFile) {

	static IMAGE bkimg;
	static char k = 1;
	int c1 = 0;
	if (k == 1) {
		loadimage(&bkimg, _T("ͼƬ�ز�\\��������.jpg"));
		k = 0;
	}
	cleardevice();
	putimage(0, 0, &bkimg);
	settextstyle(25, 0, _T("΢���ź�"));
	LPCTSTR y = _T("��Esc���������˵�");
	outtextxy(10, 10, y);
	settextstyle(30, 0, _T("΢���ź�"));
	setbkmode(TRANSPARENT);		        // �������ֱ���Ϊ͸��ɫ

	LPCTSTR x = _T("�������ٶ�(30-200,�𽥼ӿ�):");
	outtextxy(320 - textwidth(x) / 2, 200, x);
	int s[5] = { '0', '0', '0', '0', '0' };
	int index = 0;
	while (1)
	{
		int c = getch();
		if (c == 13)
			break;
		if (c == 27) {
			c1 = 1;
			return c1;
		}
		outtextxy(300 + 15 * index, 250, c);
		s[index] = c;
		index++;
	}
	int speed;
	if (index == 2)
		speed = (s[0] - '0') * 10 + (s[1] - '0');
	else
		speed = (s[0] - '0') * 100 + (s[1] - '0') * 10 + (s[2] - '0');

	fprintf(aimFile, "+%d\n", speed);

	//ѭ������һ������
	while (1) 
	{
		cleardevice();
		putimage(0, 0, &bkimg);

		char VOICE_PRE = '-';
		char VOICE_HEIGHT = '0';
		int VOICE_DIM = 4;
		int VOICE_LEGNTH = 1;
		int VOICE_IS_ADD_LENGTH = 0;

		settextstyle(25, 0, _T("΢���ź�"));
		LPCTSTR y = _T("��Esc���������˵�");
		outtextxy(10, 10, y);

		LPCTSTR x0 = _T("��=�������ļ�");
		outtextxy(320 - textwidth(x0) / 2, 50, x0);

		LPCTSTR x1 = _T("����������ǰ׺��#��������b��������-����������");
		outtextxy(320 - textwidth(x1) / 2, 100, x1);
		VOICE_PRE = getch();
		outtextxy(315,125,VOICE_PRE);
		if (VOICE_PRE == 27) 
			return 1;
		if (VOICE_PRE == '=')
			return 0;

		LPCTSTR x2 = _T("���������ף�01234567��");
		outtextxy(320 - textwidth(x2) / 2, 160, x2);
		VOICE_HEIGHT = getch();
		outtextxy(315,185,VOICE_HEIGHT);

		LPCTSTR x3 = _T("������˶ȣ�0123 4 5678)");
		outtextxy(320 - textwidth(x3) / 2, 220, x3);
		VOICE_DIM = getch();
		outtextxy(315, 245, VOICE_DIM);

		LPCTSTR x4 = _T("����������������֮������-2   2�����ȣ�2   ����Ϊ0)");
		outtextxy(320 - textwidth(x4) / 2, 280, x4);
		VOICE_LEGNTH = getch();
		outtextxy(315, 305, VOICE_LEGNTH);

		LPCTSTR x5 = _T("0��û������  1��������");
		outtextxy(320 - textwidth(x5) / 2, 340, x5);
		VOICE_IS_ADD_LENGTH = getch();
		outtextxy(315, 365, VOICE_IS_ADD_LENGTH);

		fprintf(aimFile, "%c,%c,%d,%d,%d\n", VOICE_PRE, VOICE_HEIGHT, VOICE_DIM, VOICE_LEGNTH, VOICE_IS_ADD_LENGTH);
	}
}

void DO_BEEP(VoiceStruct voiceStruct);     //����
int CHECK_VOICE(VoiceStruct voiceStruct);  //��������Ƿ���ȷ
                                           //�����ȷ����ʵ������Ƶ�ʣ����򷵻�-1
int GET_VOICE_HEIGHT(char VOICE_FLAG, char VOICE_LEVEL, int dimension);  //���ʵ��Ƶ��
int getLength(int length, int defaultLength, int isHasLen);              //��ȡ��������ʱ�� 


void run(FILE *aimFile) {
	static IMAGE bkimg;
	static char k = 1;
	if (k == 1) {
		initgraph(640, 480);
		loadimage(&bkimg, _T("ͼƬ�ز�\\��������.jpg"));
		k = 0;
	}
	putimage(0, 0, &bkimg);

	VoiceStruct voiceStruct;                                            //����һ���ṹ�� 
	int voiceSpeed = 0;                                                 //���塰�ٶȡ���ÿ���ļ�Ҳ����ÿ�׸迪ͷ����һ���ٶȣ����潫�ᱻ����ɺ��룩 
	if (fscanf(aimFile, "+%d\n", &voiceSpeed) == -1) {                  //�����ļ���ġ��ٶȡ�
		return;
	}
	else {
		if (voiceSpeed >= 30 && voiceSpeed <= 200) {
			VOICE_LENGTH_INPUT = 1000 * (60.0 / voiceSpeed);            //���ٶ���30-200������������ɺ��� 
		}
		else {
			VOICE_LENGTH_INPUT = 0;                                     //�粻�ڣ�Խ�磬��ʼ��0 
		}
	}


	while ((fscanf(aimFile, "%c,%c,%d,%d,%d\n",                         //�����ļ���һ����������Ϣ���浽�Լ����Ľṹ���У���ѭ�������������� 
		&voiceStruct.voiceHeigh[0],
		&voiceStruct.voiceHeigh[1],
		&voiceStruct.voiceDimension,
		&voiceStruct.voiceLength,
		&voiceStruct.voiceIsHasLen)) != -1) {

		DO_BEEP(voiceStruct);                                          //���� 
	}
	getch();
	return;
}


//����һ������
void DO_BEEP(VoiceStruct voiceStruct) {
	int voiceNum = CHECK_VOICE(voiceStruct);                      //��������Ƿ���ȷ�������ȷ����ʵ������Ƶ�ʣ����򷵻�-1
	if (voiceNum != -1) {

		int voiceLength = getLength(voiceStruct.voiceLength,
			VOICE_LENGTH_INPUT == 0 ? DEFAULT_VOICE_LENGTH : VOICE_LENGTH_INPUT,
			voiceStruct.voiceIsHasLen);   //���������Ĳ���ʱ�� 

		Beep(voiceNum, voiceLength);                              //��һ��������Ƶ�ʣ�ʱ����Beep�������������� 
	}
}


//��������Ƿ���ȷ
//�����ȷ����ʵ������Ƶ�ʣ����򷵻�-1
int CHECK_VOICE(VoiceStruct voiceStruct) {

	//���ʵ��Ƶ�� 
	int voice = GET_VOICE_HEIGHT(voiceStruct.voiceHeigh[0], voiceStruct.voiceHeigh[1], voiceStruct.voiceDimension);
	//����״̬����ȷ
	if (voice == -1) {
		return -1;
	}

	// ������0���֣� ���Ϊ��������Ϊ������ ���磻-4 = �ķ�֮����
	if (voiceStruct.voiceLength == 0) {
		return -1;
	}

	// ���ܳ���8 ����С��-16
	if (voiceStruct.voiceLength < -16 || voiceStruct.voiceLength > 8) {
		return -1;
	}

	return voice;
}


//���ʵ��Ƶ�� 
int GET_VOICE_HEIGHT(char VOICE_FLAG, char VOICE_LEVEL, int dimension) {
	int voiceLevel;
	int voiceFlag;

	// 0 ���ģ� 1234567 ��������
	if (VOICE_LEVEL >= '0' && VOICE_LEVEL <= '7') {                //���� 
		voiceLevel = VOICE_LEVEL - '0';
	}
	else {                                                       // �쳣
		return -1;
	}

	if (voiceLevel == 0) {                                       //����ǿ��ģ�ֱ�ӷ��أ������� 
		return 0;
	}

	// # ������� b �����
	//����� #��voiceflag=1���� b��voiceflag=-1��������Ϊ0 
	voiceFlag = VOICE_FLAG == '#' ? 1 : (VOICE_FLAG == 'b' ? -1 : 0);

	int voiceListIndex = 0;

	//�����Ϸ���Ƶ�ʱ��Ӧ 
	switch (voiceLevel) {
	case 1: {
		voiceListIndex = 0;
		break;
	}
	case 2: {
		voiceListIndex = 2;                                 //��಻ͬ����Ϊ֮���а������ 
		break;
	}
	case 3: {
		voiceListIndex = 4;
		break;
	}
	case 4: {
		voiceListIndex = 5;
		break;
	}
	case 5: {
		voiceListIndex = 7;
		break;
	}
	case 6: {
		voiceListIndex = 9;
		break;
	}
	case 7: {
		voiceListIndex = 11;
		break;
	}
	default:                                        //���ȫ���ǣ�˵������ 
		return -1;
	}

	//���߷�Χ�ж�
	if (dimension < 0 || dimension > 8) {              //���߷�ΧԽ�� 
		return -1;
	}


	//�����������
	voiceListIndex += voiceFlag;                       //���������� 
	if (voiceListIndex == -1) {
		voiceListIndex = 11;
	}
	else if (voiceListIndex == 12) {
		voiceListIndex = 0;
	}

	// ���߶�Ӧʵ��Ƶ��
	long voiceNumber = VOICE_LIST[voiceListIndex];

	//�͸߰˶ȴ��� ÿ����һ�ΰ˶ȣ�Ƶ�ʳ˻����2
	int demp = dimension - 4;                           //4��Ĭ�ϰ˶ȣ�Ҳ��������Ƶ�ʱ������ 
	if (demp > 0) {                                     //����õ��İ˶�demp����4�˶ȣ�Ƶ��ÿ�γ�2 
		while (demp != 0) {
			voiceNumber *= 2;
			demp--;
		}
	}
	if (demp < 0) {                                     //����õ��İ˶�demp����4�˶ȣ�Ƶ��ÿ�γ���2
		while (demp != 0) {
			voiceNumber /= 2;
			demp++;
		}
	}

	return voiceNumber;                                 //�������������Ƶ�� 
}


//��ȡ��������ʱ�� 
int getLength(int length, int defaultLength, int isHasLen) {

	if (length < 0) {                                   //����length=-2�������ַ�ʽ�ø�������ʱ���Ƕ���֮һ�� 
		length *= -1;
		return defaultLength / length;
	}

	if (isHasLen) {                                     //�������ʱ ��ʱ���Ӱ��� 
		return defaultLength * length + defaultLength / 2;
	}
	return defaultLength * length;                      //����length=2�������ַ�ʽ�ø�������ʱ��������

}