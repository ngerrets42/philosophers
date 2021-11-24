/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   program.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:15:58 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/24 11:42:11 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_program	*program_alloc(void)
{
	t_program	*program;

	program = malloc(sizeof(t_program));
	if (program == NULL)
		return (NULL);
	pthread_mutex_init(&(program->lock), NULL);
	program->philos = NULL;
	program->n_philos = 0;
	program->n_eat = 0;
	program->time_die = 0;
	program->time_eat = 0;
	program->time_sleep = 0;
	program->exit = 0;
	return (program);
}

int	program_free(t_program *program)
{
	if (program != NULL)
		free(program);
	return (SUCCESS);
}
