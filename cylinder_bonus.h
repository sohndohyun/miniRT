/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:06:15 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/22 22:30:20 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_BONUS_H
# define CYLINDER_BONUS_H

# include "cylinder.h"
# include "disk.h"

t_result		cylinder_bonus_hit(void *obj, \
			t_ray r, double t_min, double t_max);
t_hittable		*cylinder_bonus_alloc(t_ray r, double radius, \
			double height, t_material *mat);
void			cylinder_bonus_free(void *cylinder);

#endif
