/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_util4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 02:15:06 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/22 16:14:03 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include "libft/libft.h"
#include "minirt.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

double		vector3_angle(t_vector3 a, t_vector3 b)
{
	return (acos(vector3_dot(a, b) / (vector3_length(a) * vector3_length(b))));
}

t_vector3	vector3_aar(t_vector3 v, t_vector3 axis, double angle)
{
	double c;
	double s;

	s = sin(angle);
	c = cos(angle);
	return (vector3_add(vector3_add(vector3_mult(v, c),
		vector3_mult(vector3_cross(axis, v), s)),
		vector3_mult(axis, vector3_dot(axis, v) * (1.0 - c))));
}

t_vector3	atov(const char *str)
{
	t_vector3	temp;
	char		**s;
	int			i;

	i = 0;
	s = ft_split(str, ',');
	if (ft_split_cnt(s) < 3)
	{
		write(1, "Error\n", 6);
		exit(0);
	}
	temp = vector3_init(ft_atod(s[0]), ft_atod(s[1]), ft_atod(s[2]));
	while (s[i])
		free(s[i++]);
	free(s);
	return (temp);
}

t_vector3	atocolor(const char *str)
{
	return (vector3_div(atov(str), 255.0));
}
