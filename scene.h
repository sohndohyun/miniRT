/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:15:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/19 18:24:29 by dsohn            ###   ########.fr       */
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
	t_list		*camera_lst;
	int			camera_no;
	t_camera	*cam;
	t_vector3	background;
}				t_scene;

typedef struct	s_mlx {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line;
	int			endian;
	t_scene		*scene;
}				t_mlx;

typedef struct	s_param
{
	t_mlx		*mlx;
	int			no;
	int			cnt;
}				t_param;

void			scene_init(t_scene *scene, \
			int sample_per_pixel, int max_depth, char *str);
t_result		scene_hit(t_scene *scene, t_ray r, double t_min, double t_max);
void			scene_add(t_scene *scene, t_hittable *object);
void			scene_free(t_scene *scene);
void			scene_fillimage(t_mlx *mlx, int th_count, int th_no);
void			scene_render(t_mlx *mlx);
void			scene_setsize(t_scene *scene, int width, int height);
void			scene_setamblight(t_scene *scene, \
			double range, t_vector3 color);
void			scene_setcamera(t_scene *scene, \
			t_vector3 pos, t_vector3 face, double fov);
void			export_bmp(char *filename, t_mlx *mlx);

#endif
