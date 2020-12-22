/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:33:22 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/21 18:22:52 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAINBOW_H
# define RAINBOW_H

# include "solid_color.h"

t_vector3		rainbow_value(void *obj, t_result *result);
void			rainbow_free(void *obj);
t_texture		*rainbow_alloc(void);

#endif
