/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:15:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/20 23:02:39 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"
# include "hittable.h"
# include "camera.h"

typedef struct	s_scene
{
	int			screen_width;
	int			screen_height;
	int			sample_per_pixel;
	int			max_depth;
	t_list		*hittable_lst;
	t_camera	cam;
}				t_scene;

typedef struct	s_image {
	void		*img;
	char		*addr;
	int			bpp;
	int			line;
	int			endian;
}				t_image;

t_result scene_hit(t_scene *scene, t_ray r, double t_min, double t_max);
void scene_add(t_scene *scene, t_hittable *object);
void scene_free(t_scene *scene);
void scene_fillimage(t_scene *scene, t_image *img, int th_count, int th_no);

#endif
