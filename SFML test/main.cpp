#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>



class Entity : public sf::Drawable
{
private:
	//Данные
	//Функции

public:
	//Конструкторы
	Entity();
	Entity(int a, int b);
	Entity(int a, int b, int s);
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	//Функции
	void step();
	void s_id(int a);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//Данные
	int x;
	int y;
	int energy;
	int id;
	sf::RectangleShape shape;
};

struct ent_data
{
public:
	Entity* ent_ptr;
	ent_data* next;
	ent_data* prev;
/*	~ent_data()
	{
		delete ent_ptr;
		delete next;
	}*/
};

class ent_list
{
private:
	ent_data* first;
public:
	//Конструктор
	ent_list();

	//Функции
	void add(Entity* ptr);
	void rm(Entity* ptr);
	ent_data* find(Entity* ptr);
	//ent_data* find_prev(Entity* ptr);
	ent_data* r_first();
	Entity* xy_find(int x, int y);
};


class Bot : public sf::Drawable
{
private:



public:
	//Конструкторы
	Bot();
	Bot(int a, int b);
	Bot(int a, int b, int s);
	Bot(const Bot&) = delete;
	Bot& operator=(const Bot&) = delete;

	//Функции

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//Данные
	int x;
	int y;
	int color;
	int id;
	int energy;
	sf::RectangleShape shape;
};

struct bot_data
{
	Bot* bot_ptr;
	bot_data* next;
	bot_data* prev;
};

class bot_list
{
private:
	bot_data * first;
public:
	//Конструктор
	bot_list();

	//Функции
	void add(Bot* ptr);
	void rm(Bot* ptr);
	bot_data* find(Bot* ptr);
	//bot_data* find_prev(Bot* ptr);
	bot_data* r_first();

};

class World
{
public:

	//Конструктор	
	World();

	//Функции
	void run();

private:

	//Функции
	void render();
	void update();
	void processEvents();
	void all_bot_draw();
	void all_ent_draw();
	void botStep();
	void entStep();
	void botStat(Bot* ptr);
	void entStat(Entity* ptr);
	void entAdd();
	void arr_shuffle(int arr[], int size, int shuffle);
	void bot_mov(int x, int y, Bot* ptr);
	void ent_rm(int x, int y);


	int pos_check(int x, int y);

	bool ent_check(int x);
	bool bot_check(int x);
	bool free_check(int x);

	//Константы
	static const int BOT_STEP_COST = 2;
	static const int BOT = 1;
	static const int ENT = 2;
	static const int FREE = 0;
	static const int ENERGY = 10;

	static const int world_size_x = 32;
	static const int world_size_y = 24;
	static const int world_scale = 4;
	static const int bot_size = 2;

	//Переменные
	int bot_num;
	int ent_num;
	int cur_bot_id;
	int cur_ent_id;
	int step_arr[4] = { 1,2,3,4 };
	
	int ent_spawn_arr[world_size_x];
	int world_arr[world_size_y][world_size_x];
	bot_list bot_arr;
	ent_list ent_arr;
	Bot* bot_ptr;
	Entity* ent_ptr;

	sf::Clock clock;
	sf::RenderWindow world_window;
};



//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////ОПРЕДЕЛЕНИЯ/////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////




Entity* ent_list::xy_find(int x, int y)
{
	ent_data* current;
	current = r_first();

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
	ent_data* current;
	current = first;

	while ((current->ent_ptr != ptr) && (current->next != NULL))
	{
		current = current->next;
	}

	return current;
}

/*
ent_data* ent_list::find_prev(Entity* ptr)
{
	ent_data* current;
	current = first;

	while (((current->next)->ent_ptr != ptr) && ((current->next)->next != NULL) && (current->next=NULL))
	{
		current = current->next;
	}

	return current;
}
*/
void ent_list::rm(Entity* ptr) //Переделать во второй раз
{
	/*
	ent_data* current;
	current = find(ptr);
	ent_data* prev;
	prev = find_prev(ptr);


	if (prev != current)
	{	
				
		delete current->ent_ptr;
		
		prev->next = current->next;
		delete current;
	}
	else
	{
		first = current->next;
		delete current->ent_ptr;
		delete current;

	}*/

	ent_data* current;
	current = find(ptr);
	
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

bot_data* bot_list::find(Bot* ptr)
{
	bot_data* current;
	current = first;

	while ((current->bot_ptr != ptr) && (current->next != NULL))
	{
		current = current->next;
	}

	return current;
}

/*
bot_data* bot_list::find_prev(Bot* ptr)
{
	bot_data* prev;
	prev = first;

	if (prev->next != NULL)
	{
		while (((prev->next)->bot_ptr != ptr) && ((prev->next)->next != NULL))
		{
			prev = prev->next;
		}
	}
	
	return prev;
}
*/

void bot_list::rm(Bot* ptr) //ПРОВЕРИТЬ ДЕСТРУКТОР И НЕ РАБОТАЕТ С УДАЛЕНИЕ ПОСЛЕДНЕГО БОТА
{
	bot_data* current;
	current = find(ptr);

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

Entity::Entity(int a, int b, int s) : x(a), y(b), shape(sf::Vector2f(s, s))
{
	shape.setFillColor(sf::Color::Blue);
}

Entity::Entity(int a, int b) : x(a), y(b), shape(sf::Vector2f(2, 2))
{
	shape.setFillColor(sf::Color::Blue);
}

Entity::Entity() : x(0), y(0), energy(10), shape(sf::Vector2f(2, 2))
{
	shape.setFillColor(sf::Color::Blue);
}

void  Entity::step()
{
	y++;
}

void Entity::s_id(int a)
{
	id = a;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

Bot::Bot(int a, int b, int s) : x(a), y(b), shape(sf::Vector2f(s, s)), color(0), id(0), energy(50)
{

	shape.setFillColor(sf::Color::Red);

}

Bot::Bot(int a, int b) : x(a), y(b), shape(sf::Vector2f(2, 2)), color(0), id(0), energy(50)
{

	shape.setFillColor(sf::Color::Red);

}

Bot::Bot() :  x(0), y(0), shape(sf::Vector2f(2, 2))
{

	shape.setFillColor(sf::Color::Red);

}

void Bot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}


World::World() : world_window(sf::VideoMode(int(world_size_x*bot_size*world_scale*1.5+bot_size*world_scale), int(world_size_y*bot_size*world_scale*1.5+bot_size * world_scale)), "The Wooooooorldo!!!"), bot_num(0), ent_num(0), cur_bot_id(0), cur_ent_id(0)
{
	//Инициализация пустой карты мира
	for (int i = 0; i < world_size_y; i++)
	{
		for (int j = 0; j < world_size_x; j++)
		{
			world_arr[i][j] = 0;
		}
	}

	for (int i = 0; i < world_size_x; i++) //REMAKE
	{
		ent_spawn_arr[i] = i;
	}

	//Добавляем первого бота и сущность
	bot_arr.add(new Bot(int(10), int(10), bot_size*world_scale));
	//ent_arr.add(new Entity(world_size_x, 0, bot_size*world_scale));
	//ent_arr.add(new Entity(int(world_size_x / 2 + 1), int(world_size_y / 2 + 1), bot_size*world_scale));
	//ent_arr.add(new Entity(world_size_x, world_size_y, bot_size*world_scale));
	

	//Дабавляем их на карту
	world_arr[10][10] = BOT;
	//world_arr[world_size_y / 2 + 1][world_size_x / 2 + 1] = ENT;


}

void World::ent_rm(int x, int y)
{
	world_arr[y][x] = FREE;
	ent_arr.rm(ent_arr.xy_find(x, y));
}

void World::bot_mov(int x, int y, Bot* ptr)
{
//	std::cout << "Going to mov to " << x << " " << y << " " << "there are " << world_arr[x][y] << std::endl; //DELETE
	
	world_arr[y][x] = BOT;
	world_arr[ptr->y][ptr->x] = FREE;	
	ptr->x = x;
	ptr->y = y;
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

void World::arr_shuffle(int arr[], int size, int shuffle)
{

	srand(static_cast<int>(time(0)));

	for (int i = 0; i < shuffle; i++)
	{
		int j, a, b;
		a = rand() % size; //Переделать генератор
		b = rand() % size;

		j = arr[a];
		arr[a] = arr[b];
		arr[b] = j;
	}

}

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


void World::botStat(Bot* ptr)
{
	bool alive;
	alive = true;

	//Уменьшаем энергию бота
	ptr->energy -= BOT_STEP_COST;

	//Проверяем бота на жизнеспособность
	if (ptr->energy <= 0)
	{	
		world_arr[ptr->y][ptr->x] = 0; //Чистим карту мира от мертвого бота
		bot_arr.rm(ptr);
		alive = false;
		std::cout << 'd' << std::endl;
	}

	if (alive)
	{

		//Перемешиваем массив проверки точек
		arr_shuffle(step_arr, 4, 32);
		bool free_pos;
		free_pos = false;
		int posx;
		int posy;
		posx = ptr->x;
		posy = ptr->y;
		//Начинаем перемещение и поглощение бота

		//Проверяем по массиву есть ли рядом сущность

		for (int i = 0; i < 4; i++)
		{
			bool flag;
			flag = true;
			posx = ptr->x;
			posy = ptr->y;

			switch (step_arr[i])
			{

			case 1: //left

				posx -= 1;
				if ((posy > world_size_y - 1) || (posy < 0)) { flag = false; break; }
				if (posx < 0) { posx = world_size_x - 1; }
				if ((ent_check(pos_check(posx, posy))) && flag)
				{
					free_pos = true;
					ent_rm(posx, posy);
					ptr->energy += ENERGY;
					bot_mov(posx, posy, ptr);
				}

				break;

			case 2: //right

				posx += 1;
				if ((posy > world_size_y - 1) || (posy < 0)) { flag = false; break; }
				if (posx > world_size_x - 1) { posx = 0; }
				if ((ent_check(pos_check(posx, posy))) && flag)
				{
					free_pos = true;
					ent_rm(posx, posy);
					ptr->energy += ENERGY;
					bot_mov(posx, posy, ptr);
				}

				break;

			case 3: //down

				posy += 1;
				if ((posy > world_size_y - 1) || (posy < 0)) { flag = false; break; }
				if ((ent_check(pos_check(posx, posy))) && flag)
				{
					free_pos = true;
					ent_rm(posx, posy);
					ptr->energy += ENERGY;
					bot_mov(posx, posy, ptr);
				}

				break;

			case 4: //up

				posy -= 1;
				if ((posy > world_size_y - 1) || (posy < 0)) { flag = false; break; }
				if ((ent_check(pos_check(posx, posy))) && flag)
				{

					free_pos = true;
					ent_rm(posx, posy);
					ptr->energy += ENERGY;
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

		//Проверяем есть ли рядом свободная точка
		if (!free_pos)
		{
			arr_shuffle(step_arr, 4, 32);

			for (int i = 0; i < 4; i++)
			{
				posx = ptr->x;
				posy = ptr->y;

				bool flag;
				flag = true;

				switch (step_arr[i])
				{

				case 1: //left
					if ((posy > world_size_y - 1) || (posy < 0)) { flag = false; break; }

					posx -= 1;
					if (posx < 0) { posx = world_size_x - 1; }
					if ((free_check(pos_check(posx, posy))) && flag)
					{
						free_pos = true;
						bot_mov(posx, posy, ptr);
					}

					break;

				case 2: //right

					if ((posy > world_size_y - 1) || (posy < 0)) { flag = false; break; }
					posx += 1;
					if (posx > world_size_x - 1) { posx = 0; }
					if ((free_check(pos_check(posx, posy))) && flag)
					{
						free_pos = true;
						bot_mov(posx, posy, ptr);
					}

					break;

				case 3: //down

					posy += 1;
					if ((posy > world_size_y - 1) || (posy < 0)) { flag = false; break; }
					if ((free_check(pos_check(posx, posy))) && flag)
					{
						free_pos = true;
						bot_mov(posx, posy, ptr);
					}

					break;

				case 4: //up

					posy -= 1;
					if ((posy > world_size_y - 1) || (posy < 0)) { flag = false; break; }
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

		//Проверяем на перебор энергии


		//булевая функция возвращает тру если можно переместить бота на клетку
		//Добавить уничтожение травы и нормальное смещение


	}
	
}

void World::botStep() //НЕ РАБОТАЕТ КОДА НЕТ БОТОВ
{
	bot_data* current;
	current = bot_arr.r_first();
	/*
	bool flag;
	flag = true;

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
			std::cout << '1' << std::endl;
				botStat(current->bot_ptr);
			
		} while (current->next != NULL);
	}
	*/

	if 




}

void World::entStat(Entity* ptr)
{
	int x, y;
	x = ptr->x;
	y = ptr->y;
	
		
	if ((y != world_size_y-1)&&(free_check(pos_check(x,y+1))))
	{
		ptr->y += 1;
		world_arr[y][x] = FREE;
		world_arr[y + 1][x] = ENT;

	}

}

void World::entStep()
{
	ent_data* current;
	current = ent_arr.r_first();
	bool flag;
	flag = true;

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
			//std::cout << "1\n"; DELETE

		} while (current->next != NULL);
	}
}

void World::entAdd()
{

	//Перемешиваем точки спавна сущности
	arr_shuffle(ent_spawn_arr, world_size_x, world_size_x*100);

		
	int i;
	int j;
	int pos;
	i = 0;
	j = 0;
	pos = 0;

	//Проверяем свободные точки для 2 сущностей и спауним их, если таких нет забиваем
	while((i<world_size_x)&&(j<2))
	{	
		i++;		
		pos = ent_spawn_arr[i];

		if (free_check(pos_check(pos,0)))
		{
			ent_arr.add(new Entity(pos, 0 , bot_size*world_scale));
			world_arr[0][pos] = ENT;
			j++;
		}
		
	}

}

void World::update()
{
	entAdd();
	entStep();
	
	
	botStep();
	std::cout << '3' << std::endl;
		
		
}

void World::all_bot_draw()
{
	bot_data* current;
	current = bot_arr.r_first();
	bool flag;
	flag = true;
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
			(*(current->bot_ptr)).shape.setPosition(int(((*(current->bot_ptr)).x)*bot_size*world_scale*1.5), int(((*(current->bot_ptr)).y)*bot_size*world_scale*1.5));
			world_window.draw(*(current->bot_ptr));
			//std::cout << current->bot_ptr->x << " " << current->bot_ptr->y << std::endl; //DELETE
		} while (current->next != NULL);
	}
}

void World::all_ent_draw()
{
	ent_data* current;
	current = ent_arr.r_first();
	bool flag;
	flag = true;

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
			(*(current->ent_ptr)).shape.setPosition(int(((*(current->ent_ptr)).x)*bot_size*world_scale)*1.5, int(((*(current->ent_ptr)).y)*bot_size*world_scale*1.5));
			//std::cout << current->ent_ptr->x << " " << current->ent_ptr->y << std::endl; //DELETE
			world_window.draw(*(current->ent_ptr));
		} while (current->next != NULL);
	}
}

void World::render()
{
	world_window.clear(sf::Color::White);

	all_bot_draw();
	all_ent_draw();

	world_window.display();
}

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

void World::run()
{
	while (world_window.isOpen())
	{
		processEvents();
		update();
		render();

		std::cout << "Cicle\n"; //DELETE

		clock.restart();
		while (clock.getElapsedTime().asMicroseconds() < 50000) {}
	}
}



int main()
{

	World world;
	world.run();

	return 0;
}