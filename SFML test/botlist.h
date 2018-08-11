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





//Структура реализующая двунаправленный список ботов
struct bot_data
{
	Bot* bot_ptr; //указатель на бота
	bot_data* next; //указатель на следующую структуру
	bot_data* prev; //указатель на предыдущую
};



//Класс для работы со списком ботов
class bot_list
{
private:
	bot_data * first; //указатель на первый элемент

public:
	//Конструктор
	bot_list();

	//Функции
	void add(Bot* ptr); //добавляет бота в начало списка
	void rm(Bot* ptr); //удаляет структуру и бота

	bot_data* find(Bot* ptr); //находит структуру с нужным ботом
	bot_data* r_first(); //возвращает первый элемент списка

};