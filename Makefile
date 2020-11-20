NAME=miniRT
MINILIB=miniLIB
LIBFT=./libft/libft.a
SRCS=	vector3_util.c \
		vector3_util1.c \
		vector3_util2.c \
		vector3_util3.c \
		sphere.c \
		ray.c \
		hittable.c \
		scene.c \
		scene_fillimage.c \
		scene_render.c \
		minirt.c \
		camera.c \
		rand.c \
		lambertian.c \
		metal.c \
		dielectric.c 

OBJS=${SRCS:.c=.o}

all: ${NAME}
bonus: all
$(OBJS): $(SRCS)
	gcc -Wall -Wextra -Werror -I. -I./libft/. -c $(SRCS)

$(NAME): libftdo $(OBJS)
	cp $(LIBFT) $(MINILIB)
	gcc -Wall -Wextra -Werror -I. $(MINILIB) $(OBJS) main.c libmlx.dylib -o $(NAME)

libftdo:
	$(MAKE) -C ./libft bonus

clean:
	$(MAKE) -C ./libft clean
	rm -f $(OBJS)
	rm -f $(MINILIB)
fclean:
	$(MAKE) -C ./libft fclean
	rm -f $(OBJS)
	rm -f $(NAME)
	rm -f $(MINILIB)
re: fclean all
.PHONY: all clean fclean re libftdo bonus