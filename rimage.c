/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rimage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 23:12:17 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/26 00:31:45 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rimage.h"
#include "minirt.h"
#include <unistd.h>

t_vector3		rimage_color(t_rimage *img, double u, double v)
{
	int				i;
	int				j;
	unsigned int	color;
	t_vector3		rst;

	i = img->width * u;
	j = img->height * (1.0 - v);
	color = *((unsigned int*)(img->addr + (img->height - j - 1) *
		img->line + i * img->bpp / 8));
	rst.z = (double)(color & 0xff) / 255.0;
	color >>= 8;
	rst.y = (double)(color & 0xff) / 255.0;
	color >>= 8;
	rst.x = (double)(color & 0xff) / 255.0;
	return (rst);
}

void			rimage_init(t_rimage *img, void *mlx, char *file_name)
{
	img->img = mlx_xpm_file_to_image(mlx, file_name,
		&img->width, &img->height);
	if (img->img == NULL)
	{
		write(1, file_name, ft_strlen(file_name));
		write(1, " Error\n", 6);
		exit(0);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
		&img->line, &img->endian);
}
