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





//ÄËß ÊËÀÑÑÀ ÑÏÈÑÊÀ ÑÓÙÍÎÑÒÈ
Entity* ent_list::xy_find(int x, int y)
{
	ent_data* current = r_first();


	do
	{
		if ((current->ent_ptr->x == x) and (current->ent_ptr->y == y))
		{
			return current->ent_ptr;
		}
		else
		{
			current = current->next;
		}
	} while (current->next != NULL);

	return NULL;
}

ent_list::ent_list()
{
	first = NULL;
}

ent_data* ent_list::r_first()
{
	return first;
}

void ent_list::add(Entity* ptr)
{
	ent_data* newstruct = new ent_data;
	newstruct->ent_ptr = ptr;


	if (first == NULL)
	{
		newstruct->next = first;
		first = newstruct;
		newstruct->prev = NULL;
	}
	else
	{
		newstruct->next = first;
		first = newstruct;
		newstruct->prev = NULL;

		newstruct->next->prev = newstruct;
	}
}

ent_data* ent_list::find(Entity* ptr)
{
	ent_data* current = first;

	while ((current->ent_ptr != ptr) && (current->next != NULL))
	{
		current = current->next;
	}

	return current;
}

void ent_list::rm(Entity* ptr) //Ïåðåäåëàòü âî âòîðîé ðàç
{
	ent_data* current = find(ptr);


	if ((current == first) && (current->next == NULL))
	{
		delete current->ent_ptr;
		delete current;
		first = NULL;
	}
	else if ((current == first) && (current->next != NULL))
	{
		current->next->prev = NULL;
		first = current->next;

		delete current->ent_ptr;
		delete current;
	}
	else if ((current != first) && (current->next == NULL))
	{
		current->prev->next = NULL;

		delete current->ent_ptr;
		delete current;
	}
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;

		delete current->ent_ptr;
		delete current;
	}
}