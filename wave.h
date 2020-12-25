/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:30:13 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/24 17:23:00 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAVE_H
# define WAVE_H

# include "lambertian.h"

t_material		*wave_alloc(t_texture *albedo);
t_ray			wave_scatter(void *obj, t_ray rin,
	t_result *result, t_vector3 *color);

#endif
