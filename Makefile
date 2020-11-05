NAME=miniRT
LIBFT=./libft/libft.a
SRCS=	vector3_util.c \
		vector3_util1.c \
		vector3_util2.c \
		ray.c


OBJS=${SRCS:.c=.o}

all: ${NAME}
bonus: all
$(OBJS): $(SRCS)
	gcc -Wall -Wextra -Werror -I. -I./libft -c $(SRCS)

$(NAME): libftdo $(OBJS)
	cp $(LIBFT) $(NAME)
	ar rc $(NAME) $(OBJS)

libftdo:
	$(MAKE) -C ./libft bonus

clean:
	$(MAKE) -C ./libft clean
	rm -f $(OBJS)

fclean:
	$(MAKE) -C ./libft fclean
	rm -f $(OBJS)
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re libftdo bonus