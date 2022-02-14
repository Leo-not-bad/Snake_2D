#include "Consts.hpp"


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

//void data_base::init_values(string name, string level_, int score_)
//{
//	name_of_player = name;
//	level = level_;
//	name_of_player = score_;
//}

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

void data_base::preparing_data_base()
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

void change_head_rotation(Sprite& sprite_snake_head, int moving, bool rotation, short definder, short snake_color)
{
	if (moving == -1 && !rotation && !definder)
	{
		if (Field[head.y1][head.x1 + 1] == snake_color)
		{
			sprite_snake_head.setOrigin(0, 20);
			sprite_snake_head.rotate(90.f);
		}
		else if (Field[head.y1][head.x1 - 1] == snake_color)
		{
			sprite_snake_head.setOrigin(0, 20);
			sprite_snake_head.rotate(-90.f);
		}
	}
	else if (moving == -1 && !rotation && definder == 1)
	{
		if (Field[head.y1 - 1][head.x1] == snake_color)
		{
			sprite_snake_head.setOrigin(0, 0);
			sprite_snake_head.rotate(90.f);
		}
		else if (Field[head.y1 + 1][head.x1] == snake_color)
		{
			sprite_snake_head.setOrigin(0, 0);
			sprite_snake_head.rotate(-90.f);
		}
	}
	else if (moving == 1 && !rotation && definder == 2)
	{
		if (Field[head.y1 - 1][head.x1] == snake_color)
		{
			sprite_snake_head.setOrigin(20, 20);
			sprite_snake_head.rotate(-90.f);
		}
		else if (Field[head.y1 + 1][head.x1] == snake_color)
		{
			sprite_snake_head.setOrigin(20, 20);
			sprite_snake_head.rotate(90.f);
		}
	}
	else if (moving == 1 && !rotation && definder == 3)
	{
		if (Field[head.y1][head.x1 + 1] == snake_color)
		{
			sprite_snake_head.setOrigin(20, 0);
			sprite_snake_head.rotate(-90.f);
		}
		else if (Field[head.y1][head.x1 - 1] == snake_color)
		{
			sprite_snake_head.setOrigin(20, 0);
			sprite_snake_head.rotate(90.f);
		}
	}
}

void start(string& string1, float delay = 0.3, float delay_tap = 0.01, short total_elements = 30, short snake_color_over = 255, short snake_color_for_purple = 0, short value_for_show_level = 0, bool Switch = 0)
{
	snake_body* body_coordinates = new snake_body[total_elements];

	snake_body last_coordinates_of_the_snake;

	SoundBuffer sound_buffer, sound_buffer_1;
	sound_buffer.loadFromFile("Take_event.wav");
	sound_buffer_1.loadFromFile("Knocked_out.wav");
	Sound sound_event(sound_buffer), sound_event_1(sound_buffer_1);


	RenderWindow window(VideoMode(950, 400), "Snake 2D!", Style::Close);

	Clock clock_object;
	data_base current_player;
	float time_;
	short definder = 1;
	float timer = 0.0, delay_save = delay;
	int moving = 0, moving1 = 0, moving2 = 0, moving3 = 0, value_of_score = 0;
	bool first_appearance = true;
	body_coordinates[total_elements - 1].x = 0;
	body_coordinates[total_elements - 1].y = 0;
	short moving_ = -1;
	bool rot = 1;
	short counter_of_body = 2;

	Texture texture_snake_head, texture_snake_body, texture_money_pack, texture_playing_field;
	texture_snake_head.loadFromFile("Snake_head.png");
	texture_snake_body.loadFromFile("Snake_body.jpg");
	texture_money_pack.loadFromFile("Money_pack.jpg");
	texture_playing_field.loadFromFile("playing_field_1.png");
	Font font_of_symbols;
	Text text_for_level, text_from_symbols, text_from_symbols_1, text_from_symbols_2, text_from_symbols_3, text_from_symbols_4, text_from_symbols_5, text_from_symbols_6, body_counts, body_counts_, body_counts1, body_counts2;
	font_of_symbols.loadFromFile("File_of_font.ttf");
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
	body_counts.setFont(font_of_symbols);
	body_counts.setCharacterSize(15);
	body_counts.setFillColor(Color::Red);
	body_counts.setString(to_string(total_elements));
	body_counts_.setFont(font_of_symbols);
	body_counts_.setCharacterSize(15);
	body_counts_.setFillColor(Color::Red);
	body_counts_.setString("/");
	body_counts1.setFont(font_of_symbols);
	body_counts1.setCharacterSize(15);
	body_counts1.setFillColor(Color::Red);
	body_counts2.setFont(font_of_symbols);
	body_counts2.setCharacterSize(15);
	body_counts2.setFillColor(Color::Red);
	body_counts2.setString("of  body");
	

	Sprite sprite_snake_head(texture_snake_head), sprite_snake_body(texture_snake_body), sprite_money_pack(texture_money_pack), sprite_playing_field(texture_playing_field);
	short pointx, pointy, snake_len, snake_color, snake_color_head, Field_points_of_eat;
	bool Up1 = false, Left1 = true, Right1 = false, Down1 = false;
	snake_color = 1;
	snake_color_head = 2;
	Field_points_of_eat = 3;
	snake_len = 3;
	bool acceleration = false; 
	int snake_head_turnx = 0, snake_head_turny = 0;
	string string_for_level;
	bool traffic_up = false, traffic_left = true, traffic_right = false, traffic_down = false;
	bool check_music_event = 0;
	
	
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
		srand(time(0));
		time_ = clock_object.getElapsedTime().asSeconds();
		clock_object.restart();
		timer += time_;

		// reading the movements and moving the snake


		Event p;
		while (window.pollEvent(p))
		{
			if (p.type == Event::Closed)
			{
				sound_event_1.play();
				window.close(); // end of game

				for (size_t i = 0; i < 20; ++i)
					for (size_t j = 0; j < 40; ++j)
						Field[i][j] = 0;


				current_player.name_of_player = string1;
				current_player.level = string_for_level;
				current_player.score = value_of_score;
				current_player.return_func_4() << current_player;
				current_player.return_func_4().close();
				current_player.preparing_data_base();
				/*current_player.init_values(string1, string_for_level, value_of_score);*/
				menu_of_end_of_game(string1, 0);
				return;
			}
			
			if (p.type == Event::KeyPressed)
			{
				if ((Keyboard::isKeyPressed(Keyboard::Up)) && (!Down1))
				{
					if (Up1)
						acceleration = true;
					
					rot = Up1;
					moving = -1;
					moving_ = moving;
					definder = 0;
					change_head_rotation(sprite_snake_head, moving, Up1, definder, snake_color);
					Up1 = true;
					Left1 = false;
					Right1 = false;
				}
				else if ((Keyboard::isKeyPressed(Keyboard::Left)) && (!Right1))
				{
					if (Left1)
						acceleration = true;
					
					rot = Left1;
					moving1 = -1;
					moving_ = moving1;
					definder = 1;
					change_head_rotation(sprite_snake_head, moving1, Left1, definder, snake_color);
					Left1 = true;
					Down1 = false;
					Up1 = false;
				}
				else if ((Keyboard::isKeyPressed(Keyboard::Right)) && (!Left1))
				{
					if (Right1)
						acceleration = true;
		            
					rot = Right1;
					moving2 = 1;
					moving_ = moving2;
					definder = 2;
					change_head_rotation(sprite_snake_head, moving2, Right1, definder, snake_color);
					Right1 = true;
					Up1 = false;
					Down1 = false;
					
				}
				else if ((Keyboard::isKeyPressed(Keyboard::Down)) && (!Up1))
				{
					if (Down1)
						acceleration = true;
			        
					rot = Down1;
					moving3 = 1;
					moving_ = moving3;
					definder = 3;
					change_head_rotation(sprite_snake_head, moving3, Down1, definder, snake_color);
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
			sound_event_1.play();
			window.close(); // end of game
			
			for (size_t i = 0; i < 20; ++i)
				for (size_t j = 0; j < 40; ++j)
					Field[i][j] = 0;

			
			current_player.name_of_player = string1;
			current_player.level = string_for_level;
			current_player.score = value_of_score;
			/*current_player.init_values(string1, string_for_level, value_of_score);*/
			current_player.return_func_4() << current_player;
			current_player.return_func_4().close();
			current_player.preparing_data_base();
			menu_of_end_of_game(string1, 0);
			return;
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
			short itter_;
			size_t i_;
			pointx = 1 + rand() % 39;
			pointy = 1 + rand() % 19;

			
			do{
				i_ = 0;
				itter_ = 0;
				for (;i_ < snake_len; ++i_)
					if ((pointx == head.x1) && (pointy == head.y1) || (pointx == body_coordinates[i_].x && pointy == body_coordinates[i_].y))
					{
						pointx = 1 + rand() % 39;
						pointy = 1 + rand() % 19;
						i_ = 0;
						itter_ = 0;
					}
					else
						++itter_;

			} while (itter_ != snake_len);

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
				counter_of_body += 1;
				check_music_event = 1;
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

				size_t i;
				short itter;
				size_t start_time, finish_time;
				start_time = clock();
				do
				{
					i = 0;
					itter = 0;
					for (;i < snake_len; ++i)
					{
						if ((pointx == head.x1 && pointy == head.y1) || (pointx == body_coordinates[i].x && pointy == body_coordinates[i].y))
						{
							srand(time(0));
							pointx = 1 + rand() % 39;
							pointy = 1 + rand() % 19;
							/*Field[pointy][pointx] = Field_points_of_eat;*/
							i = 0;
							itter = 0;
						}
						else
							++itter;

						if ((((finish_time = clock()) - start_time) / 1000) >= 2)
							break;
					}

				} while (itter != snake_len && (((finish_time = clock()) - start_time) / 1000) < 2);
						
				Field[pointy][pointx] = Field_points_of_eat;
			}
		}
		else if ((body_coordinates[total_elements - 1].x != 0 && body_coordinates[total_elements - 1].y != 0) && (head.x1 == pointx && head.y1 == pointy))
		{
			sound_event_1.play();
			window.close(); // end of game
		
			for (size_t i = 0; i < 20; ++i)
				for (size_t j = 0; j < 40; ++j)
					Field[i][j] = 0;


			current_player.name_of_player = string1;
			current_player.level = string_for_level;
			current_player.score = value_of_score;
			/*current_player.init_values(string1, string_for_level, value_of_score);*/
			current_player.return_func_4() << current_player;
			current_player.return_func_4().close();
			current_player.preparing_data_base();
			menu_of_end_of_game(string1, 1);
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////

		moving = moving1 = moving2 = moving3 = 0; acceleration = false;
		delay = delay_save; first_appearance = false;

		// output of elements on display

		window.draw(sprite_playing_field);
		for (size_t i = 0; i < height; ++i)
			for (size_t j = 0; j < width; ++j)
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

		/*if (Field[pointy][pointx] == Field_points_of_eat)*/
		
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
		body_counts1.setString(to_string(counter_of_body));
		body_counts1.setPosition(826, 278);
		body_counts_.setPosition(844, 278);
		body_counts.setPosition(851, 278);
		body_counts2.setPosition(883, 279);
		window.draw(text_from_symbols_6);
		window.draw(text_from_symbols_5);
		window.draw(text_from_symbols_2);
		window.draw(text_from_symbols_4);
		window.draw(body_counts);
		window.draw(body_counts_);
		window.draw(body_counts1);
		window.draw(body_counts2);

		if (check_music_event)
		{
			sound_event.play();
			check_music_event = 0;
		}

		window.display();
	
		//////////////////////////////////////////////////////////////////////////////////////////
	}
	
	delete[] body_coordinates;
}


void menu_of_field_for_input()
{	
	RenderWindow input_window(VideoMode(400, 400), "Field for input", Style::Titlebar);
	Texture texture_main_menu_field, texture_field_for_input;
	texture_main_menu_field.loadFromFile("Main_menu_field.png");
	texture_field_for_input.loadFromFile("Field_for_input.png");
	Sprite sprite_main_menu_field(texture_main_menu_field), sprite_field_for_input(texture_field_for_input);
	Color sprite_color = sprite_field_for_input.getColor();
	Font font_of_nickname_symbols;
	font_of_nickname_symbols.loadFromFile("File_of_font.ttf");
	Text nickname_symbols, template_text;
	nickname_symbols.setFont(font_of_nickname_symbols);
	nickname_symbols.setCharacterSize(32);
	nickname_symbols.setFillColor(Color::Black);
	template_text.setFont(font_of_nickname_symbols);
	template_text.setCharacterSize(20);
	template_text.setFillColor(Color::Black);
	
	string nickname, template_text_;
	template_text_ = "Enter your nickname";
	template_text.setString(template_text_);
	template_text.setPosition(67, 119);
	bool flug = 0;
	
	while (input_window.isOpen())
	{
		Event event_;

		while (input_window.pollEvent(event_))
		{

			if (event_.type == Event::TextEntered && flug)
			{
				if (event_.text.unicode < 128 && event_.key.code != 8)
				
					nickname.push_back(static_cast<char>(event_.text.unicode));

				if (nickname.size() > 7)
					nickname.erase(nickname.size() - 1);

				else if (event_.key.code == 8 && nickname.size() >= 1)
					nickname.erase(nickname.size() - 1);
			}

		    else if (event_.type == Event::MouseButtonPressed && !flug && event_.mouseButton.button == Mouse::Left && (event_.mouseButton.x >= 40 && event_.mouseButton.x <= 272) && (event_.mouseButton.y >= 104 && event_.mouseButton.y <= 162))
			{
					  sprite_field_for_input.setColor(Color(255, 244, 233, 100));
					  flug = 1;
					  //расскрасить только поле для ввода 
			}

			else if (event_.type == Event::MouseButtonPressed && event_.mouseButton.button == Mouse::Left && (event_.mouseButton.x >= 275 && event_.mouseButton.x <= 356) && (event_.mouseButton.y >= 104 && event_.mouseButton.y <= 162) && flug && (nickname.size() >= 3 && nickname.size() <= 7))//registration of cursor in place "go"   
			{
				  input_window.close();
				  start_window_of_game(nickname, sprite_main_menu_field, 0.3, 0.01, 30, 255, 0, 0, 0);
				  return;
			}
		  
			
		}

		input_window.draw(sprite_main_menu_field);
		sprite_field_for_input.setPosition(40, 100);
		input_window.draw(sprite_field_for_input);
		nickname_symbols.setString(nickname);
		nickname_symbols.setPosition(50, 113);
		input_window.draw(nickname_symbols);

		if (!flug)
		  input_window.draw(template_text);
		  
		input_window.display();

	}
}

void menu_of_table_of_leaders(string& string, Sprite& sprite_main_menu_field, float delay, float delay_tap, short total_elements, short value_for_show_level, short snake_color_over, short snake_color_for_purple, bool Switch)
{
	RenderWindow window_of_show_data_about_players(VideoMode(400, 400), "Table of leaders", Style::Close);
	ifstream file_object("file_for_data_about_players.txt", ios::in);
	Texture texture_field_for_table;
	texture_field_for_table.loadFromFile("Field_for_table.png");

	Sprite sprite_field_for_table(texture_field_for_table);
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
				start_window_of_game(string, sprite_main_menu_field, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level, Switch);
				return;
			}
		}

		window_of_show_data_about_players.draw(sprite_field_for_table);

		Font font_of_symbols_;
		Text text_from_symbols_[3];
		font_of_symbols_.loadFromFile("File_of_font.ttf");
		short y = 35, value_for_func_from_data_base = 0, x = 68;

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
					x += 117;
				else
					x += 102;
			}
			x = 68;
			y += 30;
			value_for_func_from_data_base = 0;
		}

		window_of_show_data_about_players.display();
	}
}

void menu_of_level(string& string, Sprite& sprite_main_menu_field, short snake_color_over, short snake_color_for_purple, bool Switch)
{
	short total_elements, value_for_show_level;
	float delay, delay_tap;

	RenderWindow window_level(VideoMode(400, 400), "Level", Style::Titlebar);
	Texture texture_bottons_easy, texture_bottons_medium, texture_bottons_hard, texture_bottons_unbearable;
	texture_bottons_easy.loadFromFile("Bottons_easy.png");
	texture_bottons_medium.loadFromFile("Bottons_medium.png");
	texture_bottons_hard.loadFromFile("Bottons_hard.png");
	texture_bottons_unbearable.loadFromFile("Bottons_unbearable.png");

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
						total_elements = TOTAL_ELEMENTS;
						delay = DELAY;
						delay_tap = DELAY_TAP;
						value_for_show_level = VALUE_FOR_SHOW_LEVEL;
						window_level.close();
						start_window_of_game(string, sprite_main_menu_field, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level, Switch);
						return;
					}
					else if ((p_level.mouseButton.x >= 75 && p_level.mouseButton.x <= 325) && (p_level.mouseButton.y >= 120 && p_level.mouseButton.y <= 180))
					{
						total_elements = TOTAL_ELEMENTS_;
						delay = DELAY_;
						delay_tap = DELAY_TAP_;
						value_for_show_level = VALUE_FOR_SHOW_LEVEL_;
						window_level.close();
						start_window_of_game(string, sprite_main_menu_field, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level, Switch);
						return;
					}
					else if ((p_level.mouseButton.x >= 130 && p_level.mouseButton.x <= 263) && (p_level.mouseButton.y >= 195 && p_level.mouseButton.y <= 250))
					{
						total_elements = TOTAL_ELEMENTS__;
						delay = DELAY__;
						delay_tap = DELAY_TAP__;
						value_for_show_level = VALUE_FOR_SHOW_LEVEL__;
						window_level.close();
						start_window_of_game(string, sprite_main_menu_field, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level, Switch);
						return;
					}
					else if ((p_level.mouseButton.x >= 25 && p_level.mouseButton.x <= 375) && (p_level.mouseButton.y >= 265 && p_level.mouseButton.y <= 335))
					{
						total_elements = TOTAL_ELEMENTS_1;
						delay = DELAY_1;
						delay_tap = DELAY_TAP_1;
						value_for_show_level = VALUE_FOR_SHOW_LEVEL_1;
						window_level.close();
						start_window_of_game(string, sprite_main_menu_field, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level, Switch);
						return;
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

void menu_of_color(string& string, Sprite& sprite_main_menu_field, float delay, float delay_tap, short total_elements, short value_for_show_level, bool Switch)
{
	RenderWindow window_color(VideoMode(400, 400), "Colors", Style::Titlebar);
	short snake_color_over, snake_color_for_purple;

	Texture texture_bottons_color_purple, texture_bottons_color_red, texture_bottons_color_blue;

	texture_bottons_color_purple.loadFromFile("Bottons_color_purple.png");
	texture_bottons_color_red.loadFromFile("Bottons_color_red.png");
	texture_bottons_color_blue.loadFromFile("Bottons_color_blue.png");

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
						snake_color_over = SNAKE_COLOR_OVER;
						snake_color_for_purple = SNAKE_COLOR_FOR_PURPLE;
						window_color.close();
						start_window_of_game(string, sprite_main_menu_field, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level, Switch);
						return;
					}
					else if ((p_color.mouseButton.x >= 134 && p_color.mouseButton.x <= 267) && (p_color.mouseButton.y >= 170 && p_color.mouseButton.y <= 230))
					{
						snake_color_over = SNAKE_COLOR_OVER_;
						snake_color_for_purple = SNAKE_COLOR_FOR_PURPLE_;
						window_color.close();
						start_window_of_game(string, sprite_main_menu_field, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level, Switch);
						return;
					}
					else if ((p_color.mouseButton.x >= 124 && p_color.mouseButton.x <= 280) && (p_color.mouseButton.y >= 252 && p_color.mouseButton.y <= 312))
					{
						snake_color_over = SNAKE_COLOR_FOR_PURPLE__;
						snake_color_for_purple = SNAKE_COLOR_OVER__;
						window_color.close();
						start_window_of_game(string, sprite_main_menu_field, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level, Switch);
						return;
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

void start_window_of_game(string& string, Sprite& sprite_main_menu_field, float delay = 0.3, float delay_tap = 0.01, short total_elements = 30, short snake_color_over = 255, short snake_color_for_purple = 0, short value_for_show_level = 0, bool Switch = 0)
{
	Music music_;
	music_.openFromFile("Jumping_Wall.wav");
	music_.play();
	music_.setLoop(true);

	RenderWindow window_head(VideoMode(400, 400), "Main Menu", Style::Close);

	Texture texture_main_menu_field, texture_bottons_level, texture_bottons_snake_color, texture_bottons_start_game, texture_title, texture_bottons_data_of_players;
	texture_title.loadFromFile("title.png");
	texture_bottons_start_game.loadFromFile("Bottons_start_game.png");
	texture_bottons_level.loadFromFile("Bottons_level.png");
	texture_bottons_snake_color.loadFromFile("Bottons_snake_color.png");
	texture_bottons_data_of_players.loadFromFile("Bottons_table_of_leaders.png");
	Sprite sprite_bottons_level(texture_bottons_level), sprite_bottons_snake_color(texture_bottons_snake_color), sprite_bottons_start_game(texture_bottons_start_game), sprite_title(texture_title), sprite_bottons_data_of_players(texture_bottons_data_of_players);
	bool turn_sound = true;

	while (window_head.isOpen())
	{
		Event p_head;

		while (window_head.pollEvent(p_head))
		{
			if (p_head.type == Event::Closed)
			{
				window_head.close();
				music_.stop();
				return;
			}
			    

			if (p_head.type == Event::MouseButtonPressed)
			{
				if (p_head.mouseButton.button == Mouse::Left)
				{
					if ((p_head.mouseButton.x >= 130 && p_head.mouseButton.x <= 264) && (p_head.mouseButton.y >= 64 && p_head.mouseButton.y <= 369))
					{
						if (p_head.mouseButton.y >= 64 && p_head.mouseButton.y <= 139)
						{
							window_head.close();
							music_.stop();
							start(string, delay, delay_tap, total_elements, snake_color_over, snake_color_for_purple, value_for_show_level, Switch);
							return;
						}
						else if (p_head.mouseButton.y >= 154 && p_head.mouseButton.y <= 195)
						{
							window_head.close();
							music_.stop();
							menu_of_level(string, sprite_main_menu_field, snake_color_over, snake_color_for_purple, Switch);
							return;
							
						}
						else if (p_head.mouseButton.y >= 224 && p_head.mouseButton.y <= 269)
						{
							window_head.close();
							music_.stop();
							menu_of_color(string, sprite_main_menu_field, delay, delay_tap, total_elements, value_for_show_level, Switch);
							return;
							
						}
						else if (p_head.mouseButton.y >= 294 && p_head.mouseButton.y <= 369)
						{
							window_head.close();
							music_.stop();
							menu_of_table_of_leaders(string, sprite_main_menu_field, delay, delay_tap, total_elements, value_for_show_level, snake_color_over, snake_color_for_purple, Switch);
							return;
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
		sprite_bottons_level.setPosition(130, 150);
		window_head.draw(sprite_bottons_level);
		sprite_bottons_snake_color.setPosition(129, 220);
		window_head.draw(sprite_bottons_snake_color);
		sprite_bottons_data_of_players.setPosition(126, 290);
		window_head.draw(sprite_bottons_data_of_players);

		window_head.display();
	}
}

void menu_of_end_of_game(string& string, bool check)
{
	SoundBuffer sound_buffer_of_end;
	sound_buffer_of_end.loadFromFile("Final_blow.wav");
	Sound end_sound(sound_buffer_of_end);

	RenderWindow window_end_of_game(VideoMode(400, 400), "If you think you ready", Style::Titlebar);
	const char string_of_end[] = "You lose, try agian if you don't afraid;)";
	Font font_of_symbols;
	font_of_symbols.loadFromFile("File_of_font.ttf");
	Text text_for_end;
	text_for_end.setFont(font_of_symbols);
	text_for_end.setString(string_of_end);
	text_for_end.setCharacterSize(22);
	text_for_end.setFillColor(Color::Black);

	Texture texture_cup;
	texture_cup.loadFromFile("Cup.png");
    Sprite sprite_cup(texture_cup);
	Text text_for_win;
	text_for_win.setFont(font_of_symbols);
	text_for_win.setString("You won, but don't relax:)");
	text_for_win.setCharacterSize(22);
	text_for_win.setFillColor(Color::Black);
	text_for_win.setPosition(30, 40);
	
	
	Texture texture_main_menu_field, texture_bottons_restart, texture_bottons_exit;
	texture_main_menu_field.loadFromFile("Main_menu_field.png");
	texture_bottons_restart.loadFromFile("Bottons_restart.png");
	texture_bottons_exit.loadFromFile("Bottons_exit.png");

	Sprite sprite_main_menu_field(texture_main_menu_field), sprite_bottons_restart(texture_bottons_restart), sprite_bottons_exit(texture_bottons_exit);
	
	if (!check)
		end_sound.play();

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
						start_window_of_game(string, sprite_main_menu_field, 0.3, 0.01, 30, 255, 0, 0);
						return;
					}

					else if (p_end_of_game.mouseButton.x > 231 && p_end_of_game.mouseButton.x < 350 && p_end_of_game.mouseButton.y > 90 && p_end_of_game.mouseButton.y < 145)
					{
						window_end_of_game.close();
						return;
					}
				}
			}
		}

		window_end_of_game.draw(sprite_main_menu_field);
		sprite_bottons_restart.setPosition(50, 90);
		sprite_bottons_exit.setPosition(231, 90);
		window_end_of_game.draw(sprite_bottons_restart);
		window_end_of_game.draw(sprite_bottons_exit);

		if (!check)
		{
			text_for_end.setPosition(15, 40);
			window_end_of_game.draw(text_for_end);
		}
		else
		{
			window_end_of_game.draw(text_for_win);
			sprite_cup.setPosition(285, 5);
			window_end_of_game.draw(sprite_cup);
		}

		window_end_of_game.display();
	}
}
