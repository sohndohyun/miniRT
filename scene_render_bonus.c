/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_render_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 00:32:00 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/21 14:28:04 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <unistd.h>
#include <pthread.h>

#define THREAD_MAX 10

static void		*my_thread_main(void *param)
{
	t_param *p;

	p = (t_param*)param;
	scene_fillimage(p->mlx, p->cnt, p->no);
	return (NULL);
}

void			scene_render(t_mlx *mlx)
{
	int			i;
	t_param		params[THREAD_MAX];
	pthread_t	p_thread[THREAD_MAX];

	i = 0;
	mlx->scene->cam = ft_lstat(mlx->scene->camera_lst, mlx->scene->camera_no);
	while (i < THREAD_MAX)
	{
		params[i].no = i;
		params[i].cnt = THREAD_MAX;
		params[i].mlx = mlx;
		if (pthread_create(&p_thread[i], NULL,
			my_thread_main, (void*)&params[i]) < 0)
		{
			write(1, "thread create error \n", 21);
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < THREAD_MAX)
		pthread_join(p_thread[i++], NULL);
}
