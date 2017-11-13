NAME	= ft_retro

CC		= clang++
FLG		= -Wall -Werror -Wextra

SRC		= main.cpp Game.cpp Player.cpp Bullet.cpp

ATTR	= -lncurses

OBJ		= $(SRC:.cpp=.o)

$(NAME) : $(OBJ)
	$(CC) $(FLG) $(OBJ) $(ATTR) -o $(NAME)

.cpp.o	:
	$(CC) $(FLG) -o $@ -c $<

all		: $(NAME)

clean	:
	rm -f $(OBJ)

fclean	: clean
	rm -f $(NAME)

re		: fclean all