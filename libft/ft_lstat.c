/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsohn <dsohn@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 22:47:18 by dsohn             #+#    #+#             */
/*   Updated: 2020/12/18 23:05:07 by dsohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstat(t_list *lst, int at)
{
	int i;

	i = 0;
	while (i < at && lst)
	{
		i++;
		lst = lst->next;
	}
	if (lst)
		return (lst->content);
	else
		return (NULL);
}
