/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads_create.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:57:02 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/09 14:38:13 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	_abort(t_program *program, int i)
{
	program->philo_dead = true;
	while (i > 0)
	{
		i--;
		pthread_join(program->threads[i], NULL);
	}
	return (ERROR);
}

int	threads_create(t_program *program)
{
	int	i;

	i = 0;
	program->start = false;
	while (i < program->input.nphilo)
	{
		if (pthread_create(&program->threads[i], NULL,
				philo_thread, &program->philos[i]) != 0)
			return (_abort(program, i));
		usleep(100);
		i++;
	}
	program->start_time = time_get();
	program->start = true;
	return (SUCCES);
}

int	threads_join(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->input.nphilo)
	{
		if (pthread_join(program->threads[i], NULL) != 0)
			return (ERROR);
		i++;
	}
	return (SUCCES);
}
