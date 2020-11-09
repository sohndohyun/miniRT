/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 02:04:30 by dsohn             #+#    #+#             */
/*   Updated: 2020/11/09 02:05:16 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

void	hittable_free(t_hittable *hittable)
{
	free(hittable->object);
	free(hittable);	
}
