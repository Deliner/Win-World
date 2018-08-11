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





//Класс реализующий бота
class Bot : public sf::Drawable
{
private:

public:
	//Конструкторы
	Bot(int posx, int posy, int size); //выставляет позиции и размер для отрисовки
	Bot(const Bot&) = delete;
	Bot& operator=(const Bot&) = delete;

	//Функции
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//Данные
	int x; //позиция по x
	int y; //позиция по y
	int energy; //енергия

	sf::RectangleShape shape;
};