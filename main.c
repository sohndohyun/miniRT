/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:46:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 16:59:22 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readrt.h"

#define SAMPLE_PER_PIXEL 2048
#define MAX_DEPTH 32

int		key_hook(int key, void *param)
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
		scene_render(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}
	return (0);
}

int		exit_program(void)
{
	exit(0);
	return (0);
}

void	clampscreensize(t_mlx *mlx)
{
	int w;
	int h;

	mlx_get_screen_size(mlx->mlx, &w, &h);
	mlx->scene->screen_width = mlx->scene->screen_width > w ?
		w : mlx->scene->screen_width;
	mlx->scene->screen_height = mlx->scene->screen_height > h ?
		h : mlx->scene->screen_height;
}

int		main(int argc, char **argv)
{
	t_mlx	mlx;
	t_scene	scene;

	if (argc == 1 || argc > 3)
		return (0);
	mlx.scene = &scene;
	scene_init(&scene, SAMPLE_PER_PIXEL, MAX_DEPTH, argv[1]);
	mlx.mlx = mlx_init();
	clampscreensize(&mlx);
	mlx.win = mlx_new_window(
		mlx.mlx, scene.screen_width, scene.screen_height, "miniRT");
	mlx.img = mlx_new_image(mlx.mlx, scene.screen_width, scene.screen_height);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line, &mlx.endian);
	scene_render(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
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
