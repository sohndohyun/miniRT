/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:59:27 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/23 21:10:47 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "solid_color.h"

typedef struct	s_checker
{
	t_texture	*odd;
	t_texture	*even;
}				t_checker;

t_vector3		checker_value(void *obj, double u, double v, t_vector3 point);
void			checker_free(void *obj);
t_texture		*checker_alloc(t_vector3 c1, t_vector3 c2);

#endif
