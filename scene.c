/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:31:58 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/11 16:30:42 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void scene_render(t_scene *scene)
{
	t_scene it;
	t_hittable *obj;

	it = *scene;
	while (it != 0)
	{
		it->content;
		obj = it->content;
		
		it = it->next;
	}
}

void scene_addobject(t_scene *scene, t_hittable *object)
{
	ft_lstadd_back(scene, ft_lstnew(object));
}
  
void scene_free(t_scene *scene)
{
	ft_lstclear(scene, hittable_free);
}
