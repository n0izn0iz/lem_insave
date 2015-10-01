NAME=lem_in
SRCS=$(patsubst main.c,,$(patsubst %.c,srcs/%.c,$(shell ls srcs)))
OBJS=$(patsubst srcs/%.c,objs/%.o,$(SRCS))
CFLAGS=-c -g -Wall -Wextra -Werror -Iincludes -Ilibft/includes
LDFLAGS=-Llibft -lft -L. -llem_in
LIBFT=libft/libft.a
LIB=liblem_in.a
MAIN=objs/main.o

all: $(NAME) tests

$(NAME): $(MAIN) $(LIB) $(LIBFT)
	gcc -o $@ $(MAIN) $(LDFLAGS)

$(LIB): $(OBJS)
	ar -rs $@ $^

$(LIBFT):
	make -C libft

objs/%.o: srcs/%.c
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)
	rm -f $(MAIN)
	rm -f $(LIB)

fclean: clean
	rm -f $(NAME)
	make -C tests clean
	make -C libft fclean

tests:
	make -C tests

re: fclean all

.PHONY: all clean fclean re tests
