/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   program.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:15:58 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/17 11:29:24 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_program	*program_alloc(void)
{
	t_program	*program;

	program = malloc(sizeof(t_program));
	if (program == NULL)
		return (NULL);
	program->n_philos = 0;
	program->n_eat = 0;
	program->time_die = 0;
	program->time_eat = 0;
	program->time_sleep = 0;
	return (program);
}

int	program_free(t_program *program)
{
	if (program != NULL)
		free(program);
	return (SUCCESS);
}
