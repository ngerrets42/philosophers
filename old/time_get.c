/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_get.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:26:25 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/17 11:37:59 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "time_get.h"

unsigned long	time_get_msec(void)
{
	struct timeval	val;
	unsigned long	time;

	gettimeofday(&val, NULL);
	time = val.tv_sec * 1000000 + val.tv_usec;
	time *= 0.001;
	return (time);
}

unsigned long	time_get_usec(void)
{
	struct timeval	val;
	unsigned long	time;

	gettimeofday(&val, NULL);
	time = val.tv_sec * 1000000 + val.tv_usec;
	return (time);
}

unsigned long	time_start_get(void)
{
	static unsigned long	start_time = 0;

	if (start_time == 0)
		start_time = time_get_usec();
	return (start_time);
}
