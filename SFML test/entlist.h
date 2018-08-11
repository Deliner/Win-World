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





//Структура реализующая двунаправленный список из сущностей
struct ent_data
{
public:
	Entity * ent_ptr; //указатель на сущность
	ent_data* next; //указатель на след структуру
	ent_data* prev; //указатель на пред структуру
};



//Класс для работы со списком сущностей
class ent_list
{
private:
	ent_data * first; //указывает на текущий первый элемент списка

public:
	//Конструктор
	ent_list();

	//Функции
	void add(Entity* ptr); //добавляет элемент в начало списка
	void rm(Entity* ptr); //удаляет структуру и бота

	ent_data* find(Entity* ptr); //находит структуру по указателю на сущность
	ent_data* r_first(); //возвращает первый элемент списка

	Entity* xy_find(int x, int y); //находит указатель на сущность по координатам
};