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





//��������� ����������� ��������������� ������ �� ���������
struct ent_data
{
public:
	Entity * ent_ptr; //��������� �� ��������
	ent_data* next; //��������� �� ���� ���������
	ent_data* prev; //��������� �� ���� ���������
};



//����� ��� ������ �� ������� ���������
class ent_list
{
private:
	ent_data * first; //��������� �� ������� ������ ������� ������

public:
	//�����������
	ent_list();

	//�������
	void add(Entity* ptr); //��������� ������� � ������ ������
	void rm(Entity* ptr); //������� ��������� � ����

	ent_data* find(Entity* ptr); //������� ��������� �� ��������� �� ��������
	ent_data* r_first(); //���������� ������ ������� ������

	Entity* xy_find(int x, int y); //������� ��������� �� �������� �� �����������
};