#pragma once
#include <stdio.h>
#include <string.h>


typedef struct music
{
	char name[20];    //歌名
	char player[20];  //演奏者
	char album[20];   //所属专辑
	char time[15];    //出版时间
	struct music* next;
}music;

//函数声明
int destory_list(music* head);
music* _GET_MUSIC_MEMORY();
music* create_music_list(int list_length);

music* head = NULL;
music* musicList(void) {

	//7个数据  + 空头 = 8
	head = create_music_list(8);

	music* p = head->next;

	char s11[] = "Memory of Childhood";
	strcpy(p->name, s11);
	char s12[] = "Unknown";
	strcpy(p->player, s12);
	char s13[] = "A Best";
	strcpy(p->album, s13);
	char s14[] = "Unknown";
	strcpy(p->time, s14);
	p = p->next;

	char s21[] = "The Way";
	strcpy(p->name, s21);
	char s22[] = "Florian Bur";
	strcpy(p->player, s22);
	char s23[] = "Dream Once again";
	strcpy(p->album, s23);
	char s24[] = "2013";
	strcpy(p->time, s24);
	p = p->next;

	char s31[] = "Quiet Afternoon";
	strcpy(p->name, s31);
	char s32[] = "Pianoboy";
	strcpy(p->player, s32);
	char s33[] = "A best";
	strcpy(p->album, s33);
	char s34[] = "2005";
	strcpy(p->time, s34);
	p = p->next;

	char s41[] = "Colorful Moon";
	strcpy(p->name, s41);
	char s42[] = "Otokaze";
	strcpy(p->player, s42);
	char s43[] = "Colorful Moon-Sai-getsu";
	strcpy(p->album, s43);
	char s44[] = "2011";
	strcpy(p->time, s44);
	p = p->next;

	char s51[] = "Going Home";
	strcpy(p->name, s51);
	char s52[] = "Kenny G";
	strcpy(p->player, s52);
	char s53[] = "Unknown";
	strcpy(p->album, s53);
	char s54[] = "1989";
	strcpy(p->time, s54);
	p = p->next;

	char s61[] = "Kiss the Rain";
	strcpy(p->name, s61);
	char s62[] = "Yiruma";
	strcpy(p->player, s62);
	char s63[] = "Unknown";
	strcpy(p->album, s63);
	char s64[] = "2011";
	strcpy(p->time, s64);
	p = p->next;

	char s71[] = "Open Credits";
	strcpy(p->name, s71);
	char s72[] = "Hans zimmer";
	strcpy(p->player, s72);
	char s73[] = " Modern welfare 2";
	strcpy(p->album, s73);
	char s74[] = "2009";
	strcpy(p->time, s74);

	p->next = NULL;

	return head;
}


music* create_music_list(int list_length) {
	if (list_length <= 0) {
		return NULL;
	}

	music* head = _GET_MUSIC_MEMORY();
	music* m_point = head;
	int size = 0;
	while (size++ < list_length) {
		m_point->next = _GET_MUSIC_MEMORY();
		m_point = m_point->next;
	}

	return head;
}
//创建节点函数，用来创建
music* _GET_MUSIC_MEMORY() {
	music * node = (music*)malloc(sizeof(music));

	node->next = NULL;
	return node;
}


int destory_list(music* head) {
	int count = 0;
	while (head != NULL) {
		music* node = head;
		head = head->next;
		count++;
	}

	return count;
}