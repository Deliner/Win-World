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





//ДЛЯ КЛАССА МИРА

//КОНСТРУКТОРЫ
World::World() : bot_num(0), ent_num(0), turn(0), SCREEN_SCALE(2), BOT_SIZE(2),
ENT_NUM_SPAWN(4), ENERGY_FOR_SPAWN(100), ENERGY_GAINED(10), BOT_STEP_COST(2), BOT_POS_X(150), BOT_POS_Y(78), WORLD_SIZE_X(300), WORLD_SIZE_Y(156),
world_window(sf::VideoMode(screen_size(WORLD_SIZE_X), screen_size(WORLD_SIZE_Y)), "The Wooooooorldo!!!")
{

	//Инициализация пустой карты мира
	for (int i = 0; i < WORLD_SIZE_Y; i++)
	{
		for (int j = 0; j < WORLD_SIZE_X; j++)
		{
			world_arr[i][j] = 0;
		}
	}

	for (int i = 0; i < WORLD_SIZE_X; i++) //REMAKE
	{
		ent_spawn_arr[i] = i;
	}

	//Добавляем первого бота и сущность
	bot_add(WORLD_SIZE_X / 2, WORLD_SIZE_Y / 2);
}
//переделать конструктор
World::World(int sizex, int sizey, int scale, int botsize, int entspawn, int energy_spawn, int energy_gain, int stepcost, int botx, int boty) :	//не работает инициализация с проверкой для количества спауна сущности
	bot_num(0), ent_num(0), turn(0), SCREEN_SCALE(scale), BOT_SIZE(botsize), ENERGY_FOR_SPAWN(energy_spawn),
	ENERGY_GAINED(energy_gain), BOT_STEP_COST(stepcost), WORLD_SIZE_X(((sizex<MAX_WORLD_SIZE_X) ? sizex : MAX_WORLD_SIZE_X)),
	WORLD_SIZE_Y(((sizey<MAX_WORLD_SIZE_Y) ? sizey : MAX_WORLD_SIZE_Y)),/*BOT_POS_X(((botx<WORLD_SIZE_X) ? botx : WORLD_SIZE_X))*/ BOT_POS_X(botx),
	/*BOT_POS_Y(((boty<WORLD_SIZE_Y) ? boty : WORLD_SIZE_Y))*/BOT_POS_Y(boty), /*ENT_NUM_SPAWN(((entspawn<WORLD_SIZE_X) ? entspawn : WORLD_SIZE_X))*/ENT_NUM_SPAWN(entspawn),
	world_window(sf::VideoMode(screen_size(WORLD_SIZE_X), screen_size(WORLD_SIZE_Y)), "The Wooooooorldo!!!")
{
	//Инициализация пустой карты мира
	for (int i = 0; i < WORLD_SIZE_Y; i++)
	{
		for (int j = 0; j < WORLD_SIZE_X; j++)
		{
			world_arr[i][j] = 0;
		}
	}

	for (int i = 0; i < WORLD_SIZE_X; i++) //REMAKE
	{
		ent_spawn_arr[i] = i;
	}

	//Добавляем первого бота и сущность
	bot_add(BOT_POS_X, BOT_POS_Y);
}



//фУНКЦИИ
//проверка на события
void World::processEvents()
{
	sf::Event event;
	while (world_window.pollEvent(event))
	{
		if ((event.type == sf::Event::Closed) or ((event.type == sf::Event::KeyPressed) and (event.key.code == sf::Keyboard::Escape)))
		{
			world_window.close();
		}
	}
}



//отрисовка
void World::render()
{
	world_window.clear(sf::Color::White);

	all_bot_draw();
	all_ent_draw();

	world_window.display();
}

void World::all_bot_draw()
{
	bot_data* current = bot_arr.r_first();
	bool flag = true;

	if (current != NULL)
	{
		do
		{
			if (flag)
			{
				flag = false;
			}
			else
			{
				current = current->next;
			}
			(*(current->bot_ptr)).shape.setPosition(int(((*(current->bot_ptr)).x)*BOT_SIZE*SCREEN_SCALE*1.5), int(((*(current->bot_ptr)).y)*BOT_SIZE*SCREEN_SCALE*1.5));
			world_window.draw(*(current->bot_ptr));
			//std::cout << current->bot_ptr->x << " " << current->bot_ptr->y << std::endl; //DELETE
		} while (current->next != NULL);
	}
}

void World::all_ent_draw()
{
	ent_data* current = ent_arr.r_first();
	bool flag = true;

	if (current != NULL)
	{
		do
		{
			if (flag)
			{
				flag = false;
			}
			else
			{
				current = current->next;
			}

			(*(current->ent_ptr)).shape.setPosition(int(((*(current->ent_ptr)).x)*BOT_SIZE*SCREEN_SCALE)*1.5, int(((*(current->ent_ptr)).y)*BOT_SIZE*SCREEN_SCALE*1.5));
			world_window.draw(*(current->ent_ptr));
		} while (current->next != NULL);
	}
}



//обновление логики
void World::update()
{
	botStep(bot_arr.r_first());
	entStep();

	entSpawn();
}
//переделать
void World::botStep(bot_data* current) //НЕ РАБОТАЕТ КОДА НЕТ БОТОВ
{
	bool flag = true;

	if (current != NULL)
	{
		do
		{
			if (flag)
			{
				current = bot_arr.r_first();
				flag = false;
			}
			else
			{
				current = current->next;
			}
			botStat(current->bot_ptr);
		} while (current->next != NULL);
	}
}
//переделать
void World::botStat(Bot* ptr)
{
	bool alive = true;
	bool full = false;

	//Уменьшаем энергию бота
	ptr->energy -= BOT_STEP_COST;

	//Проверяем бота на жизнеспособность
	if (ptr->energy <= 0)
	{
		/*world_arr[ptr->y][ptr->x] = 0; //Чистим карту мира от мертвого бота
		bot_arr.rm(ptr);
		alive = false;
		std::cout << 'd' << std::endl;*/

		ptr->energy += BOT_STEP_COST;
	}

	if (alive) //тут пытаемся создать нового бота
	{
		if (ptr->energy > ENERGY_FOR_SPAWN)
		{
			arr_shuffle(step_arr, 4, 32);

			bool free_pos = false;
			int posx;
			int posy;


			for (int i = 0; i < 4; i++)
			{
				bool flag = true;
				posx = ptr->x;
				posy = ptr->y;


				switch (step_arr[i])
				{
				case 1: //left

					posx -= 1;

					if (posx < 0) { posx = WORLD_SIZE_X - 1; } //для смещения через левую грань

					if (((ent_check(pos_check(posx, posy))) or (free_check(pos_check(posx, posy)))) && flag)
					{
						if (ent_check(pos_check(posx, posy)))
						{
							ent_rm(posx, posy);
						}

						free_pos = true;
						bot_add(posx, posy);
						ptr->energy -= ENERGY_FOR_SPAWN / 4;
					}
					break;

				case 2: //right

					posx += 1;

					if (posx > WORLD_SIZE_X - 1) { posx = 0; } //для смещения через правую грань

					if (((ent_check(pos_check(posx, posy))) or (free_check(pos_check(posx, posy)))) && flag)
					{
						if (ent_check(pos_check(posx, posy)))
						{
							ent_rm(posx, posy);
						}

						free_pos = true;
						bot_add(posx, posy);
						ptr->energy -= ENERGY_FOR_SPAWN / 4;
					}
					break;

				case 4: //down

					posy += 1;
					if ((posy > WORLD_SIZE_Y - 1) || (posy < 0)) { flag = false; break; }

					if (((ent_check(pos_check(posx, posy))) or (free_check(pos_check(posx, posy)))) && flag)
					{
						if (ent_check(pos_check(posx, posy)))
						{
							ent_rm(posx, posy);
						}

						free_pos = true;
						bot_add(posx, posy);
						ptr->energy -= ENERGY_FOR_SPAWN / 4;
					}
					break;

				case 3: //up

					posy -= 1;
					if ((posy > WORLD_SIZE_Y - 1) || (posy < 0)) { flag = false; break; }

					if (((ent_check(pos_check(posx, posy))) or (free_check(pos_check(posx, posy)))) && flag)
					{

						if (ent_check(pos_check(posx, posy)))
						{
							ent_rm(posx, posy);
						}

						free_pos = true;
						bot_add(posx, posy);
						ptr->energy -= ENERGY_FOR_SPAWN / 4;
					}
					break;

				default:
					break;
				}

				if (free_pos)
				{
					break;
				}
			}


			/*if (!free_pos)
			{
			УДАЛЯЕМ БОТА
			}
			*/
		}
	}


	if (alive) //пытаемся съесть сущность
	{
		//Перемешиваем массив проверки точек
		arr_shuffle(step_arr, 4, 32);

		bool free_pos = false;
		int posx;
		int posy;


		//Проверяем по массиву есть ли рядом сущность
		for (int i = 0; i < 4; i++)
		{
			bool flag = true;
			posx = ptr->x;
			posy = ptr->y;


			switch (step_arr[i])
			{

			case 1: //left

				posx -= 1;

				if (posx < 0) { posx = WORLD_SIZE_X - 1; }
				if ((ent_check(pos_check(posx, posy))) && flag)
				{
					free_pos = true;
					ent_rm(posx, posy);
					ptr->energy += ENERGY_GAINED;
					bot_mov(posx, posy, ptr);
				}
				break;

			case 2: //right

				posx += 1;

				if (posx > WORLD_SIZE_X - 1) { posx = 0; }
				if ((ent_check(pos_check(posx, posy))) && flag)
				{
					free_pos = true;
					ent_rm(posx, posy);
					ptr->energy += ENERGY_GAINED;
					bot_mov(posx, posy, ptr);
				}
				break;

			case 4: //down

				posy += 1;

				if ((posy > WORLD_SIZE_Y - 1) || (posy < 0)) { flag = false; break; }
				if ((ent_check(pos_check(posx, posy))) && flag)
				{
					free_pos = true;
					ent_rm(posx, posy);
					ptr->energy += ENERGY_GAINED;
					bot_mov(posx, posy, ptr);
				}
				break;

			case 3: //up

				posy -= 1;

				if ((posy > WORLD_SIZE_Y - 1) || (posy < 0)) { flag = false; break; }
				if ((ent_check(pos_check(posx, posy))) && flag)
				{
					free_pos = true;
					ent_rm(posx, posy);
					ptr->energy += ENERGY_GAINED;
					bot_mov(posx, posy, ptr);
				}
				break;

			default:
				break;
			}

			if (free_pos)
			{
				break;
			}
		}


		if (!free_pos) //если рядом нет сущности
		{
			arr_shuffle(step_arr, 4, 32);


			for (int i = 0; i < 4; i++)
			{
				bool flag = true;
				posx = ptr->x;
				posy = ptr->y;


				switch (step_arr[i])
				{

				case 1: //left

					posx -= 1;

					if (posx < 0) { posx = WORLD_SIZE_X - 1; }

					if ((free_check(pos_check(posx, posy))) && flag)
					{
						free_pos = true;
						bot_mov(posx, posy, ptr);
					}
					break;

				case 2: //right

					posx += 1;

					if (posx > WORLD_SIZE_X - 1) { posx = 0; }

					if ((free_check(pos_check(posx, posy))) && flag)
					{
						free_pos = true;
						bot_mov(posx, posy, ptr);
					}
					break;

				case 4: //down

					posy += 1;

					if ((posy > WORLD_SIZE_Y - 1) || (posy < 0)) { flag = false; break; }

					if ((free_check(pos_check(posx, posy))) && flag)
					{
						free_pos = true;
						bot_mov(posx, posy, ptr);
					}
					break;

				case 3: //up

					posy -= 1;

					if ((posy > WORLD_SIZE_Y - 1) || (posy < 0)) { flag = false; break; }

					if ((free_check(pos_check(posx, posy))) && flag)
					{
						free_pos = true;
						bot_mov(posx, posy, ptr);
					}
					break;

				default:
					break;
				}

				if (free_pos)
				{
					break;
				}
			}
		}
	}
}

void World::entStep() //ПЕРЕДЕЛАТЬ ДЛЯ ПУСТОГО СПИСКА
{
	ent_data* current = ent_arr.r_first();
	bool flag = true;


	if (current != NULL)
	{
		do
		{
			if (flag)
			{
				flag = false;
			}
			else
			{
				current = current->next;
			}

			entStat(current->ent_ptr);
		} while (current->next != NULL);
	}
}

void World::entStat(Entity* ptr)
{
	int x = ptr->x;
	int y = ptr->y;

	if ((y != WORLD_SIZE_Y - 1) && (free_check(pos_check(x, y + 1))))
	{
		ptr->y += 1;
		world_arr[y][x] = FREE;
		world_arr[y + 1][x] = ENT;

	}
}

void World::entSpawn()
{
	//Перемешиваем точки спавна сущности
	arr_shuffle(ent_spawn_arr, WORLD_SIZE_X, WORLD_SIZE_X * 100);

	int i = 0;
	int j = 0;

	//Проверяем свободные точки для нужжного колва сущностей и спауним их, если таких нет забиваем
	while ((i<WORLD_SIZE_X) && (j<ENT_NUM_SPAWN))
	{
		i++;

		if (free_check(pos_check(ent_spawn_arr[i], 0)))
		{
			ent_arr.add(new Entity(ent_spawn_arr[i], 0, BOT_SIZE*SCREEN_SCALE));
			world_arr[0][ent_spawn_arr[i]] = ENT;
			j++;

			ent_num++; //мировой счетчик
		}
	}
}



//проверка карты мира
int World::pos_check(int x, int y)
{
	if (world_arr[y][x] == FREE)
	{
		return FREE;
	}
	else if (world_arr[y][x] == BOT)
	{
		return BOT;
	}
	else if (world_arr[y][x] == ENT)
	{
		return ENT;
	}
}

bool World::ent_check(int x)
{
	if (x == ENT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool World::bot_check(int x)
{
	if (x == BOT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool World::free_check(int x)
{
	if (x == FREE)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//взаимодействие с объектами
void World::bot_mov(int x, int y, Bot* ptr)
{
	world_arr[y][x] = BOT;
	world_arr[ptr->y][ptr->x] = FREE;

	ptr->x = x;
	ptr->y = y;
}

void World::ent_rm(int x, int y)
{
	world_arr[y][x] = FREE;
	ent_arr.rm(ent_arr.xy_find(x, y));

	ent_num--; //мировой счетчик сущностей
}

void World::bot_add(int x, int y)
{
	world_arr[y][x] = BOT;
	bot_arr.add(new Bot(x, y, BOT_SIZE*SCREEN_SCALE));

	bot_num++; //мировой счетчик ботов
}



//добавочные
void World::arr_shuffle(int arr[], int size, int shuffle)
{
	srand(static_cast<int>(main_clock.getElapsedTime().asSeconds())); //посев генератора от основного времени

	for (int i = 0; i < shuffle; i++)
	{
		int j, a, b;

		a = rand() % (size);
		b = rand() % (size);

		j = arr[a];
		arr[a] = arr[b];
		arr[b] = j;
	}
}

int World::screen_size(int x)
{
	x = static_cast<int>(x*BOT_SIZE*SCREEN_SCALE*1.5); //подстраиваем размер экрана под игровое поле
	return x;
}

void World::inf_print()
{
	std::cout << "Current turn is " << turn << std::endl << "Bot number is " << bot_num << std::endl << "Ent number is " << ent_num << std::endl << std::endl << std::endl;
}

void World::run()
{
	while (world_window.isOpen())
	{
		turn++;

		processEvents();
		update();
		render();

		inf_print();
	}
}