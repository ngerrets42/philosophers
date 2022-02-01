/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   func.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 16:08:31 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/01/26 16:29:36 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "func.h"

void	*alloc_size(unsigned long size)
{
	void	*alloc;
	char	*p;

	alloc = malloc(size);
	if (alloc == NULL)
		return (NULL);
	p = (char *)alloc;
	while (size > 0)
	{
		*p = 0;
		size--;
		p++;
	}
	return (alloc);
}