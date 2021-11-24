/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/24 10:28:31 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/24 12:46:05 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*make_philo(t_program *program, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->program = program;
	philo->index = index;
	philo->neighbour = NULL;
	pthread_mutex_init(&(philo->lock), NULL);
	pthread_mutex_init(&(philo->fork), NULL);
	mlock(&(philo->lock));
	pthread_create(&(philo->thread), NULL, philo_thread, philo);
	return (philo);
}

static void	setnull(t_philo **philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		philos[i] = NULL;
		i++;
	}
}

static void	_unlock_all(t_philo **philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (philos[i] != NULL)
			munlock(&(philos[i]->lock));
		i++;
	}
}

static t_philo	**philos_init(t_program *program)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = malloc(sizeof(t_philo *) * program->n_philos);
	if (philos == NULL)
		return (NULL);
	setnull(philos, program->n_philos);
	while (i < program->n_philos)
	{
		philos[i] = make_philo(program, i);
		if (philos[i] == NULL)
		{
			program->exit = 1;
			printf("AAAAAH!\n");
			return (philos);
		}
		if (i > 0)
			philos[i]->neighbour = philos[i - 1];
		i++;
	}
	philos[0]->neighbour = philos[i - 1];
	_unlock_all(philos, program->n_philos);
	return (philos);
}

static void	philos_join_and_free(t_program *program)
{
	int		i;
	t_philo	**philos;

	philos = program->philos;
	i = 0;
	while (i < program->n_philos)
	{
		pthread_join(philos[i]->thread, NULL);
		pthread_mutex_destroy(&(philos[i]->fork));
		pthread_mutex_destroy(&(philos[i]->lock));
		free(philos[i]);
		i++;
	}
}

int	run(t_program *program)
{
	//CREATE
	mlock(&(program->lock));
	program->philos = philos_init(program);
	if (program->philos == NULL)
		return (FAILURE);
	munlock(&(program->lock));
	//WAIT FOR END

	//FREE
	philos_join_and_free(program);
	return (SUCCESS);
}
