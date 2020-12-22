/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 18:53:53 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/22 19:01:22 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISK_H
# define DISK_H

# include "hittable.h"
# include "material.h"

typedef struct	s_disk
{
	t_vector3	orig;
	t_vector3	face;
	double		radius;
	t_material	*mat;
}				t_disk;

t_result		disk_hit(void *obj, t_ray r, double t_min, double t_max);
t_hittable		*disk_alloc(t_vector3 orig,
	t_vector3 face, double radius, t_material *mat);
void			disk_free(void *disk);

#endif
