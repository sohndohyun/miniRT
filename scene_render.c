/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:10:01 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/21 01:50:07 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include <unistd.h>
#include <pthread.h>

#define THREAD_MAX 12

typedef struct	s_param
{
	t_scene	*scene;
	t_image	*image;
	int		no;
	int		cnt;
}				t_param;

static void *my_thread_main(void *param)
{
	t_param *p;

	p = (t_param*)param;
	scene_fillimage(p->scene, p->image, p->cnt, p->no);
	return (NULL);
}

void scene_render(t_scene *scene, t_image *img)
{
	int i;
	t_param params[THREAD_MAX];
	pthread_t p_thread[THREAD_MAX];

	i = 0;
	while (i < THREAD_MAX)
	{
		params[i].no = i;
		params[i].cnt = THREAD_MAX;
		params[i].image = img;
		params[i].scene = scene;
		if (pthread_create(&p_thread[i], NULL, my_thread_main, (void*)&params[i]) < 0)
		{
			write(1, "thread create error \n", 21);
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < THREAD_MAX)
	{
		pthread_join(p_thread[i++], NULL);
	}
}