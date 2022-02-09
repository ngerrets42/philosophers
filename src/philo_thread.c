/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_thread.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:56:52 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/09 14:36:33 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	_grab_forks(t_philo *philo)
{
	int	fork[2];

	if (philo->id % 2 == 0)
	{
		fork[0] = neighbour_id(philo);
		fork[1] = philo->id;
	}
	else
	{
		fork[0] = philo->id;
		fork[1] = neighbour_id(philo);
	}
	pthread_mutex_lock(&philo->program->forks[fork[0]]);
	message(philo, MSG_FORK);
	pthread_mutex_lock(&philo->program->forks[fork[1]]);
	message(philo, MSG_FORK);
}

static void	_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->time_eaten = time_get();
	pthread_mutex_unlock(&philo->lock);
	message(philo, MSG_EAT);
	sleep_for(philo, philo->program->input.time_to_eat);
	philo->amount_eaten += 1;
	pthread_mutex_unlock(&philo->program->forks[philo->id]);
	pthread_mutex_unlock(&philo->program->forks[neighbour_id(philo)]);
}

static void	*_single(t_philo *philo)
{
	message(philo, MSG_FORK);
	sleep_for(philo, philo->program->input.time_to_die);
	return (NULL);
}

t_input	_input(t_philo *philo)
{
	return (philo->program->input);
}

void	*philo_thread(void *arg)
{
	t_philo	*p;

	p = arg;
	if (_input(p).nphilo == 1)
		return (_single(p));
	if (p->id % 2 != 0)
		usleep(1000);
	if (monitor_thread_init(p) == ERROR)
		return (NULL);
	p->time_eaten = time_get();
	while (!philo_check_death(p))
	{
		_grab_forks(p);
		_eat(p);
		if (p->amount_eaten == _input(p).amount_to_eat)
			break ;
		message(p, MSG_SLEEP);
		sleep_for(p, _input(p).time_to_sleep);
		message(p, MSG_THINK);
	}
	pthread_join(p->monitor, NULL);
	return (NULL);
}
