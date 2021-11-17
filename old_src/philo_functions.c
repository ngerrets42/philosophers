/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 08:19:21 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/28 11:30:33 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*philosopher_create(t_program *program, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	pthread_mutex_init(&(philo->fork_mutex), NULL);
	pthread_mutex_init(&(philo->thread_mutex), NULL);
	philo_lock(philo);
	philo->time_of_death = program->start_time + program->time_to_die;
	philo->program = program;
	philo->status = S_THINKING;
	philo->times_eaten = 0;
	philo->neighbour = NULL;
	philo->index = index;
	philo->kill = 0;
	if (pthread_create(&(philo->thread), NULL, philo_thread, philo) != 0)
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}

int	philo_lock(t_philo *philo)
{
	printf("===Attempting lock of philosopher %d\n", philo->index + 1);
	return (pthread_mutex_lock(&(philo->thread_mutex)));
}

int	philo_unlock(t_philo *philo)
{
	printf("===Unlocking of philosopher %d\n", philo->index + 1);
	return (pthread_mutex_unlock(&(philo->thread_mutex)));
}

int	philosophers_have_eaten(t_philo **philos, t_program *program)
{
	int	i;

	i = 0;
	while (i < program->philo_amount)
	{
		if (philos[i]->times_eaten < program->eat_amount)
			return (0);
		i++;
	}
	return (1);
}
