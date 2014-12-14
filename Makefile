NAME	=b3n_sim
SRCS	=$(wildcard srcs/*.c)
OBJS	=$(patsubst srcs/%.c,objs/%.o,$(SRCS))
HDRS	=includes
C_FLAGS	=-Wall -Wextra -Werror -DB3N_SIMULATOR
LD_FLAGS=-lSDL2 -lm

all: $(NAME)

$(NAME): $(OBJS)
	gcc -o $@ $^ $(LD_FLAGS)

objs/%.o: srcs/%.c
	gcc -o $@ -c $^ $(C_FLAGS) -I$(HDRS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
