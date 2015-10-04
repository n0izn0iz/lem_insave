/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeier <nmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 14:34:23 by nmeier            #+#    #+#             */
/*   Updated: 2015/02/03 14:36:14 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REALLOC_H
# define FT_REALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

# include <stdlib.h>

void		*ft_realloc(void *ptr, size_t basesize, size_t newsize);

#ifdef __cplusplus
}
#endif

#endif
