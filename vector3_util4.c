/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_util4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 02:15:06 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/15 23:26:50 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include "libft/libft.h"
#include <math.h>
#include <stdlib.h>

double		vector3_angle(t_vector3 a, t_vector3 b)
{
	return (acos(vector3_dot(a, b) / (vector3_length(a) * vector3_length(b))));
}

t_vector3	vector3_rotate_x(t_vector3 v, double angle)
{
	double y;
	double z;

	if (angle < 0)
		angle += 360.0;
	else if (angle > 360.0)
		angle -= 360.0;
	y = v.y * cos(angle) - v.z * sin(angle);
	z = v.y * sin(angle) + v.z * cos(angle);
	v.y = y;
	v.z = z;
	return (v);
}

t_vector3	vector3_rotate_z(t_vector3 v, double angle)
{
	double x;
	double y;

	if (angle < 0)
		angle += 360.0;
	else if (angle > 360.0)
		angle -= 360.0;
	x = v.x * cos(angle) - v.y * sin(angle);
	y = v.x * sin(angle) + v.y * cos(angle);
	v.x = x;
	v.y = y;
	return (v);
}

t_vector3	atov(const char *str)
{
	t_vector3 temp;
	char **s;
	int i;

	i = 0;
	s = ft_split(str, ',');
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