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





//����� ����������� ����
class Bot : public sf::Drawable
{
private:

public:
	//������������
	Bot(int posx, int posy, int size); //���������� ������� � ������ ��� ���������
	Bot(const Bot&) = delete;
	Bot& operator=(const Bot&) = delete;

	//�������
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//������
	int pos_to_mov_x; //������� � ������� ��������� ��� �� x
	int pos_to_mov_y; //������� � ������� ��������� ��� �� y
	int steps; //������� ��� ���� � �������
	bool follower; //�������� �� ��������������
	
	int x; //������� �� x
	int y; //������� �� y
	int energy; //�������

	sf::RectangleShape shape;
};