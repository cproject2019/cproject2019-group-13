#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>

//ͼƬ��Ϣ�ṹ��
typedef struct my_img {
	IMAGE img;        //ͼƬ����
	IMAGE before;     //(���ڻָ�ԭͼ)����ǰ��ͼƬ����
	int flag;         //�Ƿ���ʾ�ڽ����ϣ�1������ʾ��0������ʾ
	int x;            //ͼƬ���ϽǺ�����
	int y;            //ͼƬ���Ͻ������� 
	int isgetd;       //(����ˮ����)�Ƿ񱻵÷֣�0Ϊ��1Ϊ��
	my_img() {}
};

//��������
void begin(void);                 //��������
int login(void);                  //��¼����
int select(void);                 //ѡ����
void introduction(void);          //��麯��
void myoutimg(my_img*, IMAGE*);   //ͼƬ�������
void static_game(void);           //��Ϸ��̬����
void Update(void);                //������Ϸ�ڵĶ�̬��Ϣ
void track(void);                 //���ʵ��
void play_bgm(void);              //��������
int UpdateWithInput(void);		  //�������ܵ�ʵ��
int selectClassical(void);
void listen(void);
void Score(void);
int write(FILE *aimFile);                                        //¼������
void run(FILE *aimFile);                                          //����ԭ����Ŀ
int GET_VOICE_HEIGHT(char VOICE_FLAG, char VOICE_LEVEL, int dimension); //��ȡʵ��Ƶ��