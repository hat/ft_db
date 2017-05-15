/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrameau <jrameau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 06:01:33 by jrameau           #+#    #+#             */
/*   Updated: 2017/05/05 23:21:53 by jrameau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtolower(char **str)
{
	int		i;
	char	*tmp;

	tmp = *str;
	i = -1;
	while (tmp[++i])
	{
		if (ft_isupper(tmp[i]))
			tmp[i] = tmp[i] + 32;
	}
}
