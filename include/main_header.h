#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime> 
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;
using namespace sf;


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

	data_base(string m1, string m2, int m3);

	void preparing_data_base();

	friend istream& operator >> (istream& object, data_base& object_1);

	friend ostream& operator << (ostream& object, data_base const& object_1);

};

vector <data_base>& data_sorting(vector <data_base>&);
void menu_of_field_for_input();
void start(string&, float, float, short, short, short, short, bool);
void start_window_of_game(string&, Sprite&, float, float, short, short, short, short, bool);
void menu_of_color(string&, Sprite&, float, float, short, short, bool);
void menu_of_level(string&, Sprite&, short, short, bool);
void menu_of_table_of_leaders(string&, Sprite&, float, float, short, short, short, short, bool);
void menu_of_end_of_game(string&, bool);


struct snake_body
{
	short x, y;
};

struct snake_head
{
	short x1, y1;
};


snake_head random_snake_head();

int check(int, snake_body*);
void change_head_rotation(Sprite&, int, bool, short, short);


