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





//������� ����� ����
class World
{
public:
	//������������	
	World(); //������� ��� �� ������������ �����������
	World(int sizex, int sizey, int scale, int botsize, int entspawn, int energy_spawn, int energy_gain, int stepcost, int botx, int boty); //������� ��� � ����������� �����

																																	
	void run(); //�������� ������� ����

private:

	//�������
	void processEvents(); //��������� �� ������� 

	void render(); //������� ������� ���������� �� �����������
	void all_bot_draw(); //���������� ���� �����
	void all_ent_draw(); //���������� ��� ��������

	void update(); //��������� ��������� ����
	void botStep(bot_data* current); //��� ������� ���� �������� ������� �����������
	void botStat(Bot* ptr); //������� ����������� ��� ����	
	void entStep(); //��� ������ �������� �������� ������� ��������	
	void entStat(Entity* ptr); //������� �������� ��� ��������
	void entSpawn(); //�� ������ ���� ���������� ����� ��������

	int pos_check(int x, int y); //��������� �������
	bool ent_check(int x); //��������� ����� �� ��������
	bool bot_check(int x); //��������� ����� �� ����
	bool free_check(int x); //��������� ����� �� ��������� �����

	void bot_mov(int x, int y, Bot* ptr); //������� ����
	void ent_rm(int x, int y); //������� ��������
	void bot_add(int x, int y); //��������� ����

	void arr_shuffle(int arr[], int size, int shuffle); //������������ �������� �������
	int screen_size(int x); //���������� ������ ������ ������
	void inf_print(); //������� ���������� �� ����

					  //���������	
	static const int BOT = 1; //��� ���������� ���� �� �����
	static const int ENT = 2; //��� ���������� �������� �� ����� 
	static const int FREE = 0; //��� ���������� ������� �� �����

	static const int MAX_WORLD_SIZE_X = 316; //������������ ����� ������ �� �����������
	static const int MAX_WORLD_SIZE_Y = 176; //������������ ������ ������ �� ���������

											 //����������(���������), ��� ������� �������������
	int ENERGY_GAINED; //������� �������� ������� �� ��������
	int BOT_STEP_COST;	//������� ������� �������� ��� ����
	int SCREEN_SCALE; //����������� ������ ������
	int BOT_SIZE; //������ ����
	int ENT_NUM_SPAWN; //������� ��������� ��������� �� ����
	int ENERGY_FOR_SPAWN; //������� ����� ������� ��� ������
	int BOT_POS_X; //�� ����� ������� �������� ���� �� x
	int BOT_POS_Y; //�� ����� ������� �������� ���� �� y
	int WORLD_SIZE_X; //������ ���� �� x
	int WORLD_SIZE_Y; //������ ���� �� y

					  //����������
	int turn; //������� �����
	int bot_num; //������� ���-�� �����
	int ent_num; //������� ���-�� ���������

	int step_arr[4] = { 1,2,3,4 }; //������ ��� ������ �����������	
	int ent_spawn_arr[MAX_WORLD_SIZE_X]; //������ ��� ������ ����� ������ ��������
	int world_arr[MAX_WORLD_SIZE_Y][MAX_WORLD_SIZE_X]; //������ ����� ����

	bot_list bot_arr; //������ ��� �����
	ent_list ent_arr; //������ ��� ���������

	sf::Clock main_clock; //������� ����
	sf::RenderWindow world_window; //������� ����
};
