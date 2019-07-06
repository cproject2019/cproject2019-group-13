#pragma once
#include <stdio.h>                      //文件
#include <graphics.h>                   //图形库
#include <conio.h>                      //图形库
#include <easyx.h>                      //图形库
#include <windows.h>
#include <string.h>

void create(void)
{
	static IMAGE bkimg;
	static char k = 1;
	int c1=0;
	if (k == 1) {
		loadimage(&bkimg, _T("图片素材\\原创曲目.jpg"));
		k = 0;
	}
	cleardevice();
	putimage(0, 0, &bkimg);
	setbkmode(TRANSPARENT);		        // 设置文字背景为透明色

	LPCTSTR x = _T("请输入原创的文件名称（以[.cmusic]结尾）");
	outtextxy(320 - textwidth(x) / 2, 180, x);
	settextstyle(25, 0, _T("微软雅黑"));
	LPCTSTR y = _T("按Esc键返回主菜单");
	outtextxy(10, 10, y);
	char filePath[100];
	int index = 0;
	settextstyle(30, 0, _T("楷体"));
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
			//判定退格键，下标-1
			index--;
			loadimage(&bkimg, _T("图片素材\\原创曲目.jpg"));
			putimage(0, 0, &bkimg);
			setbkmode(TRANSPARENT);		        // 设置文字背景为透明色
			settextstyle(30, 0, _T("微软雅黑"));
			LPCTSTR x = _T("请输入原创的文件名称（以[.cmusic]结尾）");
			outtextxy(320 - textwidth(x) / 2, 180, x);
			//还原已输入信息
			for (int inner_i = 0; inner_i < index; inner_i++) {
				settextstyle(30, 0, _T("楷体"));
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
	settextstyle(30, 0, _T("微软雅黑"));

	//打开文件
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
//频率对照表 
long VOICE_LIST[] = { 261, 277, 293, 311, 329, 349, 369, 392, 415, 440, 466, 493 };

int VOICE_LENGTH_INPUT = 0;

//音节信息结构体
typedef struct {

	int voiceDimension;     //八度 如：高八度 等 用 0123 4 5678表示 (4 表示正常音节， 为默认）
	int voiceLength;        //音长
	int voiceIsHasLen;      //有无延音符
	char voiceHeigh[2];     //音阶 如:1\2\3\4\5\6\7

} VoiceStruct;

int write(FILE *aimFile) {

	static IMAGE bkimg;
	static char k = 1;
	int c1 = 0;
	if (k == 1) {
		loadimage(&bkimg, _T("图片素材\\输入音符.jpg"));
		k = 0;
	}
	cleardevice();
	putimage(0, 0, &bkimg);
	settextstyle(25, 0, _T("微软雅黑"));
	LPCTSTR y = _T("按Esc键返回主菜单");
	outtextxy(10, 10, y);
	settextstyle(30, 0, _T("微软雅黑"));
	setbkmode(TRANSPARENT);		        // 设置文字背景为透明色

	LPCTSTR x = _T("请输入速度(30-200,逐渐加快):");
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

	//循环输入一个音符
	while (1) 
	{
		cleardevice();
		putimage(0, 0, &bkimg);

		char VOICE_PRE = '-';
		char VOICE_HEIGHT = '0';
		int VOICE_DIM = 4;
		int VOICE_LEGNTH = 1;
		int VOICE_IS_ADD_LENGTH = 0;

		settextstyle(25, 0, _T("微软雅黑"));
		LPCTSTR y = _T("按Esc键返回主菜单");
		outtextxy(10, 10, y);

		LPCTSTR x0 = _T("按=键保存文件");
		outtextxy(320 - textwidth(x0) / 2, 50, x0);

		LPCTSTR x1 = _T("请输入音阶前缀（#升半音，b降半音，-不升不降）");
		outtextxy(320 - textwidth(x1) / 2, 100, x1);
		VOICE_PRE = getch();
		outtextxy(315,125,VOICE_PRE);
		if (VOICE_PRE == 27) 
			return 1;
		if (VOICE_PRE == '=')
			return 0;

		LPCTSTR x2 = _T("请输入音阶（01234567）");
		outtextxy(320 - textwidth(x2) / 2, 160, x2);
		VOICE_HEIGHT = getch();
		outtextxy(315,185,VOICE_HEIGHT);

		LPCTSTR x3 = _T("请输入八度（0123 4 5678)");
		outtextxy(320 - textwidth(x3) / 2, 220, x3);
		VOICE_DIM = getch();
		outtextxy(315, 245, VOICE_DIM);

		LPCTSTR x4 = _T("请输入音长（二分之音符：-2   2倍长度：2   不能为0)");
		outtextxy(320 - textwidth(x4) / 2, 280, x4);
		VOICE_LEGNTH = getch();
		outtextxy(315, 305, VOICE_LEGNTH);

		LPCTSTR x5 = _T("0：没有延音  1：有延音");
		outtextxy(320 - textwidth(x5) / 2, 340, x5);
		VOICE_IS_ADD_LENGTH = getch();
		outtextxy(315, 365, VOICE_IS_ADD_LENGTH);

		fprintf(aimFile, "%c,%c,%d,%d,%d\n", VOICE_PRE, VOICE_HEIGHT, VOICE_DIM, VOICE_LEGNTH, VOICE_IS_ADD_LENGTH);
	}
}

void DO_BEEP(VoiceStruct voiceStruct);     //发声
int CHECK_VOICE(VoiceStruct voiceStruct);  //检查音节是否正确
                                           //如果正确返回实际音高频率，否则返回-1
int GET_VOICE_HEIGHT(char VOICE_FLAG, char VOICE_LEVEL, int dimension);  //获得实际频率
int getLength(int length, int defaultLength, int isHasLen);              //获取音符播放时长 


void run(FILE *aimFile) {
	static IMAGE bkimg;
	static char k = 1;
	if (k == 1) {
		initgraph(640, 480);
		loadimage(&bkimg, _T("图片素材\\音乐欣赏.jpg"));
		k = 0;
	}
	putimage(0, 0, &bkimg);

	VoiceStruct voiceStruct;                                            //定义一个结构体 
	int voiceSpeed = 0;                                                 //定义“速度”（每个文件也就是每首歌开头都有一个速度，后面将会被换算成毫秒） 
	if (fscanf(aimFile, "+%d\n", &voiceSpeed) == -1) {                  //读入文件里的“速度”
		return;
	}
	else {
		if (voiceSpeed >= 30 && voiceSpeed <= 200) {
			VOICE_LENGTH_INPUT = 1000 * (60.0 / voiceSpeed);            //如速度在30-200，正常，换算成毫秒 
		}
		else {
			VOICE_LENGTH_INPUT = 0;                                     //如不在，越界，初始成0 
		}
	}


	while ((fscanf(aimFile, "%c,%c,%d,%d,%d\n",                         //读入文件中一个音符的信息保存到自己建的结构体中，用循环读入所有音符 
		&voiceStruct.voiceHeigh[0],
		&voiceStruct.voiceHeigh[1],
		&voiceStruct.voiceDimension,
		&voiceStruct.voiceLength,
		&voiceStruct.voiceIsHasLen)) != -1) {

		DO_BEEP(voiceStruct);                                          //发声 
	}
	getch();
	return;
}


//发声一个音符
void DO_BEEP(VoiceStruct voiceStruct) {
	int voiceNum = CHECK_VOICE(voiceStruct);                      //检查音节是否正确，如果正确返回实际音高频率，否则返回-1
	if (voiceNum != -1) {

		int voiceLength = getLength(voiceStruct.voiceLength,
			VOICE_LENGTH_INPUT == 0 ? DEFAULT_VOICE_LENGTH : VOICE_LENGTH_INPUT,
			voiceStruct.voiceIsHasLen);   //计算音符的播放时长 

		Beep(voiceNum, voiceLength);                              //把一个音符的频率，时长给Beep函数，让它发声 
	}
}


//检查音节是否正确
//如果正确返回实际音高频率，否则返回-1
int CHECK_VOICE(VoiceStruct voiceStruct) {

	//获得实际频率 
	int voice = GET_VOICE_HEIGHT(voiceStruct.voiceHeigh[0], voiceStruct.voiceHeigh[1], voiceStruct.voiceDimension);
	//音节状态不正确
	if (voice == -1) {
		return -1;
	}

	// 不允许0出现， 如果为负数，则为短音符 例如；-4 = 四分之音符
	if (voiceStruct.voiceLength == 0) {
		return -1;
	}

	// 不能超过8 不能小于-16
	if (voiceStruct.voiceLength < -16 || voiceStruct.voiceLength > 8) {
		return -1;
	}

	return voice;
}


//获得实际频率 
int GET_VOICE_HEIGHT(char VOICE_FLAG, char VOICE_LEVEL, int dimension) {
	int voiceLevel;
	int voiceFlag;

	// 0 空拍， 1234567 正常音阶
	if (VOICE_LEVEL >= '0' && VOICE_LEVEL <= '7') {                //正常 
		voiceLevel = VOICE_LEVEL - '0';
	}
	else {                                                       // 异常
		return -1;
	}

	if (voiceLevel == 0) {                                       //如果是空拍，直接返回，不发声 
		return 0;
	}

	// # 升半调， b 降半调
	//如果是 #令voiceflag=1，是 b令voiceflag=-1，都不是为0 
	voiceFlag = VOICE_FLAG == '#' ? 1 : (VOICE_FLAG == 'b' ? -1 : 0);

	int voiceListIndex = 0;

	//与最上方的频率表对应 
	switch (voiceLevel) {
	case 1: {
		voiceListIndex = 0;
		break;
	}
	case 2: {
		voiceListIndex = 2;                                 //间距不同是因为之后还有半音设计 
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
	default:                                        //如果全不是，说明出错 
		return -1;
	}

	//音高范围判断
	if (dimension < 0 || dimension > 8) {              //音高范围越界 
		return -1;
	}


	//添加升降半音
	voiceListIndex += voiceFlag;                       //考虑升降调 
	if (voiceListIndex == -1) {
		voiceListIndex = 11;
	}
	else if (voiceListIndex == 12) {
		voiceListIndex = 0;
	}

	// 音高对应实际频率
	long voiceNumber = VOICE_LIST[voiceListIndex];

	//低高八度处理， 每升降一次八度，频率乘或除以2
	int demp = dimension - 4;                           //4是默认八度，也就是上面频率表里的音 
	if (demp > 0) {                                     //若想得到的八度demp低于4八度，频率每次乘2 
		while (demp != 0) {
			voiceNumber *= 2;
			demp--;
		}
	}
	if (demp < 0) {                                     //若想得到的八度demp高于4八度，频率每次除以2
		while (demp != 0) {
			voiceNumber /= 2;
			demp++;
		}
	}

	return voiceNumber;                                 //返回最终算出的频率 
}


//获取音符播放时长 
int getLength(int length, int defaultLength, int isHasLen) {

	if (length < 0) {                                   //比如length=-2，用这种方式让该音符的时长是二分之一拍 
		length *= -1;
		return defaultLength / length;
	}

	if (isHasLen) {                                     //如果有延时 ，时长加半拍 
		return defaultLength * length + defaultLength / 2;
	}
	return defaultLength * length;                      //比如length=2，用这种方式让该音符的时长是两拍

}