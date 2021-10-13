/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 08:19:21 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/13 10:55:08 by ngerrets      ########   odam.nl         */
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
	philo->time_of_action = program->start_time;
	philo->program = program;
	philo->status = S_THINKING;
	philo->neighbour = NULL;
	philo->fork_has = 1;
	philo->index = index;
	if (pthread_create(&(philo->thread), NULL, philo_thread, philo) != 0)
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}

void	philosopher_destroy(t_philo *philo)
{
	if (philo == NULL)
		return ;
	//MAYBE KILL THREAD?
	pthread_mutex_destroy(&(philo->fork_mutex));
	free(philo);
}
