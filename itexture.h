/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itexture.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 02:25:36 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/26 00:52:33 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEXTURE_H
# define ITEXTURE_H

# include "texture.h"
# include "rimage.h"

typedef struct	s_itexture
{
	t_rimage	image;
}				t_itexture;

t_texture		*itexture_alloc(char *filename, void *mlx);
t_vector3		itexture_value(void *obj, t_result *result);
void			itexture_free(void *obj);

#endif
