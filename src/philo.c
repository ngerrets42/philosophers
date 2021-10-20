/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 08:39:58 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/20 15:53:56 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>

static void	sleep_for(unsigned long ms)
{
	long			time_diff;
	unsigned long	time_last;
	unsigned long	time_now;
	unsigned long	time_to_sleep;

	time_diff = 0;
	time_last = time_get_micro();
	while (1)
	{
		time_to_sleep = STANDARD_SLEEP_TIME - time_diff;
		if (ms < STANDARD_SLEEP_TIME)
			time_to_sleep = ms;
		usleep(time_to_sleep);
		if (ms < STANDARD_SLEEP_TIME)
			break ;
		time_now = time_get_micro();
		ms -= time_now - time_last;
		time_diff = time_now - time_last - time_to_sleep;
		time_last = time_now;
	}
}

static void	_go_sleep(t_philo *me)
{
	me->status = S_SLEEPING;
	message_status(me, MSG_SLEEPING);
	pthread_mutex_unlock(&(me->fork_mutex));
	pthread_mutex_unlock(&(me->neighbour->fork_mutex));
	sleep_for(me->program->time_to_sleep);
}

static void	_go_eat(t_philo *me)
{
	if (me->neighbour == NULL)
		while (1)
		;
	pthread_mutex_lock(&(me->fork_mutex));
	pthread_mutex_lock(&(me->neighbour->fork_mutex));
	me->time_of_death = time_get_micro() + me->program->time_to_die;
	me->status = S_EATING;
	message_status(me, MSG_EATING);
	sleep_for(me->program->time_to_eat);
	me->times_eaten++;
}

static void	_go_think(t_philo *me)
{
	me->status = S_THINKING;
	message_status(me, MSG_THINKING);
}

void	*philo_thread(void *arg)
{
	t_philo	*me;
	
	me = (t_philo *)arg;
	message_status(me, MSG_THINKING);
	usleep(1000);
	if (me->index % 2 == 1)
		usleep(1000);
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
