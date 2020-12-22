/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:10:01 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/21 13:11:15 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void			scene_render(t_mlx *mlx)
{
	mlx->scene->cam = ft_lstat(mlx->scene->camera_lst, mlx->scene->camera_no);
	scene_fillimage(mlx, 1, 0);
}
