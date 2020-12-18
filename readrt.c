/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readrt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:58:17 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/15 23:31:38 by dsohn            ###   ########.fr       */
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
#include <stdio.h>

#define READ_MAX 2048

static void add_object_to_scene(t_scene *scene, char **line, int linelen)
{
	if (ft_strncmp(line[0], "l", linelen) == 0)
		scene_add(scene, sphere_alloc(atov(line[1]), ft_atod(line[2]) * 3, 
			dulight_alloc(solid_color_alloc(atocolor(line[3])))));
	else if (ft_strncmp(line[0], "sp", linelen) == 0)
		scene_add(scene, sphere_alloc(atov(line[1]), ft_atod(line[2]), 
			lambertian_alloc(solid_color_alloc(atocolor(line[3])))));
	else if (ft_strncmp(line[0], "pl", linelen) == 0)
		scene_add(scene, plane_alloc(atov(line[1]), atov(line[2]),
			lambertian_alloc(solid_color_alloc(atocolor(line[3])))));
	else if (ft_strncmp(line[0], "sq", linelen) == 0)
		scene_add(scene, square_alloc(atov(line[1]), atov(line[2]), ft_atod(line[3]), 
			lambertian_alloc(solid_color_alloc(atocolor(line[4])))));
	else if (ft_strncmp(line[0], "cy", linelen) == 0)
		scene_add(scene, cylinder_alloc(ray_init(atov(line[1]), atov(line[2])), 
			ft_atod(line[3]), ft_atod(line[4]),
			lambertian_alloc(solid_color_alloc(atocolor(line[5])))));
	else if (ft_strncmp(line[0], "tr", linelen) == 0)
		scene_add(scene, triangle_alloc(atov(line[1]), atov(line[2]), atov(line[3]),
			lambertian_alloc(solid_color_alloc(atocolor(line[4])))));
}

static void readline(t_scene *scene, char **line)
{
	int i;

	i = ft_strlen(line[0]);
	if (ft_strncmp(line[0], "R", i) == 0)
		scene_setsize(scene, ft_atoi(line[1]), ft_atoi(line[2]));
	else if (ft_strncmp(line[0], "A", i) == 0)
		scene_setamblight(scene, ft_atod(line[1]), atocolor(line[2]));
	else if (ft_strncmp(line[0], "c", i) == 0)
		scene_setcamera(scene, atov(line[1]), atov(line[2]), ft_atod(line[3]));
	else
		add_object_to_scene(scene, line, i);
	i = 0;
	while (line[i])
		free(line[i++]);
	free(line);
}

int	readrt(t_scene *scene, char *file)
{
	int fd;
	char buf[READ_MAX];
	char **lines;
	int i;

	if ((fd = open(file, O_RDONLY)) <= 0)
		return (0);
	read(fd, buf, READ_MAX);
	lines = ft_split(buf, '\n');
	i = 0;
	while (lines[i])
	{
		readline(scene, ft_split(lines[i], ' '));
		printf("read file line %d\n", i + 1);
		free(lines[i++]);
		printf("free file line %d\n", i);
	}
	free(lines);
	close(fd);
	return (1);
}
