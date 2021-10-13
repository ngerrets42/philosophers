/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 08:39:58 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/13 12:48:46 by ngerrets      ########   odam.nl         */
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
		if (sleepy_time < 10000)
		{
			usleep(sleepy_time);
		}
		else
			usleep(10000);
	}
}

void	_go_sleep(t_philo *me)
{
	//RELEASE FORKS
	pthread_mutex_unlock(&(me->fork_mutex));
	me->fork_has = 1;
	pthread_mutex_unlock(&(me->neighbour->fork_mutex));
	me->neighbour->fork_has = 1;
	me->status = S_SLEEPING;
	//me->time_of_death = me->time_of_death + me->program->time_to_die;
	message_status(me);
	me->time_of_action += me->program->time_to_sleep;
	_sleep_until(me, me->time_of_action);
}

void	_grab_forks(t_philo *me)
{
	unsigned long	fork_time;

	//wait_for_turn(me);
	fork_time = time_get_micro();
	if (me->neighbour == NULL)
		while (1)
		;
	while (me->neighbour->fork_has == 0 || me->fork_has == 0)
		;
	pthread_mutex_lock(&(me->fork_mutex));
	me->fork_has = 0;
	pthread_mutex_lock(&(me->neighbour->fork_mutex));
	me->neighbour->fork_has = 0;
	fork_time = time_get_micro() - fork_time;
	me->time_of_action += (unsigned long)(fork_time / me->program->time_to_eat)
		* me->program->time_to_eat;
}

void	_go_eat(t_philo *me)
{
	//FIRST PICK UP FORK
	_grab_forks(me);
	me->time_of_action += me->program->time_to_eat;
	if (me->time_of_action <= me->time_of_death)
		me->time_of_death += me->program->time_to_die;
	me->status = S_EATING;
	message_status(me);
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
	while (me->neighbour == NULL)
		;
	if (me->index == 0)
		me->status = S_THINKING;
	while (me->status == S_NONE)
	{
		if (me->neighbour->status != S_NONE)
			me->status = S_THINKING;
		usleep(1);
	}
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
	printf("PHILO THREAD %d RETURNED\n", me->index);
	return (NULL);
}
