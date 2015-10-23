/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeier <nmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 14:36:26 by nmeier            #+#    #+#             */
/*   Updated: 2015/02/03 14:36:37 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_realloc.h"

void		*ft_realloc(void *ptr, size_t basesize, size_t newsize)
{
	char		*newdata;
	char		*olddata;
	size_t		i;

	if (newsize == basesize)
		return (ptr);
	olddata = ptr;
	newdata = (char*)malloc(sizeof(char) * newsize);
	i = 0;
	while (i < basesize)
	{
		newdata[i] = olddata[i];
		i++;
	}
	free(olddata);
	return (newdata);
}
