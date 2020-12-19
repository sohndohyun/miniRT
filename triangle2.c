/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 20:03:05 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 20:22:31 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangle.h"

void			triangle_get_uv(double *u, double *v, double denom)
{
	*u = *u / denom;
	*v = *v / denom;
}

int				pot(t_vector3 face, t_vector3 edge, t_vector3 vp, double *uv)
{
	if ((*uv = vector3_dot(face, vector3_cross(edge, vp))) < 0)
		return (0);
	return (1);
}
