#ifndef __PLAYER_HPP
# define __PLAYER_HPP
# define COMMET_NUM 13
# define BULLETS 25
#include "Game.hpp"
#include "Bullet.hpp"

typedef struct {
	int x;
	int y;
} v2ip;

class Player {
public:
	WINDOW *win;
	v2ip pos;
	int pos_x;
	int pos_y;
	int maxx;
	int maxy;
	int score;
	char pship;
	int hp;
	int maxHP;
	char w_type;
	int w_dam;
	int	iter;
	Bullet b[BULLETS];
	v2ip		commet[COMMET_NUM];
	Player(int x, int y, WINDOW *w);
	Player(const Player &pl);
	virtual ~Player();
	Player &operator=(Player &pl);
	void takeHP(int hp);
	int takehp();
	void	print_inf(WINDOW *wwin, int maxy);
	void	switch_key(int in_char, bool *pause, bool *exit_requested);
	void change_pos(void);
	void	set_commet(void);
	int	change_commet(void);
	void	shooting();
	void	shoot();
};
#endif