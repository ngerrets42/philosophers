/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/08 08:40:04 by mraasvel      #+#    #+#                 */
/*   Updated: 2022/02/01 16:52:52 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "philosophers.h"

static int	_abort(t_program *program, int i, int time)
{
	if (time > 0)
		pthread_mutex_destroy(&program->forks[i]);
	if (time > 1)
		pthread_mutex_destroy(&program->philos[i].search_lock);
	while (i > 0)
	{
		i--;
		pthread_mutex_destroy(&program->forks[i]);
		pthread_mutex_destroy(&program->philos[i].search_lock);
		pthread_mutex_destroy(&program->philos[i].lock);
	}
	return (ERROR);
}

int	mutexes_init(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->input.amount_philo)
	{
		program->philos[i].id = i + 1;
		program->philos[i].program = program;
		program->philos[i].amount_eaten = 0;
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
			return (_abort(program, i, 0));
		else if (pthread_mutex_init(&program->philos[i].search_lock, NULL) != 0)
			return (_abort(program, i, 1));
		else if (pthread_mutex_init(&program->philos[i].lock, NULL) != 0)
			return (_abort(program, i, 2));
		i++;
	}
	if (pthread_mutex_init(&program->lock, NULL) != 0)
		return (_abort(program, i + 1, 0));
	return (SUCCES);
}

/*
Destructor for all mutexes
*/

void	mutexes_destroy(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->input.amount_philo)
	{
		pthread_mutex_destroy(&program->forks[i]);
		pthread_mutex_destroy(&program->philos[i].search_lock);
		pthread_mutex_destroy(&program->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&program->lock);
}
