/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeier <nmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 14:10:46 by nmeier            #+#    #+#             */
/*   Updated: 2015/02/03 14:12:34 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

typedef struct	s_array
{
	unsigned int	size;
	unsigned int	cap;
	void			**data;
}				t_array;

t_array			*array_create(unsigned int cap);
void			array_destroy(t_array *array);
void			array_append(t_array *array, void *value);
void			array_merge(t_array *dest, t_array *src);
void			*array_get(t_array *array, unsigned int index);
void			array_set(t_array *array, unsigned int index, void *value);
void			array_swap(t_array *array, unsigned int i1, unsigned int i2);
void			*array_remove(t_array *array, unsigned int index);
t_array*		array_dup(t_array* array);

#endif
