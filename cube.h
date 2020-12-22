/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 22:22:15 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/22 16:32:56 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "square.h"

t_result		cube_hit(void *obj, t_ray r, double t_min, double t_max);
t_hittable		*cube_alloc(t_vector3 center, double size, t_material *mat);
void			cube_free(void *cube);

#endif
