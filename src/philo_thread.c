/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_thread.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/08 08:59:52 by mraasvel      #+#    #+#                 */
/*   Updated: 2022/02/01 16:43:34 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_grab_forks(t_philo *philo)
{
	int	indexes[2];
	pthread_mutex_t	*forks[2];

	indexes[0] = left_index(philo);
	indexes[1] = right_index(philo);
	if (philo->id % 2 == 0)
		ft_swap_int(&indexes[0], &indexes[1]);


	//LEFT FORK
	forks[0] = &philo->program->forks[indexes[0]];
	//RIGHT FORK
	forks[1] = &philo->program->forks[indexes[1]];
	
	pthread_mutex_lock(forks[0]);
	message(philo, MSG_FORK);
	pthread_mutex_lock(forks[1]);
	message(philo, MSG_FORK);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->time_eaten = time_get();
	pthread_mutex_unlock(&philo->lock);
	message(philo, MSG_EAT);
	sleep_for(philo, philo->program->input.time_to_eat);
	philo->amount_eaten += 1;
	pthread_mutex_unlock(&philo->program->forks[left_index(philo)]);
	pthread_mutex_unlock(&philo->program->forks[right_index(philo)]);
}

static int	monitor_thread_init(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, monitor_thread, philo) != 0)
	{
		philo->program->philo_dead = true;
		return (ERROR);
	}
	return (SUCCES);
}

static void	*single_philosopher(t_philo *philo)
{
	message(philo, MSG_FORK);
	sleep_for(philo, philo->program->input.time_to_die);
	return (NULL);
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->program->input.amount_philo == 1)
		return (single_philosopher(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	philo->time_eaten = time_get();
	if (monitor_thread_init(philo) == ERROR)
		return (NULL);
	while (true)
	{
		if (philo->program->philo_dead)
			break ;
		philo_grab_forks(philo);
		philo_eat(philo);
		if (philo->amount_eaten == philo->program->input.amount_to_eat)
			break ;
		message(philo, MSG_SLEEP);
		sleep_for(philo, philo->program->input.time_to_sleep);
		message(philo, MSG_THINK);
		usleep(1000);
	}
	philo->status = inactive;
	pthread_join(philo->monitor, NULL);
	return (NULL);
}
