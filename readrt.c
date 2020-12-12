/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readrt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:58:17 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/13 03:01:49 by dsohn            ###   ########.fr       */
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

#define READ_MAX 2048

static void readline(t_scene *scene, char **line)
{
	int i;

	i = ft_strlen(line[0]);
	if (ft_strncmp(line[0], "R", i) == 0)
		

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
	char **temp;

	if ((fd = open(file, O_RDONLY)) <= 0)
		return (0);
	read(fd, buf, READ_MAX);
	lines = ft_split(buf, '\n');
	if (lines == NULL)
		return (0);
	temp = lines;
	while (*temp)
	{
		readline(scene, ft_split(*temp, ' '));
		free(*temp++);
	}
	free(lines);
	close(fd);
	return (1);
}
