NAME=visualizer
SRCS=$(patsubst main.cpp,,$(patsubst %.cpp,srcs/%.cpp,$(shell ls srcs)))
OBJS=$(patsubst srcs/%.cpp,objs/%.o,$(SRCS))
CFLAGS=-c -g -Wall -Wextra -Werror -I../includes -I../libft/includes -I$(HOME)/.brew/include
LDFLAGS= -L.. -llem_in -L../libft -L$(HOME)/.brew/lib -lft -lsfml-graphics -lsfml-window -lsfml-system -rpath $(HOME)/.brew/Cellar/sfml/2.3_1/lib

all: $(NAME)

$(NAME): $(OBJS)
	g++ -o $@ $^ $(LDFLAGS)

objs/%.o: srcs/%.cpp
	g++ $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
