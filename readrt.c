/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readrt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:58:17 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/26 00:10:29 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readrt.h"
#include <fcntl.h>
#include <unistd.h>
#include "minirt.h"
#include "sphere.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "solid_color.h"
#include "checker.h"
#include "dulight.h"
#include "plane.h"
#include "triangle.h"
#include "square.h"
#include "cylinder.h"

#define READ_MAX 4096

void		error_end(void)
{
	write(1, "Error\n", 6);
	exit(0);
}

static void	add_object_to_scene(
	t_scene *scene, char **line, int linelen, int split_no)
{
	if (ft_strncmp(line[0], "sp", linelen) == 0 && split_no > 3)
		scene_add(scene, sphere_alloc(atov(line[1]), ft_atod(line[2]),
			lambertian_alloc(solid_color_alloc(atocolor(line[3])))));
	else if (ft_strncmp(line[0], "pl", linelen) == 0 && split_no > 3)
		scene_add(scene, plane_alloc(atov(line[1]), atov(line[2]),
			lambertian_alloc(solid_color_alloc(atocolor(line[3])))));
	else if (ft_strncmp(line[0], "sq", linelen) == 0 && split_no > 4)
		scene_add(scene, square_alloc(
			atov(line[1]), atov(line[2]), ft_atod(line[3]),
			lambertian_alloc(solid_color_alloc(atocolor(line[4])))));
	else if (ft_strncmp(line[0], "cy", linelen) == 0 && split_no > 5)
		scene_add(scene, cylinder_alloc(ray_init(atov(line[1]), atov(line[2])),
			ft_atod(line[3]), ft_atod(line[4]),
			lambertian_alloc(solid_color_alloc(atocolor(line[5])))));
	else if (ft_strncmp(line[0], "tr", linelen) == 0 && split_no > 4)
		scene_add(scene, triangle_alloc(
			atov(line[1]), atov(line[2]), atov(line[3]),
			lambertian_alloc(solid_color_alloc(atocolor(line[4])))));
	else
		error_end();
}

static void	readline(t_scene *scene, char **line)
{
	int i;
	int j;

	i = ft_strlen(line[0]);
	j = ft_split_cnt(line);
	if (ft_strncmp(line[0], "R", i) == 0 && j > 2)
		scene_setsize(scene, ft_atoi(line[1]), ft_atoi(line[2]));
	else if (ft_strncmp(line[0], "A", i) == 0 && j > 2)
		scene_setamblight(scene, ft_atod(line[1]), atocolor(line[2]));
	else if (ft_strncmp(line[0], "c", i) == 0 && j > 3)
		scene_setcamera(scene, atov(line[1]), atov(line[2]), ft_atod(line[3]));
	else if (ft_strncmp(line[0], "l", i) == 0 && j > 3)
		scene_add(scene, sphere_alloc(atov(line[1]), ft_atod(line[2]) * 3,
		dulight_alloc(solid_color_alloc(vector3_mult(atocolor(line[3]), 4)))));
	else
		add_object_to_scene(scene, line, i, j);
	i = 0;
	while (line[i])
		free(line[i++]);
	free(line);
}

int			readrt(t_scene *scene, char *file, void *mlx)
{
	int		fd;
	char	buf[READ_MAX];
	char	**lines;
	int		i;

	if (mlx == NULL)
		return (0);
	if ((fd = open(file, O_RDONLY)) <= 0)
		return (0);
	read(fd, buf, READ_MAX);
	lines = ft_split(buf, '\n');
	i = 0;
	while (lines[i])
	{
		readline(scene, ft_split(lines[i], ' '));
		free(lines[i++]);
	}
	free(lines);
	close(fd);
	return (1);
}
