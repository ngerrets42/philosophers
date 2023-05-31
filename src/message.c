/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   message.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:57:30 by ngerrets      #+#    #+#                 */
/*   Updated: 2023/05/31 17:06:16 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

/*
**	Function that handles sending messages one by one using a mutex.
**	It is also practically responsible for telling the program to stop when a
**	philosopher dies.
*/
void	message(t_philo *philo, t_msg msg)
{
	static const char	*str[] = {
	[MSG_FORK] = "has taken a fork",
	[MSG_EAT] = "is eating",
	[MSG_SLEEP] = "is sleeping",
	[MSG_THINK] = "is thinking",
	[MSG_DEAD] = "died"
	};

	pthread_mutex_lock(&philo->program->lock);
	if (!philo->program->philo_dead)
	{
		printf("%ld %d %s\n",
			time_diff(philo->program->start_time), philo->index + 1, str[msg]);
		if (msg == MSG_DEAD)
			philo->program->philo_dead = true;
	}
	pthread_mutex_unlock(&philo->program->lock);
}
