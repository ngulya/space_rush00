#include "Game.hpp"

Player::Player(int x, int y, WINDOW *w) {
	pos_x = -1;
	pos_y = -1;
	iter = 0;
	win = w;
	pos.x = x/2;
	maxx = x;
	maxy = y;
	pos.y = 2;
	pship = 'V';
	hp = 50;
	maxHP = 50;
	w_type = '\'';
}

void	Player::set_commet(){
	int tmp;
	int i = 0;

	while(i < COMMET_NUM)
	{
		tmp = rand() % (maxx);
		tmp = tmp < 1 ? 1 :tmp;
		tmp = tmp > maxx - 1 ? maxx - 1: tmp;
		commet[i].x = tmp;
			
		tmp = rand() % (maxy);
		tmp = tmp < 1 ? 1 :tmp;
		tmp = tmp > maxy - 1 ? maxy - 1: tmp;
		commet[i].y = tmp;
		i++;
	}
}

void	Player::shoot(){
	int i;

	i = 0;
	while(i < BULLETS)
	{
		if(b[i].posx == -1 && b[i].posy == -1)
		{
			init_pair(3, COLOR_RED, COLOR_BLACK);
			attron(COLOR_PAIR(3));
			b[i].posx = pos_x;
			b[i].posy = pos_y + 1;
			mvaddch(b[i].posy, b[i].posx, b[i].bullet);
			attroff(COLOR_PAIR(3));
			return;
		}
		i++;
	}
}

void	Player::shooting(){
	int i;
	int i_com;


	i_com = 0;
	i = 0;
	init_pair(2, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	while(i < BULLETS)
	{
		if(b[i].posx != -1 && b[i].posy != -1)
		{
			i_com = 0;
			while(i_com < COMMET_NUM)
			{
				if(b[i].posx == commet[i_com].x && (commet[i_com].y == b[i].posy || b[i].posy + 1 == commet[i_com].y))
				{
					mvaddch(b[i].posy, b[i].posx, ' ');
					b[i].posy = -1;
					b[i].posx = -1;
					mvaddch(commet[i_com].y, commet[i_com].x, ' ');
					commet[i_com].y = -1;
				}
				i_com++;
			}
		}
		i++;
	}
	i = 0;
	while(i<BULLETS)
	{
		
		if(b[i].posx != -1 && b[i].posy != -1){
			mvaddch(b[i].posy, b[i].posx, b[i].bullet);
			if(b[i].posy + 1 >= maxy -1)
			{
				mvaddch(b[i].posy, b[i].posx, ' ');
				b[i].posy = -1;
				b[i].posx= -1;
			}
			else{
				mvaddch(b[i].posy, b[i].posx, ' ');
				b[i].posy++;
				mvaddch(b[i].posy, b[i].posx, b[i].bullet);
			}
			
		}
		i++;
	}
	attroff(COLOR_PAIR(2));
}

int Player::change_commet(void){
	int i;
	int cX, cY;

	i = 0;
	int 	tmp;
	while(i < COMMET_NUM)
	{
		cX = commet[i].x;
		cY = commet[i].y;
		if(cY > 0 && cY < maxy - 1 && cX > 0 && cX < maxx -1)
			mvaddch(commet[i].y, commet[i].x, ' ');
		if(cY < 1){
			tmp = rand() % (maxx);
			tmp = tmp < 1 ? 1 :tmp;
			tmp = tmp > maxx - 1 ? maxx - 1: tmp;
			commet[i].x = tmp;
			commet[i].y = commet[i].y + maxy;
		}
		else{
			commet[i].y--;
		}
		i++;
	}
	i = 0;
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	while(i < COMMET_NUM)
	{
		cX = commet[i].x;
		cY = commet[i].y;
		if(cX == pos_x && cY == pos_y)
			return 0;
		if(cY > 0 && cY < maxy - 1 && cX > 0 && cX < maxx -1){
			mvaddch(commet[i].y, commet[i].x, '*');
		}
		i++;
	}
	attroff(COLOR_PAIR(1));
	usleep(45000);
	return 1;
	// refresh();
	// box(win,0,0);
	// usleep(45000);//level up
}

Player::Player(const Player &pl) {
	this->pos.x = pl.pos.x;
	this->pos.y = pl.pos.y;
	this->pship = pl.pship;
	this->hp = pl.hp;
	this->maxHP = pl.maxHP;
	this->w_type = pl.w_type;
}

Player::~Player() {
}

Player &Player::operator=(Player &pl) {
	this->pos.x = pl.pos.x;
	this->pos.y = pl.pos.y;
	this->pship = pl.pship;
	this->hp = pl.hp;
	this->maxHP = pl.maxHP;
	this->w_type = pl.w_type;
	return (*this);
}


void Player::change_pos(void){

	
	if(pos.y != pos_y || pos.x != pos_x)
	{
		if(pos.y > 0 && pos.y < maxy - 1 && pos.x > 0 && pos.x < maxx -1)
		{
			mvaddch(pos_y, pos_x, ' ');
			mvaddch(pos.y, pos.x, pship);
			pos_x = pos.x;
			pos_y = pos.y;
			refresh();
		}
		else{
			pos.x = pos_x;
			pos.y = pos_y;
		}
	}
	else{
		mvaddch(pos.y, pos.x, pship);
		refresh();
	}
}
void Player::takeDamage(int dam) {
	if (dam < this->hp)
		this->hp -= dam;
	else
	{
		//game over
	}
}

void Player::takeHP(int hp) {
	this->hp = (hp + this->hp >= maxHP) ? maxHP : this->hp + hp;
}

int Player::doDamage() {
	return (w_dam);
}