/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:56:46 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/09 14:56:31 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	_abort(t_program *program, int i)
{
	pthread_mutex_destroy(&program->forks[i]);
	while (i > 0)
	{
		i--;
		pthread_mutex_destroy(&program->forks[i]);
		pthread_mutex_destroy(&program->philos[i].lock);
	}
	return (ERROR);
}

int	mutexes_init(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->input.nphilo)
	{
		program->philos[i].index = i;
		program->philos[i].program = program;
		program->philos[i].amount_eaten = 0;
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
			return (_abort(program, i));
		else if (pthread_mutex_init(&program->philos[i].lock, NULL) != 0)
			return (_abort(program, i));
		i++;
	}
	if (pthread_mutex_init(&program->lock, NULL) != 0)
		return (_abort(program, i + 1));
	return (SUCCES);
}

void	mutexes_destroy(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->input.nphilo)
	{
		pthread_mutex_destroy(&program->forks[i]);
		pthread_mutex_destroy(&program->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&program->lock);
}
