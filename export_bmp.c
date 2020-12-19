/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 20:03:44 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 16:30:05 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <fcntl.h>
#include <unistd.h>

#define HEADER_SIZE 122

void	fill_bmp(char **data, t_mlx *mlx)
{
	int i;
	int j;
	int x;
	int y;

	i = HEADER_SIZE;
	y = mlx->scene->screen_height;
	while (y--)
	{
		x = -1;
		while (++x < mlx->scene->screen_width)
		{
			j = (x * (mlx->bpp / 8)) + (y * mlx->line);
			*(*data + i++) = *(mlx->addr + j++);
			*(*data + i++) = *(mlx->addr + j++);
			*(*data + i++) = *(mlx->addr + j);
		}
	}
}

/*
** Initialize the header of bmp (char *data)
**
** HEADER
** Position | Hex	| Description
** 00		| 00	| TYPE OF BMP FILE
** 02		| 02	| TOTAL SIZE OF FILE
** 06-08	| 06-08	| RESERVED TO SIGN
** 10		| 0A	| HEADER SIZE
** =============================================================================
** HEADER INFOS
** Position | Hex	| Description
** 14		| 0E	| HEADER INFOS SIZE
** 18		| 12	| WIDTH OF IMG (PX)
** 22		| 16	| HEIGHT OF IMG (PX)
** 26		| 1A	| NUMBER OF PLANS
** 28		| 1C	| BITS PER PIXELS (1 - 4 - 8 - 24)
** 30		| 1E	| COMPRESSION TYPE
** 34		| 22	| SIZE OF IMG
** 38		| 26	| RES X PX PER METER
** 42		| 2A	| RES Y PX PER METER
** 46		| 2E	| NB OF USED COLOR (0 = MAX)
** 50		| 32	| NB OF INDEX OF COLOR (0 = ALL)
*/

void	header_bmp(char **data, t_mlx *mlx)
{
	unsigned int size;

	size = mlx->scene->screen_width * mlx->scene->screen_height * 3;
	*(unsigned short *)*data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*data + 2) = (size + HEADER_SIZE);
	*(unsigned int *)(*data + 6) = 0u;
	*(unsigned char *)(*data + 10) = HEADER_SIZE;
	*(unsigned int *)(*data + 14) = HEADER_SIZE - 14;
	*(unsigned int *)(*data + 18) = mlx->scene->screen_width;
	*(unsigned int *)(*data + 22) = mlx->scene->screen_height;
	*(unsigned short *)(*data + 26) = 1;
	*(unsigned short *)(*data + 28) = 24;
	*(unsigned int *)(*data + 30) = 0;
	*(unsigned int *)(*data + 34) = (unsigned int)size;
	*(unsigned int *)(*data + 38) = 3780;
	*(unsigned int *)(*data + 42) = 3780;
	*(int *)(*data + 46) = 0;
	*(int *)(*data + 50) = 0;
}

/*
** Create bmp (char *data), put header and fill it, then put result into
** filename (*.bmp).
*/

void	export_bmp(char *filename, t_mlx *mlx)
{
	int				fd;
	unsigned int	size;
	unsigned int	i;
	char			*data;

	size = mlx->scene->screen_height * mlx->scene->screen_width * 3;
	data = malloc((size + HEADER_SIZE));
	i = 0;
	while (i < size + HEADER_SIZE)
		data[i++] = 0;
	header_bmp(&data, mlx);
	fill_bmp(&data, mlx);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	write(fd, data, (size + HEADER_SIZE));
	close(fd);
}
