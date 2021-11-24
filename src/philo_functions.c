/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/24 10:51:11 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/24 12:44:52 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mlock(pthread_mutex_t *mutex)
{
	return (pthread_mutex_lock(mutex));
}

int	munlock(pthread_mutex_t *mutex)
{
	return (pthread_mutex_unlock(mutex));
}
