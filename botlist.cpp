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





//ÄËß ÊËÀÑÑÀ ÑÏÈÑÊÀ ÁÎÒÎÂ
bot_list::bot_list()
{
	first = NULL;
}

bot_data* bot_list::r_first()
{
	return first;
}

void bot_list::add(Bot* ptr)
{
	bot_data* newstruct = new bot_data;
	newstruct->bot_ptr = ptr;

	if (first == NULL)
	{
		newstruct->next = NULL;
		first = newstruct;
		first->prev = NULL;

	}
	else
	{
		newstruct->next = first;
		first = newstruct;
		newstruct->prev = NULL;

		newstruct->next->prev = newstruct;
	}
}

bot_data* bot_list::find(Bot* ptr)
{
	bot_data* current = first;

	while ((current->bot_ptr != ptr) && (current->next != NULL))
	{
		current = current->next;
	}

	return current;
}

void bot_list::rm(Bot* ptr) //ÏÐÎÂÅÐÈÒÜ ÄÅÑÒÐÓÊÒÎÐ È ÍÅ ÐÀÁÎÒÀÅÒ Ñ ÓÄÀËÅÍÈÅ ÏÎÑËÅÄÍÅÃÎ ÁÎÒÀ
{
	bot_data* current = find(ptr);


	if ((current == first) && (current->next == NULL))
	{
		delete current->bot_ptr;
		delete current;
		first = NULL;
	}
	else if ((current == first) && (current->next != NULL))
	{
		current->next->prev = NULL;
		first = current->next;

		delete current->bot_ptr;
		delete current;
	}
	else if ((current != first) && (current->next == NULL))
	{
		current->prev->next = NULL;

		delete current->bot_ptr;
		delete current;
	}
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;

		delete current->bot_ptr;
		delete current;
	}
}