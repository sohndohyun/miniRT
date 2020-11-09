/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:15:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/07 01:31:40 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "libft/libft.h"
# include "hittable.h"

typedef t_list		*t_scene;

void scene_render(t_scene *scene);
void scene_addobject(t_scene *scene, t_hittable *object);
void scene_free(t_scene *scene);

#endif
