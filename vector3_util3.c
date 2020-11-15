/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_util3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 02:15:06 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/16 02:17:20 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vector3		vector3_random_hemisphere(t_vector3 norm)
{
	t_vector3 temp;

	temp = vector3_random_unit_sphere();
	if (vector3_dot(temp, norm) > 0.0)
		return (temp);
	return (vector3_not(temp));
}
