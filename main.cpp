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





//ќ—Ќќ¬Ќјя ‘”Ќ ÷»я
int main()
{
	//¬ыводим приветствие
	std::cout << std::endl << "Hey!!! My name is Del O'Ner, and it's my small world simulation.\n"
		<< "The RED scuare is called BOT, it can move up, down, left and right. The BLUE one is its food.\n"
		<< "BOT can destroy it and gain energy. Also u can change some params of this world.\n"
		<< "So have fun and good luck... And be carefull it non optimized =)\n";	
		


	//÷икл запуска симул€ции в приложении
	bool repeat;
	repeat = false;
	
	while(!repeat)
	{				
		char answ;
		World* main;

		do
		{
			std::cout << std::endl << "Do u whant to change standart parameters? (y/n) ";
			std::cin >> answ;
		} while (!((answ == 'y') || (answ == 'n')));

		if (answ == 'n')
		{
			main = new World;
			main->run();
		}
		else
		{
			int sizex;
			int sizey;
			int scale;
			int botsize;
			int entspawn;
			int energy_spawn;
			int energy_gain;
			int stepcost;
			int botx;
			int boty;

			//¬ывод стандартных и пользовательский ввод
			std::cout << std::endl << "Ok, here is standart parametrs: \n";
			std::cout << "WORLD_SIZE_X = 300 "; std::cout << "\nInput yours: "; std::cin >> sizex; std::cout << std::endl;
			std::cout << "WORLD_SIZE_Y = 156 "; std::cout << "\nInput yours: "; std::cin >> sizey; std::cout << std::endl;
			std::cout << "WORLD_SCALE = 2 "; std::cout << "\nInput yours: "; std::cin >> scale; std::cout << std::endl;
			std::cout << "BOT_SIZE = 2 "; std::cout << "\nInput yours: "; std::cin >> botsize; std::cout << std::endl;
			std::cout << "ENT_NUM_SPAWN = 4 "; std::cout << "\nInput yours: "; std::cin >> entspawn; std::cout << std::endl;
			std::cout << "ENERGY_FOR_SPAWN = 100 "; std::cout << "\nInput yours: "; std::cin >> energy_spawn; std::cout << std::endl;
			std::cout << "ENERGY_GAINED  = 10 "; std::cout << "\nInput yours: "; std::cin >> energy_gain; std::cout << std::endl;
			std::cout << "BOT_STEP_COST = 2 "; std::cout << "\nInput yours: "; std::cin >> stepcost; std::cout << std::endl;
			std::cout << "BOT_POS_X  = 150 "; std::cout << "\nInput yours: "; std::cin >> botx; std::cout << std::endl;
			std::cout << "BOT_POS_Y = 78 "; std::cout << "\nInput yours: "; std::cin >> boty; std::cout << std::endl;
			
			main = new World(sizex, sizey, scale, botsize, entspawn, energy_spawn, energy_gain, stepcost, botx, boty);
			main->run();
		}
			
		do
		{	std::cout << "Would u like to repeat simulation? (y/n) ";
			std::cin >> answ;			
		}	while (!((answ == 'y') || (answ == 'n')));

		if (answ == 'y')
		{
			repeat = false;
		}
		else
		{
			repeat = true;
		}
	} 
	return 0;
}
