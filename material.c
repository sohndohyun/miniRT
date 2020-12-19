/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:27:26 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 17:01:28 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"

t_vector3		material_emitted(void *obj, double u, double v, t_vector3 p)
{
	t_material *mat;

	mat = obj;
	p.x = u + v;
	return (vector3_init(0, 0, 0));
}
