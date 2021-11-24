/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/24 10:51:11 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/24 16:37:17 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mlock(pthread_mutex_t *mutex)
{
	//printf("==locking %p\n", mutex);
	pthread_mutex_lock(mutex);
	//printf("===locked %p\n", mutex);
	return (1);
}

int	munlock(pthread_mutex_t *mutex)
{
	//printf("=unlocked %p\n", mutex);
	return (pthread_mutex_unlock(mutex));
}
