/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:13:05 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/17 11:25:16 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	atoi(char *str);

int	parse(t_program *program, int argc, char **argv)
{
	program->n_philos = atoi(argv[1]);
	program->time_die = atoi(argv[2]);
	program->time_eat = atoi(argv[3]);
	program->time_sleep = atoi(argv[4]);
	if (argc == 6)
		program->n_eat = atoi(argv[5]);
	else
		program->n_eat = -1;
	return (SUCCESS);
}
