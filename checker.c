/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 21:07:44 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/23 21:30:42 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_vector3		checker_value(void *obj, double u, double v, t_vector3 point)
{
	double sines;
	t_checker *ch;

	ch = (t_checker*)obj;
	sines = sin(10 * point.x) * sin(10 * point.y) * sin(10 * point.z);
	if (sines < 0)
		return (ch->odd->value(ch->odd->obj, u, v, point));
	else 
		return (ch->even->value(ch->even->obj, u, v, point));
}

void			checker_free(void *obj)
{
	t_checker *ch;

	ch = (t_checker*)obj;
	ch->even->free(ch->even->obj);
	free(ch->even);
	ch->odd->free(ch->odd->obj);
	free(ch->odd);
	free(ch);
}

t_texture		*checker_alloc(t_vector3 c1, t_vector3 c2)
{
	t_texture *te;
	t_checker *ch;

	ch = (t_checker*)malloc(sizeof(t_checker));
	ch->odd = solid_color_alloc(c1);
	ch->even = solid_color_alloc(c2);
	te = (t_texture*)malloc(sizeof(t_texture));
	te->obj = ch;
	te->value = checker_value;
	te->free = checker_free;
	return (te);
}
