/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:56:39 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/15 13:31:22 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	Creates monitor thread.
*/
int	monitor_thread_init(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, monitor_thread, philo) != 0)
	{
		philo->program->philo_dead = true;
		return (ERROR);
	}
	return (SUCCES);
}

/*
**	Simple check to see if given philosopher has eaten enough.
*/
static bool	_check_eaten_enough(t_philo *p)
{
	if (p->program->input.amount_to_eat >= p->amount_eaten)
		return (true);
	return (false);
}

/*
**	Main thread of the monitor.
**	Every philosopher has one to continuously check if they are either dead
**	or has eaten enough.
**	This mainly makes it easy to check for death while the philosopher is waiting
**	for a mutex or sleeping.
*/
void	*monitor_thread(void *arg)
{
	t_philo	*p;

	p = arg;
	while (true)
	{
		if (philo_check_death(p) > 0 || _check_eaten_enough(p))
			break ;
		pthread_mutex_lock(&p->lock);
		if (time_diff(p->time_eaten) > p->program->input.time_to_die)
			message(p, MSG_DEAD);
		pthread_mutex_unlock(&p->lock);
		usleep(MONITOR_SLEEP_CONSTANT);
	}
	return (NULL);
}
