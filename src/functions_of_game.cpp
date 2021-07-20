#include "main_header.h"

snake_head head;
const int height = 20; // height of field
const int width = 40; // width of field
int Field[height][width] = { 0 };

template <typename T>
T data_base::return_func(T value)
{
	return value;
}

string data_base::return_func_1()
{
	return name_of_player;
}

string data_base::return_func_2()
{
	return level;
}

int data_base::return_func_3()
{
	return score;
}

ofstream data_base::return_func_4()
{
	ofstream object("file_for_data_about_players.txt", ios::app);
	object.seekp(ios::cur);
	return object;
}

data_base::data_base(string m1 = "", string m2 = "", int m3 = 0) : name_of_player(m1), level(m2), score(m3)
{}
	

istream& operator >> (istream& object, data_base& object_1)
{
	object >> object_1.name_of_player >> object_1.level >> object_1.score;
	return object;
}

ostream& operator << (ostream& object, data_base const& object_1)
{
	object << object_1.name_of_player << " " << object_1.level << " " << object_1.score << endl;
	return object;
}

snake_head random_snake_head()
{
	int pointx_head = 5 + rand() % 12;
	int pointy_head = 5 + rand() % 12;
	head.x1 = pointx_head;
	head.y1 = pointy_head;
	return head;
}

int check(int snake_len, snake_body* body_coordinates)
{
	if (head.x1 >= width || head.y1 >= height || head.x1 < 0 || head.y1 < 0)
		return 1;

	else
		for (int i = 1; i < snake_len - 1; ++i)
			if ((head.x1 == body_coordinates[i].x) && (head.y1 == body_coordinates[i].y))
				return 1;

	return 0;
}

void start(string& string1, float delay = 0.3, float delay_tap = 0.01, short total_elements = 100, short snake_color_over = 255, short snake_color_for_purple = 0, short value_for_show_level = 0)
{
	snake_body* body_coordinates = new snake_body[total_elements];

	snake_body last_coordinates_of_the_snake;

	RenderWindow window(VideoMode(950, 400), "Snake 2D!", Style::Close);

	srand(time(0));
	Clock clock_object;
	data_base current_player;
	float time;
	float timer = 0.0, delay_save = delay;
	int moving = 0, moving1 = 0, moving2 = 0, moving3 = 0, value_of_score = 0;
	bool first_appearance = true;
	body_coordinates[total_elements - 1].x = 0;
	body_coordinates[total_elements - 1].y = 0;

	Texture texture_snake_head, texture_snake_body, texture_money_pack, texture_playing_field;
	texture_snake_head.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Snake_head.jpg");
	texture_snake_body.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Snake_body.jpg");
	texture_money_pack.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Money_pack.jpg");
	texture_playing_field.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\playing_field_1.png");
	Font font_of_symbols;
	Text text_for_level, text_from_symbols, text_from_symbols_1, text_from_symbols_2, text_from_symbols_3, text_from_symbols_4, text_from_symbols_5, text_from_symbols_6;
	font_of_symbols.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\File_of_font.ttf");
	text_from_symbols.setFont(font_of_symbols);
	text_from_symbols.setString("Level:");
	text_from_symbols.setCharacterSize(15);
	text_from_symbols_1.setFont(font_of_symbols);
	text_from_symbols_1.setString("Score:");
	text_from_symbols_1.setCharacterSize(15);
	text_from_symbols.setFillColor(Color::Red);
	text_from_symbols_1.setFillColor(Color::Red);
	text_from_symbols_2.setFont(font_of_symbols);
	text_from_symbols_3.setFont(font_of_symbols);
	text_from_symbols_3.setString("Player:");
	text_from_symbols_3.setCharacterSize(15);
	text_from_symbols_3.setFillColor(Color::Red);
	text_from_symbols_4.setFont(font_of_symbols);
	text_from_symbols_4.setCharacterSize(15);
	text_from_symbols_4.setFillColor(Color::Red);
	text_from_symbols_5.setFont(font_of_symbols);
	text_from_symbols_5.setCharacterSize(15);
	text_from_symbols_5.setFillColor(Color::Red);
	text_from_symbols_5.setString("Color:");
	text_from_symbols_6.setFont(font_of_symbols);
	text_from_symbols_6.setCharacterSize(15);
	text_from_symbols_6.setFillColor(Color::Red);


	Sprite sprite_snake_head(texture_snake_head), sprite_snake_body(texture_snake_body), sprite_money_pack(texture_money_pack), sprite_playing_field(texture_playing_field);
	int pointx, pointy, snake_len = 3, snake_color, snake_color_head, Field_points_of_eat;
	bool Up1 = false, Left1 = true, Right1 = false, Down1 = false;
	snake_color = 1;
	snake_color_head = 2;
	Field_points_of_eat = 3;
	bool acceleration = false; 
	int snake_head_turnx = 0, snake_head_turny = 0;
	string string_for_level;
	bool traffic_up = false, traffic_left = true, traffic_right = false, traffic_down = false;
	

	// initialization of string for level

	switch (value_for_show_level)
	{
	case 0:
	{
		string_for_level = "easy";
		text_for_level.setString(string_for_level);
		break;
	}
	case 1:
	{
		string_for_level = "medium";
		text_for_level.setString(string_for_level);
		break;
	}
	case 2:
	{
		string_for_level = "hard";
		text_for_level.setString(string_for_level);
		break;
	}
	case 3:
	{
		string_for_level = "unbearable";
		text_for_level.setString(string_for_level);
		break;
	}
	}

	if (snake_color_over && !snake_color_for_purple)
		text_from_symbols_6.setString("red");
	else if (!snake_color_over && snake_color_for_purple)
		text_from_symbols_6.setString("blue");
	else
		text_from_symbols_6.setString("purple");


	text_from_symbols_4.setString(string1);


	while (window.isOpen())
	{
		time = clock_object.getElapsedTime().asSeconds();
		clock_object.restart();
		timer += time;

		// reading the movements and moving the snake


		Event p;
		while (window.pollEvent(p))
		{
			if (p.type == Event::Closed)
			{
				window.close();
				
				for (size_t i = 0; i < 20; ++i)
				for (size_t j = 0; j < 40; ++j)
					Field[i][j] = 0;

			preparing_data_base();
			current_player.name_of_player = string1;
			current_player.level = string_for_level;
			current_player.score = value_of_score;
			current_player.return_func_4() << current_player;
			current_player.return_func_4().close();
				
			menu_of_end_of_game(string1);
			}

			if (p.type == Event::KeyPressed)
			{
				if ((Keyboard::isKeyPressed(Keyboard::Up)) && (!Down1))
				{
					if (Up1)
						acceleration = true;
					moving = -1;
					Up1 = true;
					Left1 = false;
					Right1 = false;
				}
				else if ((Keyboard::isKeyPressed(Keyboard::Left)) && (!Right1))
				{
					if (Left1)
						acceleration = true;
					moving1 = -1;
					Left1 = true;
					Down1 = false;
					Up1 = false;
				}
				else if ((Keyboard::isKeyPressed(Keyboard::Right)) && (!Left1))
				{
					if (Right1)
						acceleration = true;
					moving2 = 1;
					Right1 = true;
					Up1 = false;
					Down1 = false;
				}
				else if ((Keyboard::isKeyPressed(Keyboard::Down)) && (!Up1))
				{
					if (Down1)
						acceleration = true;
					moving3 = 1;
					Down1 = true;
					Left1 = false;
					Right1 = false;
				}
			}
		}

		if (acceleration) // click acceleration 
			delay = delay_tap;



		if (first_appearance)
		{
			head = random_snake_head();
			Field[head.y1][head.x1] = snake_color_head;
			snake_len = 3;
			short b = 1;
			for (int i = 0; i < snake_len - 1; ++i)
			{
				body_coordinates[i].x = head.x1 + b;
				body_coordinates[i].y = head.y1;
				Field[head.y1][head.x1 + b] = snake_color;
				b += 1;
			}
		}

		//////////////////////////////////////////////////////////////////////////////////////////

		// twist of the snake

		if (moving && !acceleration)
		{
			Field[body_coordinates[snake_len - 2].y][body_coordinates[snake_len - 2].x] = 0;
			snake_head promejyt;
			snake_body promejyt1, promejyt2;
			promejyt = head;
			Field[head.y1][head.x1] = snake_color;
			head.y1 += moving;
			Field[head.y1][head.x1] = snake_color_head;
			promejyt1 = body_coordinates[0];
			body_coordinates[0].x = promejyt.x1;
			body_coordinates[0].y = promejyt.y1;

			for (int i = 1; i < snake_len - 1; ++i)
			{
				if (i == snake_len - 2)
					last_coordinates_of_the_snake = body_coordinates[i];
				promejyt2 = body_coordinates[i];
				body_coordinates[i] = promejyt1;
				promejyt1 = promejyt2;
			}
		}
		else if (moving1 && !acceleration)
		{
			Field[body_coordinates[snake_len - 2].y][body_coordinates[snake_len - 2].x] = 0;
			snake_head promejyt;
			snake_body promejyt1, promejyt2;
			promejyt = head;
			Field[head.y1][head.x1] = snake_color;
			head.x1 += moving1;
			Field[head.y1][head.x1] = snake_color_head;
			promejyt1 = body_coordinates[0];
			body_coordinates[0].x = promejyt.x1;
			body_coordinates[0].y = promejyt.y1;

			for (int i = 1; i < snake_len - 1; ++i)
			{
				if (i == snake_len - 2)
					last_coordinates_of_the_snake = body_coordinates[i];
				promejyt2 = body_coordinates[i];
				body_coordinates[i] = promejyt1;
				promejyt1 = promejyt2;
			}
		}
		else if (moving2 && !acceleration)
		{
			Field[body_coordinates[snake_len - 2].y][body_coordinates[snake_len - 2].x] = 0;
			snake_head promejyt;
			snake_body promejyt1, promejyt2;
			promejyt = head;
			Field[head.y1][head.x1] = snake_color;
			head.x1 += moving2;
			Field[head.y1][head.x1] = snake_color_head;
			promejyt1 = body_coordinates[0];
			body_coordinates[0].x = promejyt.x1;
			body_coordinates[0].y = promejyt.y1;

			for (int i = 1; i < snake_len - 1; ++i)
			{
				if (i == snake_len - 2)
					last_coordinates_of_the_snake = body_coordinates[i];
				promejyt2 = body_coordinates[i];
				body_coordinates[i] = promejyt1;
				promejyt1 = promejyt2;
			}
		}
		else if (moving3 && !acceleration)
		{
			Field[body_coordinates[snake_len - 2].y][body_coordinates[snake_len - 2].x] = 0;
			snake_head promejyt;
			snake_body promejyt1, promejyt2;
			promejyt = head;
			Field[head.y1][head.x1] = snake_color;
			head.y1 += moving3;
			Field[head.y1][head.x1] = snake_color_head;
			promejyt1 = body_coordinates[0];
			body_coordinates[0].x = promejyt.x1;
			body_coordinates[0].y = promejyt.y1;

			for (int i = 1; i < snake_len - 1; ++i)
			{
				if (i == snake_len - 2)
					last_coordinates_of_the_snake = body_coordinates[i];
				promejyt2 = body_coordinates[i];
				body_coordinates[i] = promejyt1;
				promejyt1 = promejyt2;
			}
		}

		if (check(snake_len, body_coordinates))
		{
			window.close(); // end of game
			
			for (size_t i = 0; i < 20; ++i)
				for (size_t j = 0; j < 40; ++j)
					Field[i][j] = 0;

			preparing_data_base();
			current_player.name_of_player = string1;
			current_player.level = string_for_level;
			current_player.score = value_of_score;
			current_player.return_func_4() << current_player;
			current_player.return_func_4().close();
			
			menu_of_end_of_game(string1);
		}


		////////////////////////////////////////////////////////////////////////////////////////////////

	   // acceleration and constant movement of the snake

		if (Up1)
		{
			if (Up1 && (timer > delay))
			{
				Field[body_coordinates[snake_len - 2].y][body_coordinates[snake_len - 2].x] = 0;
				snake_head promejyt;
				snake_body promejyt1, promejyt2;
				promejyt = head;
				Field[head.y1][head.x1] = snake_color;
				head.y1 += -1;
				Field[head.y1][head.x1] = snake_color_head;
				promejyt1 = body_coordinates[0];
				body_coordinates[0].x = promejyt.x1;
				body_coordinates[0].y = promejyt.y1;

				for (int i = 1; i < snake_len - 1; ++i)
				{
					if (i == snake_len - 2)
						last_coordinates_of_the_snake = body_coordinates[i];
					promejyt2 = body_coordinates[i];
					body_coordinates[i] = promejyt1;
					promejyt1 = promejyt2;
				}
				timer = 0;
			}
		}
		else if (Left1)
		{
			if (Left1 && (timer > delay))
			{
				Field[body_coordinates[snake_len - 2].y][body_coordinates[snake_len - 2].x] = 0;
				snake_head promejyt;
				snake_body promejyt1, promejyt2;
				promejyt = head;
				Field[head.y1][head.x1] = snake_color;
				head.x1 += -1;
				Field[head.y1][head.x1] = snake_color_head;
				promejyt1 = body_coordinates[0];
				body_coordinates[0].x = promejyt.x1;
				body_coordinates[0].y = promejyt.y1;

				for (int i = 1; i < snake_len - 1; ++i)
				{
					if (i == snake_len - 2)
						last_coordinates_of_the_snake = body_coordinates[i];
					promejyt2 = body_coordinates[i];
					body_coordinates[i] = promejyt1;
					promejyt1 = promejyt2;
				}
				timer = 0;
			}
		}
		else if (Right1)
		{
			if (Right1 && (timer > delay))
			{
				Field[body_coordinates[snake_len - 2].y][body_coordinates[snake_len - 2].x] = 0;
				snake_head promejyt;
				snake_body promejyt1, promejyt2;
				promejyt = head;
				Field[head.y1][head.x1] = snake_color;
				head.x1 += 1;
				Field[head.y1][head.x1] = snake_color_head;
				promejyt1 = body_coordinates[0];
				body_coordinates[0].x = promejyt.x1;
				body_coordinates[0].y = promejyt.y1;

				for (int i = 1; i < snake_len - 1; ++i)
				{
					if (i == snake_len - 2)
						last_coordinates_of_the_snake = body_coordinates[i];
					promejyt2 = body_coordinates[i];
					body_coordinates[i] = promejyt1;
					promejyt1 = promejyt2;
				}
				timer = 0;
			}
		}
		else if (Down1)
		{
			if (Down1 && (timer > delay))
			{
				Field[body_coordinates[snake_len - 2].y][body_coordinates[snake_len - 2].x] = 0;
				snake_head promejyt;
				snake_body promejyt1, promejyt2;
				promejyt = head;
				Field[head.y1][head.x1] = snake_color;
				head.y1 += 1;
				Field[head.y1][head.x1] = snake_color_head;
				promejyt1 = body_coordinates[0];
				body_coordinates[0].x = promejyt.x1;
				body_coordinates[0].y = promejyt.y1;

				for (int i = 1; i < snake_len - 1; ++i)
				{
					if (i == snake_len - 2)
						last_coordinates_of_the_snake = body_coordinates[i];
					promejyt2 = body_coordinates[i];
					body_coordinates[i] = promejyt1;
					promejyt1 = promejyt2;
				}
				timer = 0;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////


		// first appearance of food

		if (first_appearance)
		{
			pointx = 1 + rand() % 39;
			pointy = 1 + rand() % 19;

			for (int i = 0; i < snake_len - 1; ++i)
				if (((pointx == head.x1) && (pointy == head.y1)) || ((pointx == body_coordinates[i].x && pointy == body_coordinates[i].y)))
				{
					pointx = 1 + rand() % 39;
					pointy = 1 + rand() % 19;
				}

			Field[pointy][pointx] = Field_points_of_eat;
		}
		//////////////////////////////////////////////////////////////////////////////////////////////


		// meeting with food and it's next appearance

		if ((head.x1 == pointx && head.y1 == pointy) && (body_coordinates[total_elements - 1].x == 0 && body_coordinates[total_elements - 1].y == 0))
		{
			if ((body_coordinates[snake_len - 2].x != width) && (body_coordinates[snake_len - 2].x != 0) && (body_coordinates[snake_len - 2].y != height) && (body_coordinates[snake_len - 2].y != 0))
			{
				body_coordinates[snake_len - 1] = last_coordinates_of_the_snake;
				Field[last_coordinates_of_the_snake.y][last_coordinates_of_the_snake.x] = snake_color;
				snake_len += 1;
				pointx = 1 + rand() % 39;
				pointy = 1 + rand() % 19;
				switch (value_for_show_level)
				{
				case 0:
				{
					value_of_score += 40;
					break;
				}
				case 1:
				{
					value_of_score += 80;
					break;
				}
				case 2:
				{
					value_of_score += 160;
					break;
				}
				case 3:
				{
					value_of_score += 310;
					break;
				}
				}

				for (int i = 0; i < snake_len - 1; ++i)
					if ((pointx == head.x1 && pointy == head.y1) || (pointx == body_coordinates[i].x && pointy == body_coordinates[i].y))
					{
						pointx = 1 + rand() % 39;
						pointy = 1 + rand() % 19;
						Field[pointy][pointx] = Field_points_of_eat;
					}
				Field[pointy][pointx] = Field_points_of_eat;
			}
		}
		else if ((body_coordinates[total_elements - 1].x != 0 && body_coordinates[total_elements - 1].y != 0) && (head.x1 == pointx && head.y1 == pointy))
		{
			window.close(); // end of game
			
			for (size_t i = 0; i < 20; ++i)
				for (size_t j = 0; j < 40; ++j)
					Field[i][j] = 0;

			preparing_data_base();
			current_player.name_of_player = string1;
			current_player.level = string_for_level;
			current_player.score = value_of_score;
			current_player.return_func_4() << current_player;
			current_player.return_func_4().close();
			
			menu_of_end_of_game(string1);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////

		moving = moving1 = moving2 = moving3 = 0; acceleration = false;
		delay = delay_save; first_appearance = false;

		// output of elements on display

		window.draw(sprite_playing_field);
		for (int i = 0; i < height; ++i)
			for (int j = 0; j < width; ++j)
			{
				if (!Field[i][j])
					continue;
				if (Field[i][j] == snake_color_head)
				{
					sprite_snake_head.setPosition(head.x1 * 20, head.y1 * 20);
					window.draw(sprite_snake_head);
				}
				else if ((Field[i][j] != snake_color_head) && (Field[i][j] != Field_points_of_eat) && (Field[i][j] != 0))
				{
					sprite_snake_body.setPosition(j * 20, i * 20);
					sprite_snake_body.setColor(Color(snake_color_over, 0, snake_color_for_purple));
					window.draw(sprite_snake_body);
				}
			}
		sprite_money_pack.setPosition(pointx * 20, pointy * 20);
		window.draw(sprite_money_pack);
		text_from_symbols_3.setPosition(825, 120);
		text_from_symbols.setPosition(825, 160);
		text_from_symbols_1.setPosition(825, 200);
		window.draw(text_from_symbols);
		window.draw(text_from_symbols_1);
		window.draw(text_from_symbols_3);



		text_for_level.setFont(font_of_symbols);
		text_for_level.setString(string_for_level);
		text_for_level.setCharacterSize(15);
		text_for_level.setFillColor(Color::Red);
		text_for_level.setPosition(872, 160);
		window.draw(text_for_level);

		text_from_symbols_2.setString(to_string(value_of_score));
		text_from_symbols_2.setCharacterSize(15);
		text_from_symbols_2.setFillColor(Color::Red);
		text_from_symbols_2.setPosition(872, 200);
		text_from_symbols_4.setPosition(872, 120);
		text_from_symbols_5.setPosition(825, 240);
		text_from_symbols_6.setPosition(872, 240);
		window.draw(text_from_symbols_6);
		window.draw(text_from_symbols_5);
		window.draw(text_from_symbols_2);
		window.draw(text_from_symbols_4);

		window.display();

		//////////////////////////////////////////////////////////////////////////////////////////
	}
	delete[] body_coordinates;
}

void menu_of_field_for_input()
{	
	string string;

	cout << "input your nickname without spaces, it must be not longer than 7 characters:";
	cin >> string;

	while (string.size() > 7)
	{
		cout << endl << "your nickname is very long, repair input:";
		cin >> string;
	}

	start_window_of_game(string, 0.3, 0.01, 100, 255, 0, 0);
}

void preparing_data_base()
{
	ifstream file_object("file_for_data_about_players.txt", ios::in);
	vector <data_base> data_of_players;

	do
	{
		data_base intermediate_object;
		file_object >> intermediate_object;
		data_of_players.push_back(intermediate_object);
	} while (file_object);

	file_object.close();


	data_base promejyt;
	short count = 1;

	while (count > 0)
	{
		count = 0;
		for (int i = 0; i < data_of_players.size() - 1; ++i)
		{
			if (data_of_players[i].return_func_3() < data_of_players[i + 1].return_func_3())
			{
				promejyt = data_of_players[i];
				data_of_players[i] = data_of_players[i + 1];
				data_of_players[i + 1] = promejyt;
				count++;
			}
		}
	}

	data_of_players.erase(data_of_players.begin() + (data_of_players.size() - 1));

	if (data_of_players.size() >= size_t(10))
	{
		ofstream file_object_1("file_for_data_about_players.txt");
		data_of_players.erase(data_of_players.begin() + (data_of_players.size() - 1));
		for (size_t i = 0; i < data_of_players.size(); ++i)
			file_object_1 << data_of_players[i].return_func_1() << " " << data_of_players[i].return_func_2() << " " << data_of_players[i].return_func_3() << endl;
		file_object_1.close();
	}
}

void menu_of_table_of_leaders(string& string, Sprite& sprite_main_menu_field, float delay, float delay_tap, short total_elements, short value_for_show_level, short snake_color_over, short snake_color_for_purple)
{
	RenderWindow window_of_show_data_about_players(VideoMode(400, 400), "Table of leaders", Style::Close);
	ifstream file_object("file_for_data_about_players.txt", ios::in);
	vector <data_base> data_of_players;

	while (file_object)
	{
		data_base intermediate_object;
		file_object >> intermediate_object;
		data_of_players.push_back(intermediate_object);
	}
	file_object.close();


	// sorting

	data_base promejyt;
	short count = 1;

	while (count > 0)
	{
		count = 0;
		for (int i = 0; i < data_of_players.size() - 1; ++i)
		{
			if (data_of_players[i].return_func_3() < data_of_players[i + 1].return_func_3())
			{
				promejyt = data_of_players[i];
				data_of_players[i] = data_of_players[i + 1];
				data_of_players[i + 1] = promejyt;
				count++;
			}
		}
	}

	data_of_players.erase(data_of_players.begin() + (data_of_players.size() - 1));

	while (window_of_show_data_about_players.isOpen())
	{
		Event p_data;
		while (window_of_show_data_about_players.pollEvent(p_data))
		{
			if (p_data.type == Event::Closed)
			{
				window_of_show_data_about_players.close();
			
				start_window_of_game(string, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level);
			}
		}

		window_of_show_data_about_players.draw(sprite_main_menu_field);

		Font font_of_symbols_;
		Text text_from_symbols_[3];
		font_of_symbols_.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\File_of_font.ttf");
		short y = 15, value_for_func_from_data_base = 0, x = 80;

		for (int i = 0; i < data_of_players.size(); ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				text_from_symbols_[j].setFont(font_of_symbols_);

				switch (value_for_func_from_data_base)
				{
				case 0:
				{
					text_from_symbols_[j].setString(data_of_players[i].return_func(data_of_players[i].return_func_1()));
					break;
				}
				case 1:
				{
					text_from_symbols_[j].setString(data_of_players[i].return_func(data_of_players[i].return_func_2()));
					break;
				}
				case 2:
				{
					text_from_symbols_[j].setString(to_string(data_of_players[i].return_func(data_of_players[i].return_func_3())));
					break;
				}
				}

				text_from_symbols_[j].setCharacterSize(20);
				text_from_symbols_[j].setFillColor(Color::Black);
				text_from_symbols_[j].setPosition(x, y);

				window_of_show_data_about_players.draw(text_from_symbols_[j]);

				value_for_func_from_data_base += 1;

				if (value_for_func_from_data_base == 2)
					x += 110;
				else
					x += 80;
			}
			x = 80;
			y += 30;
			value_for_func_from_data_base = 0;
		}

		window_of_show_data_about_players.display();
	}
}

void menu_of_level(string& string, Sprite& sprite_main_menu_field, short snake_color_over, short snake_color_for_purple)
{
	short total_elements, value_for_show_level;
	float delay, delay_tap;

	RenderWindow window_level(VideoMode(400, 400), "Level", Style::Titlebar);
	Texture texture_bottons_easy, texture_bottons_medium, texture_bottons_hard, texture_bottons_unbearable;
	texture_bottons_easy.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_easy.png");
	texture_bottons_medium.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_medium.png");
	texture_bottons_hard.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_hard.png");
	texture_bottons_unbearable.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_unbearable.png");

	Sprite sprite_bottons_easy(texture_bottons_easy), sprite_bottons_medium(texture_bottons_medium), sprite_bottons_hard(texture_bottons_hard), sprite_bottons_unbearable(texture_bottons_unbearable);

	while (window_level.isOpen())
	{
		Event p_level;

		while (window_level.pollEvent(p_level))
		{
			if (p_level.type == Event::MouseButtonPressed)
			{
				if (p_level.mouseButton.button == Mouse::Left)
				{
					if ((p_level.mouseButton.x >= 130 && p_level.mouseButton.x <= 260) && (p_level.mouseButton.y >= 50 && p_level.mouseButton.y <= 108))
					{
						total_elements = 100;
						delay = 0.3;
						delay_tap = 0.01;
						value_for_show_level = 0;
						window_level.close();
						start_window_of_game(string, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level);
					}
					else if ((p_level.mouseButton.x >= 75 && p_level.mouseButton.x <= 325) && (p_level.mouseButton.y >= 120 && p_level.mouseButton.y <= 180))
					{
						total_elements = 200;
						delay = 0.2;
						delay_tap = 0.001;
						value_for_show_level = 1;
						window_level.close();
						start_window_of_game(string, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level);
					}
					else if ((p_level.mouseButton.x >= 130 && p_level.mouseButton.x <= 263) && (p_level.mouseButton.y >= 195 && p_level.mouseButton.y <= 250))
					{
						total_elements = 300;
						delay = 0.1;
						delay_tap = 0.001;
						value_for_show_level = 2;
						window_level.close();
						start_window_of_game(string, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level);
					}
					else if ((p_level.mouseButton.x >= 25 && p_level.mouseButton.x <= 375) && (p_level.mouseButton.y >= 265 && p_level.mouseButton.y <= 335))
					{
						total_elements = 400;
						delay = 0.1;
						delay_tap = 0.002;
						value_for_show_level = 3;
						window_level.close();
						start_window_of_game(string, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level);
					}
				}
			}
		}

		window_level.draw(sprite_main_menu_field);
		sprite_bottons_easy.setPosition(130, 50);
		window_level.draw(sprite_bottons_easy);
		sprite_bottons_medium.setPosition(75, 120);
		window_level.draw(sprite_bottons_medium);
		sprite_bottons_hard.setPosition(130, 195);
		window_level.draw(sprite_bottons_hard);
		sprite_bottons_unbearable.setPosition(25, 265);
		window_level.draw(sprite_bottons_unbearable);

		window_level.display();

	}
}

void menu_of_color(string& string, Sprite& sprite_main_menu_field, float delay, float delay_tap, short total_elements, short value_for_show_level)
{
	RenderWindow window_color(VideoMode(400, 400), "Colors", Style::Titlebar);
	short snake_color_over, snake_color_for_purple;

	Texture texture_bottons_color_purple, texture_bottons_color_red, texture_bottons_color_blue;

	texture_bottons_color_purple.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_color_purple.png");
	texture_bottons_color_red.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_color_red.png");
	texture_bottons_color_blue.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_color_blue.png");

	Sprite sprite_bottons_purple(texture_bottons_color_purple), sprite_bottons_red(texture_bottons_color_red), sprite_bottons_blue(texture_bottons_color_blue);

	while (window_color.isOpen())
	{
		Event p_color;

		while (window_color.pollEvent(p_color))
		{
			if (p_color.type == Event::MouseButtonPressed)
			{
				if (p_color.mouseButton.button == Mouse::Left)
				{
					if ((p_color.mouseButton.x >= 132 && p_color.mouseButton.x <= 267) && (p_color.mouseButton.y >= 90 && p_color.mouseButton.y <= 150))
					{
						snake_color_over = 255;
						snake_color_for_purple = 0;
						window_color.close();
						start_window_of_game(string, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level);
					}
					else if ((p_color.mouseButton.x >= 134 && p_color.mouseButton.x <= 267) && (p_color.mouseButton.y >= 170 && p_color.mouseButton.y <= 230))
					{
						snake_color_over = 0;
						snake_color_for_purple = 255;
						window_color.close();
						start_window_of_game(string, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level);
					}
					else if ((p_color.mouseButton.x >= 124 && p_color.mouseButton.x <= 280) && (p_color.mouseButton.y >= 252 && p_color.mouseButton.y <= 312))
					{
						snake_color_over = 255;
						snake_color_for_purple = 255;
						window_color.close();
						start_window_of_game(string, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level);
					}
				}
			}
		}


		window_color.draw(sprite_main_menu_field);
		sprite_bottons_red.setPosition(130, 90);
		window_color.draw(sprite_bottons_red);
		sprite_bottons_blue.setPosition(132, 170);
		window_color.draw(sprite_bottons_blue);
		sprite_bottons_purple.setPosition(122, 252);
		window_color.draw(sprite_bottons_purple);

		window_color.display();
	}
}

void menu_of_music(Sprite& sprite_main_menu_field)
{
	RenderWindow window_music(VideoMode(400, 400), "Music", Style::Titlebar);

	while (window_music.isOpen())
	{

	}

	//start_window_of_game();
}

void start_window_of_game(string& string, float delay = 0.3, float delay_tap = 0.01, short total_elemets = 100, short snake_color_over = 255, short snake_color_for_purple = 0, short value_for_show_level = 0)
{
	RenderWindow window_head(VideoMode(400, 400), "Main Menu", Style::Close);

	Texture texture_main_menu_field, texture_bottons_sound, texture_bottons_level, texture_bottons_snake_color, texture_bottons_start_game, texture_title, texture_bottons_data_of_players;
	texture_title.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\title.png");
	texture_main_menu_field.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Main_menu_field.png");
	texture_bottons_start_game.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_start_game.png");
	texture_bottons_sound.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_sound.png");
	texture_bottons_level.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_level.png");
	texture_bottons_snake_color.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_snake_color.png");
	texture_bottons_data_of_players.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_table_of_leaders.png");
	Sprite sprite_main_menu_field(texture_main_menu_field), sprite_bottons_sound(texture_bottons_sound), sprite_bottons_level(texture_bottons_level), sprite_bottons_snake_color(texture_bottons_snake_color), sprite_bottons_start_game(texture_bottons_start_game), sprite_title(texture_title), sprite_bottons_data_of_players(texture_bottons_data_of_players);
	bool turn_sound = true;
	while (window_head.isOpen())
	{
		Event p_head;

		while (window_head.pollEvent(p_head))
		{
			if (p_head.type == Event::Closed)
				window_head.close();

			if (p_head.type == Event::MouseButtonPressed)
			{
				if (p_head.mouseButton.button == Mouse::Left)
				{
					if ((p_head.mouseButton.x >= 130 && p_head.mouseButton.x <= 262) && (p_head.mouseButton.y >= 60 && p_head.mouseButton.y <= 395))
					{
						if (p_head.mouseButton.y >= 60 && p_head.mouseButton.y <= 130)
						{
							window_head.close();
							start(string, delay, delay_tap, total_elemets, snake_color_over, snake_color_for_purple, value_for_show_level);
						}
						else if (p_head.mouseButton.y >= 140 && p_head.mouseButton.y <= 180)
						{

						}
						else if (p_head.mouseButton.y >= 200 && p_head.mouseButton.y <= 242)
						{
							window_head.close();
							menu_of_level(string, sprite_main_menu_field, snake_color_over, snake_color_for_purple);
						}
						else if (p_head.mouseButton.y >= 260 && p_head.mouseButton.y <= 335)
						{
							window_head.close();
							menu_of_color(string, sprite_main_menu_field, delay, delay_tap, total_elemets, value_for_show_level);
						}
						else if (p_head.mouseButton.y >= 353 && p_head.mouseButton.y <= 395)
						{
							window_head.close();
							menu_of_table_of_leaders(string, sprite_main_menu_field, delay, delay_tap, total_elemets, value_for_show_level, snake_color_over, snake_color_for_purple);
						}
					}
				}
			}
		}

		window_head.draw(sprite_main_menu_field);
		sprite_title.setPosition(58, 0);
		window_head.draw(sprite_title);
		sprite_bottons_start_game.setPosition(127, 60);
		window_head.draw(sprite_bottons_start_game);
		sprite_bottons_sound.setPosition(130, 140);
		window_head.draw(sprite_bottons_sound);
		sprite_bottons_level.setPosition(130, 200);
		window_head.draw(sprite_bottons_level);
		sprite_bottons_snake_color.setPosition(130, 255);
		window_head.draw(sprite_bottons_snake_color);
		sprite_bottons_data_of_players.setPosition(130, 349);
		window_head.draw(sprite_bottons_data_of_players);

		window_head.display();
	}
}

void menu_of_end_of_game(string& string)
{
	RenderWindow window_end_of_game(VideoMode(400, 400), "If you think you ready", Style::Titlebar);
	const char string_of_end[] = "You lose, try agian if you don't afraid;)";
	Font font_of_symbols;
	font_of_symbols.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\File_of_font.ttf");
	Text text_for_end;
	text_for_end.setFont(font_of_symbols);
	text_for_end.setString(string_of_end);
	text_for_end.setCharacterSize(22);
	text_for_end.setFillColor(Color::Black);

	Texture texture_main_menu_field, texture_bottons_restart, texture_bottons_exit;
	texture_main_menu_field.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Main_menu_field.png");
	texture_bottons_restart.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_restart.png");
	texture_bottons_exit.loadFromFile("C:\\Users\\leo71\\source\\repos\\Змейка 2D\\Bottons_exit.png");

	Sprite sprite_main_menu_field(texture_main_menu_field), sprite_bottons_restart(texture_bottons_restart), sprite_bottons_exit(texture_bottons_exit);

	while (window_end_of_game.isOpen())
	{
		Event p_end_of_game;

		while (window_end_of_game.pollEvent(p_end_of_game))
		{
			if (p_end_of_game.type == Event::MouseButtonPressed)
			{
				if (p_end_of_game.mouseButton.button == Mouse::Left)
				{
					if (p_end_of_game.mouseButton.x > 50 && p_end_of_game.mouseButton.x < 187 && p_end_of_game.mouseButton.y > 90 && p_end_of_game.mouseButton.y < 145)
					{
						window_end_of_game.close();
						start_window_of_game(string, 0.3, 0.01, 100, 255, 0, 0);
					}

					else if (p_end_of_game.mouseButton.x > 231 && p_end_of_game.mouseButton.x < 350 && p_end_of_game.mouseButton.y > 90 && p_end_of_game.mouseButton.y < 145)
						window_end_of_game.close();
				}
			}
		}


		window_end_of_game.draw(sprite_main_menu_field);
		sprite_bottons_restart.setPosition(50, 90);
		sprite_bottons_exit.setPosition(231, 90);
		window_end_of_game.draw(sprite_bottons_restart);
		window_end_of_game.draw(sprite_bottons_exit);
		text_for_end.setPosition(15, 40);
		window_end_of_game.draw(text_for_end);

		window_end_of_game.display();
	}
}
