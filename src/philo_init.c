/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 16:42:31 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/01/26 17:28:35 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	_mutinit(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->numb_philo)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static	void	_single_philo(t_philo *philo, int index, t_program *program)
{
	philo->index = index;
	philo->program = program;
	philo->fork_l = &program->forks[index];
	if (index == 0)
		philo->fork_r = &program->forks[program->numb_philo - 1];
	else
		philo->fork_r = &program->forks[index - 1];
}

static	void	_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->numb_philo)
	{
		_single_philo(&program->philos[i], i, program);
		i++;
	}
}

t_bool	init(t_program *program)
{
	if (pthread_mutex_init(&program->lock, NULL) != 0)
		return (FALSE);
	program->philos = alloc_size(sizeof(t_philo) * program->numb_philo);
	if (program->philos == NULL)
		return (FALSE);
	program->forks = malloc(sizeof(pthread_mutex_t) * program->numb_philo);
	if (program->forks == NULL)
	{
		free(program->philos);
		return (FALSE);
	}
	if (_mutinit(program) == FALSE)
	{
		free(program->philos);
		free(program->forks);
		return (FALSE);
	}
	_philos(program);
	return (TRUE);
}
