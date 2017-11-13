#ifndef __GAME_HPP
# define __GAME_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <ncurses.h>
# include <cstdint>
# include <unistd.h>
# include <stdlib.h>
# include "Player.hpp"
# define DOTS_NUM 7
# include <sys/time.h>

typedef struct {
	unsigned x;
	unsigned y;
} v2ui;

typedef struct {
	int x;
	int y;
} v2i;


class Game {

	void closeGame();
	WINDOW *win;
	WINDOW *TERMINAL;
	int	smalx;
	int smaly;
	int maxx;
	int maxy;
	int gamestatus;
public:
	v2i     canvas[DOTS_NUM][DOTS_NUM];
	Game();
	~Game();
	Game(const Game&);
	Game &operator=(Game&);
	void 	run();
	void 	set_canvas();
	int 	get_maxx();
	int		get_maxy();
	void	gameinit();
	void 	change_canvas(void);
	int 	gameover1();

	int 	win_OK(void);
	void	set_commet(void);
};

#endif