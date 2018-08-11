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





// ласс реализующий бота
class Bot : public sf::Drawable
{
private:

public:
	// онструкторы
	Bot(int posx, int posy, int size); //выставл€ет позиции и размер дл€ отрисовки
	Bot(const Bot&) = delete;
	Bot& operator=(const Bot&) = delete;

	//‘ункции
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//ƒанные
	int pos_to_mov_x; //позици€ к которой стремитс€ бот по x
	int pos_to_mov_y; //позици€ к которой стремитс€ бот по y
	int steps; //сколько уже идет к позиции
	bool follower; //€вл€етс€ ли последователем
	
	int x; //позици€ по x
	int y; //позици€ по y
	int energy; //енерги€

	sf::RectangleShape shape;
};