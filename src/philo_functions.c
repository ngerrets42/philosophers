/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 08:19:21 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/27 13:53:23 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*philosopher_create(t_program *program, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	if (pthread_mutex_init(&(philo->fork_mutex), NULL) != 0)
	{
		free(philo);
		return (NULL);
	}
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
