/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 16:19:04 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/01/26 16:28:14 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	is_number(char *str)
{
	while (*str)
	{
		if ((*str < '0') || (*str > '9'))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

t_bool	parse(t_program *program, int argc, char **argv)
{
	if (!is_number(argv[1]) || !is_number(argv[2]) || !is_number(argv[3])
		|| !is_number(argv[4]))
		return (FALSE);
	if (argc == 6 && !is_number(argv[5]))
		return (FALSE);
	program->numb_philo = ft_atoi(argv[1]);
	program->time_die = ft_atoi(argv[2]);
	program->time_eat = ft_atoi(argv[3]);
	program->time_sleep = ft_atoi(argv[4]);
	program->numb_eat = -1;
	if (argc == 6)
		program->numb_eat = ft_atoi(argv[5]);
	return (TRUE);
}
