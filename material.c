/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:27:26 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/21 18:16:58 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"

t_vector3		material_emitted(void *obj, t_result *result)
{
	obj = result;
	return (vector3_init(0, 0, 0));
}
