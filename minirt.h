/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 00:17:10 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/16 21:54:53 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <limits.h>
# include <stdlib.h>
# include "ray.h"
# include "vector3.h"
# include "mlx.h"
# include "libft/libft.h"
# include "hittable.h"
# include "material.h"

# define PI 3.1415926535898

void ft_srand(unsigned int seed);
int ft_rand();
double random_double();
double random_range(double min, double max);
double dtor(double d);
double clamp(double x, double min, double max);

#endif