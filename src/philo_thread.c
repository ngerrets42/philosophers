/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_thread.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:56:52 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/15 12:41:29 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	_grab_forks(t_philo *philo)
{
	int	fork[2];

	if (philo->index % 2 == 0)
	{
		fork[0] = neighbour_id(philo);
		fork[1] = philo->index;
	}
	else
	{
		fork[0] = philo->index;
		fork[1] = neighbour_id(philo);
	}
	pthread_mutex_lock(&philo->program->forks[fork[0]]);
	message(philo, MSG_FORK);
	pthread_mutex_lock(&philo->program->forks[fork[1]]);
	message(philo, MSG_FORK);
}

static t_input	_input(t_philo *philo)
{
	return (philo->program->input);
}

static void	_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->time_eaten = time_get();
	pthread_mutex_unlock(&philo->lock);
	message(philo, MSG_EAT);
	philo->amount_eaten += 1;
	sleep_for(philo, _input(philo).time_to_eat);
	pthread_mutex_unlock(&philo->program->forks[philo->index]);
	pthread_mutex_unlock(&philo->program->forks[neighbour_id(philo)]);
}

static void	*_single(t_philo *philo)
{
	message(philo, MSG_FORK);
	sleep_for(philo, _input(philo).time_to_die);
	return (NULL);
}

void	*philo_thread(void *arg)
{
	t_philo	*p;

	p = arg;
	if (_input(p).nphilo == 1)
		return (_single(p));
	if (p->index % 2 != 0)
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
