/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:13:05 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/17 11:43:47 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse(t_program *program, int argc, char **argv)
{
	program->n_philos = ft_atoi(argv[1]);
	program->time_die = ft_atoi(argv[2]);
	program->time_eat = ft_atoi(argv[3]);
	program->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program->n_eat = ft_atoi(argv[5]);
	else
		program->n_eat = -1;
	return (SUCCESS);
}
