/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 02:00:31 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/26 02:22:31 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUMPMAP_H
# define BUMPMAP_H

# include "material.h"
# include "rimage.h"

typedef struct		s_bumpmap
{
	t_material		*mat;
	t_rimage		image;
}					t_bumpmap;

t_ray				bumpmap_scatter(void *obj, t_ray rin,
	t_result *result, t_vector3 *color);
t_material			*bumpmap_alloc(char *filename,
	t_vector3 color, void *mlx);
void				bumpmap_free(void *obj);

#endif
