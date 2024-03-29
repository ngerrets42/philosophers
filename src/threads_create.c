/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads_create.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:57:02 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/15 13:04:24 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	In case of ERROR this function waits for all already made threads to close
**	before returning ERROR.
*/
static int	_abort_return_err(t_program *program, int i)
{
	program->philo_dead = true;
	while (i > 0)
	{
		i--;
		pthread_join(program->threads[i], NULL);
	}
	return (ERROR);
}

/*
**	Creates all philosopher threads and sets the start time of the program.
*/
int	threads_create(t_program *program)
{
	int	i;

	i = 0;
	program->start = false;
	while (i < program->input.nphilo)
	{
		if (pthread_create(&program->threads[i], NULL,
				philo_thread, &program->philos[i]) != 0)
			return (_abort_return_err(program, i));
		usleep(100);
		i++;
	}
	program->start_time = time_get();
	program->start = true;
	return (SUCCES);
}

/*
**	Waits for all threads to end (join).
*/
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
