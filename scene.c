/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:31:58 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/14 03:46:40 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_result scene_hit(t_scene *scene, t_ray r, double t_min, double t_max)
{
	t_list *it;
	t_hittable *obj;
	t_result result;
	t_result current;
	double closet;

	result.ret = 0;
	closet = t_max;
	it = (t_list*)*scene;
	while (it != NULL)
	{
		obj = it->content;
		current = obj->hit(obj->object, r, t_min, closet);
		if (current.ret == 1)
		{
			closet = current.t;
			result = current;
		}
		it = it->next;
	}
	return (result);
}

void scene_add(t_scene *scene, t_hittable *object)
{
	ft_lstadd_back(scene, ft_lstnew(object));
}
  
void scene_free(t_scene *scene)
{
	ft_lstclear(scene, hittable_free);
}
