/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 14:28:07 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/25 21:11:33 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKYBOX_H
# define SKYBOX_H

# include "rimage.h"
# include "ray.h"

typedef struct	s_skybox
{
	t_rimage	img[6];
}				t_skybox;

void			skybox_init(t_skybox *box, char **line, void *mlx);
t_vector3		skybox_background(t_skybox *box, t_ray r);

#endif
