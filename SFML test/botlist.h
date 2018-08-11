#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef WORLD_H
#define WORLD_H
#include "world.h"
#endif

#ifndef SFML
#define SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#endif 

#ifndef BOTLIST_H
#define BOTLIST_H
#include "botlist.h"
#endif

#ifndef ENTLIST_H
#define ENTLIST_H
#include "entlist.h"
#endif

#ifndef BOT_H
#define BOT_H
#include "bot.h"
#endif 

#ifndef ENTITY_H
#define ENTITY_H
#include "entity.h"
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif





//��������� ����������� ��������������� ������ �����
struct bot_data
{
	Bot* bot_ptr; //��������� �� ����
	bot_data* next; //��������� �� ��������� ���������
	bot_data* prev; //��������� �� ����������
};



//����� ��� ������ �� ������� �����
class bot_list
{
private:
	bot_data * first; //��������� �� ������ �������

public:
	//�����������
	bot_list();

	//�������
	void add(Bot* ptr); //��������� ���� � ������ ������
	void rm(Bot* ptr); //������� ��������� � ����

	bot_data* find(Bot* ptr); //������� ��������� � ������ �����
	bot_data* r_first(); //���������� ������ ������� ������

};