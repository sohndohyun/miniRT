/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readrt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 00:23:48 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/24 01:25:36 by dsohn            ###   ########.fr       */
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
#include "cylinder_bonus.h"
#include "rainbow.h"
#include "cube.h"
#include "pyramid.h"
#include "disk.h"
#include "cone.h"

#define READ_MAX 2048

static void			exit_program(void)
{
	write(1, "Error\n", 6);
	exit(0);
}

static t_material	*pmat(char **line, int j)
{
	int i;

	i = ft_strlen(line[0]);
	if (ft_strncmp(line[0], "one", i) == 0 && j > 1)
		return (lambertian_alloc(solid_color_alloc(atocolor(line[1]))));
	else if (ft_strncmp(line[0], "checker", i) == 0 && j > 3)
		return (lambertian_alloc(checker_alloc(
			atocolor(line[1]), atocolor(line[2]), ft_atod(line[3]))));
	else if (ft_strncmp(line[0], "metal", i) == 0 && j > 2)
		return (metal_alloc(atocolor(line[1]), ft_atod(line[2])));
	else if (ft_strncmp(line[0], "refract", i) == 0)
		return (dielectric_alloc(ft_atod(line[1])));
	else if (ft_strncmp(line[0], "rainbow", i) == 0 && j > 0)
		return (lambertian_alloc(rainbow_alloc()));
	exit_program();
	return (NULL);
}

static void			readline2(
	t_scene *scene, char **line, int linelen, int split_no)
{
	if (ft_strncmp(line[0], "sq", linelen) == 0 && split_no > 4)
		scene_add(scene, square_alloc(atov(line[1]), atov(line[2]),
			ft_atod(line[3]), pmat(line + 4, split_no - 4)));
	else if (ft_strncmp(line[0], "cy", linelen) == 0 && split_no > 5)
		scene_add(scene, cylinder_bonus_alloc(ray_init(atov(line[1]),
			atov(line[2])), ft_atod(line[3]), ft_atod(line[4]),
			pmat(line + 5, split_no - 5)));
	else if (ft_strncmp(line[0], "tr", linelen) == 0 && split_no > 4)
		scene_add(scene, triangle_alloc(atov(line[1]), atov(line[2]),
			atov(line[3]), pmat(line + 4, split_no - 4)));
	else if (ft_strncmp(line[0], "cb", linelen) == 0 && split_no > 3)
		scene_add(scene, cube_alloc(atov(line[1]), ft_atod(line[2]),
			pmat(line + 3, split_no - 3)));
	else if (ft_strncmp(line[0], "py", linelen) == 0 && split_no > 4)
		scene_add(scene, pyramid_alloc(atov(line[1]), ft_atod(line[2]),
			ft_atod(line[3]), pmat(line + 4, split_no - 4)));
	else if (ft_strncmp(line[0], "dk", linelen) == 0 && split_no > 4)
		scene_add(scene, disk_alloc(atov(line[1]), atov(line[2]),
			ft_atod(line[3]), pmat(line + 4, split_no - 4)));
	else if (ft_strncmp(line[0], "co", linelen) == 0 && split_no > 5)
		scene_add(scene, cone_alloc(ray_init(atov(line[1]),
			atov(line[2])), ft_atod(line[3]), ft_atod(line[4]),
			pmat(line + 5, split_no - 5)));
	else
		exit_program();
}

static void			readline(t_scene *scene, char **line)
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
			dulight_alloc(solid_color_alloc(atocolor(line[3])))));
	else if (ft_strncmp(line[0], "sp", i) == 0 && j > 3)
		scene_add(scene, sphere_alloc(atov(line[1]), ft_atod(line[2]),
			pmat(line + 3, j - 3)));
	else if (ft_strncmp(line[0], "pl", i) == 0 && j > 3)
		scene_add(scene, plane_alloc(atov(line[1]), atov(line[2]),
			pmat(line + 3, j - 3)));
	else
		readline2(scene, line, i, j);
}

int					readrt(t_scene *scene, char *file)
{
	int		i[3];
	char	buf[READ_MAX];
	char	**lines;
	char	**temp;

	if ((i[0] = open(file, O_RDONLY)) <= 0)
		return (0);
	read(i[0], buf, READ_MAX);
	lines = ft_split(buf, '\n');
	i[1] = 0;
	while (lines[i[1]])
	{
		temp = ft_split(lines[i[1]], ' ');
		readline(scene, temp);
		i[2] = 0;
		while (temp[i[2]])
			free(temp[i[2]++]);
		free(temp);
		free(lines[i[1]++]);
	}
	free(lines);
	close(i[0]);
	return (1);
}
