/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/14 16:01:04 by mraasvel      #+#    #+#                 */
/*   Updated: 2022/02/01 16:52:07 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_thread(void *arg)
{
	t_philo	*p;

	p = arg;
	while (!p->program->philo_dead)
	{
		if (p->status == inactive)
			break ;
		pthread_mutex_lock(&p->lock);
		if (time_difference(p->time_eaten) >= p->program->input.time_to_die)
			message(p, MSG_DEAD);
		pthread_mutex_unlock(&p->lock);
		usleep(1000);
	}
	return (NULL);
}
