NAME=miniRT
CC=gcc
FLAG=-Wall -Wextra -Werror
LIBFT=./libft/libft.a
MINILIBX=./minilibx_mms/libmlx.dylib
RTLIB=rtlib.a
SRCS=	vector3_util.c \
		vector3_util1.c \
		vector3_util2.c \
		vector3_util3.c \
		vector3_util4.c \
		sphere.c \
		ray.c \
		hittable.c \
		material.c \
		scene.c \
		scene_fillimage.c \
		scene_render.c \
		scene_setscene.c \
		export_bmp.c \
		minirt.c \
		camera.c \
		rand.c \
		lambertian.c \
		solid_color.c \
		checker.c \
		dulight.c \
		plane.c \
		triangle.c \
		triangle2.c \
		square.c \
		cylinder.c \
		cylinder2.c \
		readrt.c

SRCSB=	vector3_util.c \
		vector3_util1.c \
		vector3_util2.c \
		vector3_util3.c \
		vector3_util4.c \
		sphere.c \
		ray.c \
		hittable.c \
		material.c \
		scene.c \
		scene_fillimage.c \
		scene_render_bonus.c \
		scene_setscene.c \
		export_bmp.c \
		minirt.c \
		camera.c \
		rand.c \
		lambertian.c \
		metal.c \
		dielectric.c \
		solid_color.c \
		checker.c \
		dulight.c \
		plane.c \
		triangle.c \
		triangle2.c \
		square.c \
		cylinder.c \
		cylinder2.c \
		readrt_bonus.c \
		rainbow.c \
		cube.c \
		pyramid.c \
		disk.c \
		cylinder_bonus.c 

OBJS=${SRCS:.c=.o}
OBJSB=${SRCSB:.c=.o}

$(NAME):
	$(CC) $(FLAG) -I. -I./libft/. -c $(SRCS)
	$(MAKE) -C ./libft bonus
	$(MAKE) -C ./minilibx_mms
	cp $(LIBFT) _libft.a
	cp $(MINILIBX) _libmlx.dylib
	$(CC) $(FLAG) -I. -I./libft/. _libft.a _libmlx.dylib $(OBJS) main.c  -o $(NAME)

all: $(NAME)
bonus:
	$(CC) $(FLAG) -I. -I./libft/. -c $(SRCSB)
	$(MAKE) -C ./libft bonus
	$(MAKE) -C ./minilibx_mms
	cp $(LIBFT) _libft.a
	cp $(MINILIBX) _libmlx.dylib
	$(CC) $(FLAG) -I. -I./libft/. _libft.a _libmlx.dylib $(OBJSB) main.c  -o $(NAME)
clean:
	$(MAKE) -C ./libft clean
	rm -f $(OBJS)
	rm -f $(OBJSB)
	rm -f $(MINILIB)
fclean:
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./minilibx_mms clean
	rm -f _libft.a
	rm -f _libmlx.dylib
	rm -f $(OBJS)
	rm -f $(OBJSB)
	rm -f $(NAME)
	rm -f $(MINILIB)
re: fclean all
.PHONY: all clean fclean re bonus