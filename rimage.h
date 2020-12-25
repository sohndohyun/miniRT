/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rimage.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 23:12:14 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/25 02:49:57 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RIMAGE_H
# define RIMAGE_H

# include "vector3.h"

typedef struct	s_rimage
{
	int			width;
	int			height;
	void		*img;
	char		*addr;
	int			bpp;
	int			line;
	int			endian;
}				t_rimage;

t_vector3		rimage_color(t_rimage *img, double u, double v);
void			rimage_init(t_rimage *img, void *mlx, char *file_name);

#endif
