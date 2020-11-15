/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:20:00 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/16 00:51:31 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

typedef struct	s_vector3 {
	double x;
	double y;
	double z;
}				t_vector3;

t_vector3		vector3_init(double x, double y, double z);
t_vector3		vector3_not(t_vector3 v);
t_vector3		vector3_add(t_vector3 v1, t_vector3 v2);
t_vector3		vector3_mult(t_vector3 v, double d);
t_vector3		vector3_div(t_vector3 v, double d);
double			vector3_length(t_vector3 v);
double			vector3_length_squared(t_vector3 v);
double			vector3_dot(t_vector3 v1, t_vector3 v2);
t_vector3		vector3_cross(t_vector3 v1, t_vector3 v2);
t_vector3		vector3_norm(t_vector3 v);
t_vector3		vector3_sbtr(t_vector3 v, t_vector3 v2);
t_vector3		vector3_random();
t_vector3		vector3_random_range(double min, double max);
t_vector3		vector3_random_unit_sphere();

#endif