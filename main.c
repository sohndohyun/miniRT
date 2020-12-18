/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:46:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/18 22:51:37 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readrt.h"
#include <stdio.h>

#define SAMPLE_PER_PIXEL 2048
#define MAX_DEPTH 32

void render_screen(t_mlx *mlx)
{
	scene_render(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int	key_hook(int key, void *param)
{
	t_mlx	*mlx;
	t_list	*lst;

	mlx = param;
	if (key == 53 && param)
		exit(0);
	else if (key == 48)
	{
		lst = mlx->scene->camera_lst;
		mlx->scene->camera_no = (mlx->scene->camera_no + 1) % ft_lstsize(lst);
		render_screen(mlx);
	}
	return (0);
}

int	exit_program(void)
{
	exit(0);
	return (0);
}

int main(int argc, char** argv)
{
	t_mlx mlx;
	t_scene scene;

	if (argc == 1 || argc > 3)
		return (0);
	mlx.scene = &scene;
	scene.hittable_lst = NULL;
	scene.sample_per_pixel = SAMPLE_PER_PIXEL;
	scene.max_depth = MAX_DEPTH;
	scene.camera_no = 0;
	readrt(&scene, argv[1]);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, scene.screen_width, scene.screen_height, "miniRT");
	mlx.img = mlx_new_image(mlx.mlx, scene.screen_width, scene.screen_height);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line, &mlx.endian);
	render_screen(&mlx);
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
		export_bmp("miniRT.bmp", &mlx);
	else
	{
		mlx_key_hook(mlx.win, key_hook, &mlx);
		mlx_hook(mlx.win, 17, 1L << 17, exit_program, NULL);
		mlx_loop(mlx.mlx);
	}
	scene_free(&scene);
	return (0);
}
