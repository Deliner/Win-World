#include <iostream>
#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


//Объект сущность, на деле является едой для бота
class Entity : public sf::Drawable
{
private:
	
public:
	//Конструкторы
	Entity(int posx, int posy, int size); //выставляет позиции и размер для отрисовки
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	//Функции
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//Данные
	int x; //позиция по x
	int y; //позиция по y

	sf::RectangleShape shape; //прямоугольник для отрисовки
};



//Структура реализующая двунаправленный список из сущностей
struct ent_data
{
public:
	Entity* ent_ptr; //указатель на сущность
	ent_data* next; //указатель на след структуру
	ent_data* prev; //указатель на пред структуру
};



//Класс для работы со списком сущностей
class ent_list
{
private:
	ent_data* first; //указывает на текущий первый элемент списка

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



//Главный класс мира
class World
{
public:
	//Конструкторы	
	World(); //создает мир со стандартными параметрами
	World(int sizex, int sizey, int scale, int botsize, int entspawn, int energy_spawn, int energy_gain, int stepcost, int botx, int boty); //создает мир с параметрами юзера

	//Функции
	void run(); //начинает игровой цикл

private:

	//Функции
	void processEvents(); //проверяет на события 

	void render(); //главная функция отвечающая за отображение
	void all_bot_draw(); //отображает всех ботов
	void all_ent_draw(); //отображает все сущности

	void update(); //обновляет состояние мира
	void botStep(bot_data* current); //для каждого бота вызывает функцию перемещения
	void botStat(Bot* ptr); //функция перемещения для бота	
	void entStep(); //для каждой сущности вызывает функцию смещения	
	void entStat(Entity* ptr); //функция смещения для сущности
	void entSpawn(); //за каждый цикл генерирует новую сущность
	
	int pos_check(int x, int y); //проверяет позицию
	bool ent_check(int x); //проверяет карту на сущность
	bool bot_check(int x); //проверяет карту на бота
	bool free_check(int x); //проверяет карту на свободное место
	
	void bot_mov(int x, int y, Bot* ptr); //плейсит бота
	void ent_rm(int x, int y); //удаляет сущность
	void bot_add(int x, int y); //добавляет бота
	
	void arr_shuffle(int arr[], int size, int shuffle); //переставляет элементы массива
	int screen_size(int x); //фозвращает нужный размер экрана
	void inf_print(); //выводит информацию за цикл

	//Константы	
	static const int BOT = 1; //Как отображать бота на карте
	static const int ENT = 2; //Как отображать сущность на карте 
	static const int FREE = 0; //Как отображать свободу на карте

	static const int MAX_WORLD_SIZE_X = 316; //максимальный рамер экрана по горизонтали
	static const int MAX_WORLD_SIZE_Y = 176; //максимальный размер экрана по вертикали
	
	//Переменные(константы), для задания пользователем
	int ENERGY_GAINED; //сколько получать энергии за сущность
	int BOT_STEP_COST;	//сколько энергии тратится при шаге
	int SCREEN_SCALE; //увеличиваем размер экрана
	int BOT_SIZE; //размер бота
	int ENT_NUM_SPAWN; //сколько спаунится сущностей за цикл
	int ENERGY_FOR_SPAWN; //сколько нужно энергии для спауна
	int BOT_POS_X; //на какой позиции спаунить бота по x
	int BOT_POS_Y; //на какой позиции спаунить бота по y
	int WORLD_SIZE_X; //размер мира по x
	int WORLD_SIZE_Y; //размер мира по y

	//Переменные
	int turn; //считает циклы
	int bot_num; //считает кол-во ботов
	int ent_num; //считает кол-во сущностей
	
	int step_arr[4] = { 1,2,3,4 }; //массив для выбора направления	
	int ent_spawn_arr[MAX_WORLD_SIZE_X]; //массив для выбора точки спауна сущности
	int world_arr[MAX_WORLD_SIZE_Y][MAX_WORLD_SIZE_X]; //массив карты мира

	bot_list bot_arr; //список для ботов
	ent_list ent_arr; //список для сущностей

	sf::Clock main_clock; //главные часы
	sf::RenderWindow world_window; //главное окно
};



//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////ОПРЕДЕЛЕНИЯ/////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////



//ДЛЯ КЛАССА СПИСКА СУЩНОСТИ
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

void ent_list::rm(Entity* ptr) //Переделать во второй раз
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



//ДЛЯ КЛАССА СПИСКА БОТОВ
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

void bot_list::rm(Bot* ptr) //ПРОВЕРИТЬ ДЕСТРУКТОР И НЕ РАБОТАЕТ С УДАЛЕНИЕ ПОСЛЕДНЕГО БОТА
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



//ДЛЯ КЛАССА СУЩНОСТИ
Entity::Entity(int posx, int posy, int size) : x(posx), y(posy), shape(sf::Vector2f(size, size))
{
	shape.setFillColor(sf::Color::Blue);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}



//ДЛЯ КЛАССА БОТОВ
Bot::Bot(int posx, int posy, int size) : x(posx), y(posy), shape(sf::Vector2f(size, size)), energy(20)
{

	shape.setFillColor(sf::Color::Red);

}

void Bot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}



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


	//bot_arr.add(new Bot(world_size_x/2, world_size_y-10, bot_size*world_scale));
	//ent_arr.add(new Entity(world_size_x, 0, bot_size*world_scale));
	//ent_arr.add(new Entity(int(world_size_x / 2 + 1), int(world_size_y / 2 + 1), bot_size*world_scale));
	//ent_arr.add(new Entity(world_size_x, world_size_y, bot_size*world_scale));
	

	//Дабавляем их на карту
	//world_arr[world_size_y - 10][world_size_x / 2] = BOT;
	//world_arr[world_size_y / 2 + 1][world_size_x / 2 + 1] = ENT;


}

World::World(int sizex, int sizey, int scale, int botsize, int entspawn, int energy_spawn, int energy_gain, int stepcost, int botx, int boty):

bot_num(0), ent_num(0), turn(0), SCREEN_SCALE(scale), BOT_SIZE(botsize),  ENERGY_FOR_SPAWN(energy_spawn),
ENERGY_GAINED(energy_gain), BOT_STEP_COST(stepcost), WORLD_SIZE_X(((sizex<MAX_WORLD_SIZE_X)?sizex:MAX_WORLD_SIZE_X)),
WORLD_SIZE_Y(((sizey<MAX_WORLD_SIZE_Y)?sizey:MAX_WORLD_SIZE_Y)), BOT_POS_X(((botx<WORLD_SIZE_X)?botx:WORLD_SIZE_X)),
BOT_POS_Y(((boty<WORLD_SIZE_Y)?boty:WORLD_SIZE_Y)), ENT_NUM_SPAWN(((entspawn<WORLD_SIZE_X)?entspawn:WORLD_SIZE_X)),
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


	if (alive)
	{
		if (ptr->energy > ENERGY_FOR_SPAWN)
		{

			arr_shuffle(step_arr, 4, 32);
			bool free_pos;
			free_pos = false;
			int posx;
			int posy;
			posx = ptr->x;
			posy = ptr->y;

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
					if ((posy > WORLD_SIZE_Y - 1) || (posy < 0)) { flag = false; break; }
					if (posx < 0) { posx = WORLD_SIZE_X - 1; }
					if (((ent_check(pos_check(posx, posy))) or (free_check(pos_check(posx, posy)))) && flag)
					{
						if (ent_check(pos_check(posx, posy)))
						{
							ent_rm(posx, posy);
						}
						free_pos = true;
						bot_add(posx, posy);


					}

					break;

				case 2: //right

					posx += 1;
					if ((posy > WORLD_SIZE_Y - 1) || (posy < 0)) { flag = false; break; }
					if (posx > WORLD_SIZE_X - 1) { posx = 0; }
					if (((ent_check(pos_check(posx, posy))) or (free_check(pos_check(posx, posy)))) && flag)
					{
						if (ent_check(pos_check(posx, posy)))
						{
							ent_rm(posx, posy);
						}
						free_pos = true;
						bot_add(posx, posy);
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
			world_arr[ptr->y][ptr->x] = 0; //Чистим карту мира от мертвого бота
			bot_arr.rm(ptr);
			alive = false;
			std::cout << 'd' << std::endl;
			}*/


		}
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
				if ((posy > WORLD_SIZE_Y - 1) || (posy < 0)) { flag = false; break; }
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
				if ((posy > WORLD_SIZE_Y - 1) || (posy < 0)) { flag = false; break; }
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
					if ((posy > WORLD_SIZE_Y - 1) || (posy < 0)) { flag = false; break; }

					posx -= 1;
					if (posx < 0) { posx = WORLD_SIZE_X - 1; }
					if ((free_check(pos_check(posx, posy))) && flag)
					{
						free_pos = true;
						bot_mov(posx, posy, ptr);
					}

					break;

				case 2: //right

					if ((posy > WORLD_SIZE_Y - 1) || (posy < 0)) { flag = false; break; }
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

		//Проверяем на перебор энергии


		//булевая функция возвращает тру если можно переместить бота на клетку
		//Добавить уничтожение травы и нормальное смещение


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



//ОСНОВНАЯ ФУНКЦИЯ
int main()
{
	//Выводим приветствие
	std::cout << std::endl << "Hey!!! My name is Del O'Ner, and it's my small world simulation.\n"
		<< "The RED scuare is called BOT, it can move up, down, left and right. The BLUE one is its food.\n"
		<< "BOT can destroy it and gain energy. Also u can change some params of this world.\n"
		<< "So have fun and good luck... And be carefull it non optimized =)\n";	
		


	//Цикл запуска симуляции в приложении
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

			//Вывод стандартных и пользовательский ввод
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