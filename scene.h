/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:15:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/13 02:02:19 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "libft/libft.h"
# include "hittable.h"
 
typedef t_list		*t_scene;

t_result scene_hit(t_scene *scene, t_ray r, double t_min, double t_max);
void scene_add(t_scene *scene, t_hittable *object);
void scene_free(t_scene *scene);

#endif
