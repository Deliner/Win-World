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





//Главный класс мира
class World
{
public:
	//Конструкторы	
	World(); //создает мир со стандартными параметрами
	World(int sizex, int sizey, int scale, int botsize, int entspawn, int energy_spawn, int energy_gain, int stepcost, int botx, int boty); //создает мир с параметрами юзера

																																	
	void run(); //начинает игровой цикл

private:

	//Функции
	void processEvents(); //проверяет на события 

	void render(); //главная функция отвечающая за отображение
	void all_bot_draw(); //отображает всех ботов
	void all_ent_draw(); //отображает все сущности

	void update(); //обновляет состояние мира
	void botStep(bot_data* current); //для каждого бота вызывает функцию перемещения
	void botStat(Bot* ptr); //функция перемещения для бота	
	void entStep(); //для каждой сущности вызывает функцию смещения	
	void entStat(Entity* ptr); //функция смещения для сущности
	void entSpawn(); //за каждый цикл генерирует новую сущность

	int pos_check(int x, int y); //проверяет позицию
	bool ent_check(int x); //проверяет карту на сущность
	bool bot_check(int x); //проверяет карту на бота
	bool free_check(int x); //проверяет карту на свободное место

	void bot_mov(int x, int y, Bot* ptr); //плейсит бота
	void ent_rm(int x, int y); //удаляет сущность
	void bot_add(int x, int y); //добавляет бота

	void arr_shuffle(int arr[], int size, int shuffle); //переставляет элементы массива
	int screen_size(int x); //фозвращает нужный размер экрана
	void inf_print(); //выводит информацию за цикл

					  //Константы	
	static const int BOT = 1; //Как отображать бота на карте
	static const int ENT = 2; //Как отображать сущность на карте 
	static const int FREE = 0; //Как отображать свободу на карте

	static const int MAX_WORLD_SIZE_X = 316; //максимальный рамер экрана по горизонтали
	static const int MAX_WORLD_SIZE_Y = 176; //максимальный размер экрана по вертикали

											 //Переменные(константы), для задания пользователем
	int ENERGY_GAINED; //сколько получать энергии за сущность
	int BOT_STEP_COST;	//сколько энергии тратится при шаге
	int SCREEN_SCALE; //увеличиваем размер экрана
	int BOT_SIZE; //размер бота
	int ENT_NUM_SPAWN; //сколько спаунится сущностей за цикл
	int ENERGY_FOR_SPAWN; //сколько нужно энергии для спауна
	int BOT_POS_X; //на какой позиции спаунить бота по x
	int BOT_POS_Y; //на какой позиции спаунить бота по y
	int WORLD_SIZE_X; //размер мира по x
	int WORLD_SIZE_Y; //размер мира по y

					  //Переменные
	int turn; //считает циклы
	int bot_num; //считает кол-во ботов
	int ent_num; //считает кол-во сущностей

	int step_arr[4] = { 1,2,3,4 }; //массив для выбора направления	
	int ent_spawn_arr[MAX_WORLD_SIZE_X]; //массив для выбора точки спауна сущности
	int world_arr[MAX_WORLD_SIZE_Y][MAX_WORLD_SIZE_X]; //массив карты мира

	bot_list bot_arr; //список для ботов
	ent_list ent_arr; //список для сущностей

	sf::Clock main_clock; //главные часы
	sf::RenderWindow world_window; //главное окно
};
