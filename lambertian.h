/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:38:48 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 04:36:06 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAMBERTIAN_H
# define LAMBERTIAN_H

# include "texture.h"

typedef struct	s_lambertian
{
	t_texture	*albedo;
}				t_lambertian;

t_ray			lambertian_scatter(void *obj, t_ray rin, \
			t_result *result, t_vector3 *color);
t_material		*lambertian_alloc(t_texture *albedo);
void			lambertian_free(void *lambertian);

#endif
