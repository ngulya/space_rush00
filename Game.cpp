#include "Game.hpp"


void	Game::set_canvas(){
	int tmp;
	int j = 0;
	int i = 0;

	while(i < DOTS_NUM)
	{
		j = 0;
		while(j < DOTS_NUM)
		{
			tmp = rand() % (maxx);
			tmp = tmp < 1 ? 1 :tmp;
			tmp = tmp > maxx - 1 ? maxx - 1: tmp;
			canvas[i][j].x = tmp;
			
			tmp = rand() % (maxy);
			tmp = tmp < 1 ? 1 :tmp;
			tmp = tmp > maxy - 1 ? maxy - 1: tmp;
			canvas[i][j].y = tmp;
			j++;
		}
		i++;
	}
 }


int 	Game::win_OK(void){
	int x;
	int y;

	x = 0;
	y = 0;
	getmaxyx(TERMINAL, y, x);

	if(maxy + 6 > y || maxx + 1 > x)
		return 0;
	return 1;
}

void Game::gameinit(){
	TERMINAL = initscr();
	maxy = 50;
	maxx = 100;

	win = newwin(maxy + 5, maxx, 0, 0);
	cbreak(); 
	noecho(); 

	keypad(win, true);
	nodelay(win, true);

	box(win,0,0);
	refresh();

	curs_set(0);
	if(!has_colors()) {
		endwin();
		std::cout << "ERROR: Terminal does not support color.\n";
		gamestatus = 1;
		exit(1);
	}
	start_color();
	attron(A_BOLD);
	attroff(A_BOLD);
	int xxx = 1;
	while(xxx < maxx - 1)
	{
		mvwprintw(win, maxy - 1, xxx, "_");
		xxx++;
	}
	gamestatus = 0;
}


 void Game::change_canvas(void){
	int i, j;
	int cX, cY;
	j = 0;
	i = 0;
	int 	tmp;
	while(i < DOTS_NUM)
	{
		j = 0;
		while(j < DOTS_NUM)
		{
			cX = canvas[i][j].x;
			cY = canvas[i][j].y;
			if(cY > 0 && cY < maxy - 1 && cX > 0 && cX < maxx -1)
				mvaddch(canvas[i][j].y, canvas[i][j].x, ' ');
			if(cY < 1){
				tmp = rand() % (maxx);
				tmp = tmp < 1 ? 1 :tmp;
				tmp = tmp > maxx - 1 ? maxx - 1: tmp;
				canvas[i][j].x = tmp;
				canvas[i][j].y = canvas[i][j].y + maxy;
			}
			else{
				canvas[i][j].y = canvas[i][j].y - 6;
			}
			j++;
		}
		i++;
	}
		j = 0;
		i = 0;
		while(i < DOTS_NUM)
		{
			j = 0;
			while(j < DOTS_NUM)
			{

				cX = canvas[i][j].x;
				cY = canvas[i][j].y;
				if(cY > 0 && cY < maxy - 1 && cX > 0 && cX < maxx -1)
					mvaddch(canvas[i][j].y, canvas[i][j].x, '.');
				j++;
			}
			i++;
		}
		usleep(45000);
}

int 	Game::get_maxy(){
	return maxy;
}

int 	Game::get_maxx(){
	return maxx;
}

Game::Game() {}

Game::~Game() {}

Game::Game(const Game &gm) {
	this->win = gm.win;
}

Game &Game::operator=(Game &gm) {
	this->win = gm.win;
	return (*this);
}


void Game::closeGame() {
	delwin(win);
	endwin();
}

int Game::gameover1(){

	int in_char = 0;

	int i = 1;
	int j = 1;
	while(i < maxx - 1)
	{
		j = 1;
		while (j < maxy - 1)
		{
			mvaddch(j, i, ' ');
			j++;
		}
		i++;
	}
	init_pair(3, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(3));
	mvwprintw(win, (maxy/2) - 1, (maxx/2) - 5,"%s", "GAME OVER");
	mvwprintw(win, maxy/2, (maxx/2 )- 8, "%s", "R-restart Q-quit");
	refresh();
	while(true)
	{
		in_char = wgetch(win);
		if(in_char == 'R' || in_char == 'r'){
			return 1;
		}
		if(in_char == 'q' || in_char == 'Q')
			return 0;
	}
	return 0;
}

void Game::run() {

	gameinit();
	if (!gamestatus) 
	{
		Player player(get_maxx(),get_maxy(), win);
		mvaddch(player.pos.y, player.pos.x, player.pship);
		int in_char;
		bool exit_requested = false;
		int tmp = 0;
			player.set_commet();
			set_canvas();
			while(true)
			{
				if(!win_OK()){
					endwin();
					std::cout<<"Give me a normal size"<<std::endl;
					exit(1);
				}
				in_char = wgetch(win);
				switch(in_char) {
					case 'q':
						exit_requested = true;
						break;
					case KEY_UP:
					case 'w':
						player.pos.y -= 1;
						break;
					case KEY_DOWN:
					case 's':
						player.pos.y += 1;
						break;
					case KEY_LEFT:
					case 'a':
						player.pos.x -= 1;
						break;
					case KEY_RIGHT:
					case 'd':
						player.pos.x += 1;
						break;
					case ' ':
						player.shoot();
						break;
					default:
						break;
					}
				player.change_pos();
				player.shooting();
				if(tmp == 3)
				{
					// player.shooting();
					change_canvas();
					if(!player.change_commet()){
						if(gameover1())
						{
							mvwprintw(win, (maxy/2) - 1, (maxx/2) - 5,"%s", "         ");
							mvwprintw(win, maxy/2, (maxx/2 )- 8, "%s", "                 ");
							player.pos.x = maxx/2;
							player.pos.y = 2;
							player.set_commet();
							set_canvas();
						}
						else
						{
							exit_requested = true;
							break;
						}
					}
					tmp = 0;
				}
				tmp++;
				if(exit_requested){
					// run = 0;
					break;
				}
				refresh();
			}
	}
	closeGame();
}