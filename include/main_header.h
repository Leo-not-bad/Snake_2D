#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>

using namespace sf;
using namespace std;

class data_base
{
public:

	string name_of_player;
	string level;
	int score;

	template <typename T>
	T return_func(T value);

	string return_func_1();

	string return_func_2();

	int return_func_3();

	ofstream return_func_4();

	data_base(string, string, int);

	friend istream& operator >> (istream& object, data_base& object_1);

	friend ostream& operator << (ostream& object, data_base const& object_1);
};

void menu_of_field_for_input();
void start(string&, float, float, short, short, short, short);
void start_window_of_game(string&, float, float, short, short, short, short);
void menu_of_color(string&, Sprite&, float, float, short, short);
void menu_of_level(string&, Sprite&, short, short);
void menu_of_table_of_leaders(string&, Sprite&, float, float, short, short, short, short);
void preparing_data_base();
void menu_of_end_of_game(string&);


struct snake_body
{
	int x, y;
};

struct snake_head
{
	int x1, y1;
};

snake_head random_snake_head();

int check(int snake_len, snake_body* body_coordinates);
