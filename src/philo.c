/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 08:39:58 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/13 11:14:20 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

void	_sleep_until(t_philo *me, unsigned long time_stamp)
{
	unsigned long	current_time;
	unsigned long	sleepy_time;

	while (1)
	{
		current_time = time_get_micro();
		if (current_time > time_stamp)
			break ;
		sleepy_time = time_stamp - current_time;
		if (sleepy_time < 5000)
			usleep(sleepy_time);
		else
			usleep(sleepy_time);
	}
}

void	_go_sleep(t_philo *me)
{
	//RELEASE FORKS
	pthread_mutex_unlock(&(me->fork_mutex));
	pthread_mutex_unlock(&(me->neighbour->fork_mutex));
	me->status = S_SLEEPING;
	me->time_of_death = me->time_of_death + me->program->time_to_die;
	message_status(me);
	me->time_of_action += me->program->time_to_sleep;
	_sleep_until(me, me->time_of_action);
}

void	_grab_forks(t_philo *me)
{
	unsigned long	fork_time;

	if (me->neighbour == NULL)
		while (1)
		;
	fork_time = time_get_micro();
	//GRAB MY FORK (RIGHT FORK)
	pthread_mutex_lock(&(me->fork_mutex));
	
	//GRAB NEIGHTBOURS FORK (LEFT FORK)
	pthread_mutex_lock(&(me->neighbour->fork_mutex));
	me->time_of_action += time_get_micro() - fork_time;
}

void	_go_eat(t_philo *me)
{
	//FIRST PICK UP FORK
	_grab_forks(me);
	me->status = S_EATING;
	message_status(me);
	me->time_of_action += me->program->time_to_eat;
	_sleep_until(me, me->time_of_action);
}

void	_go_think(t_philo *me)
{
	me->status = S_THINKING;
	message_status(me);
}

void	*philo_thread(void *arg)
{
	t_philo	*me;
	
	me = (t_philo *)arg;
	while (1)
	{
		if (me->status == S_DEAD)
			return (NULL);
		else if (me->status == S_EATING)
			_go_sleep(me);
		else if (me->status == S_SLEEPING)
			_go_think(me);
		else if (me->status == S_THINKING)
			_go_eat(me);
		else
			return (NULL);
	}
	return (NULL);
}
