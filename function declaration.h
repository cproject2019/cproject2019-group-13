#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>

//图片信息结构体
typedef struct my_img {
	IMAGE img;        //图片变量
	IMAGE before;     //(用于恢复原图)覆盖前的图片变量
	int flag;         //是否显示在界面上，1代表显示，0代表不显示
	int x;            //图片左上角横坐标
	int y;            //图片左上角纵坐标 
	int isgetd;       //(用于水晶条)是否被得分，0为否，1为是
	my_img() {}
};

//函数声明
void begin(void);                 //开场界面
int login(void);                  //登录函数
int select(void);                 //选择函数
void introduction(void);          //简介函数
void myoutimg(my_img*, IMAGE*);   //图片输出函数
void static_game(void);           //游戏静态背景
void Update(void);                //更新游戏内的动态信息
void track(void);                 //轨道实现
void play_bgm(void);              //播放音乐
int UpdateWithInput(void);		  //其他功能的实现
int selectClassical(void);
void listen(void);
void Score(void);
int write(FILE *aimFile);                                        //录入音乐
void run(FILE *aimFile);                                          //播放原创曲目
int GET_VOICE_HEIGHT(char VOICE_FLAG, char VOICE_LEVEL, int dimension); //获取实际频率