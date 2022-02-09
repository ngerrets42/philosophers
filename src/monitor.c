/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:56:39 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/09 14:37:47 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	monitor_thread_init(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, monitor_thread, philo) != 0)
	{
		philo->program->philo_dead = true;
		return (ERROR);
	}
	return (SUCCES);
}

void	*monitor_thread(void *arg)
{
	t_philo	*p;

	p = arg;
	while (true)
	{
		if (philo_check_death(p) > 0)
			break ;
		pthread_mutex_lock(&p->lock);
		if (time_diff(p->time_eaten) >= p->program->input.time_to_die)
			message(p, MSG_DEAD);
		pthread_mutex_unlock(&p->lock);
		usleep(1000);
	}
	return (NULL);
}
