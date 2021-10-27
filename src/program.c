/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   program.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 11:22:01 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/27 13:06:38 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "program.h"
#include <sys/time.h>

unsigned long	time_get_micro(void)
{
	struct timeval	val;
	unsigned long	time;

	gettimeofday(&val, NULL);
	time = val.tv_sec * 1000000 + val.tv_usec;
	return (time);
}

static t_program	*_program_init(void)
{
	t_program	*program;

	program = malloc(sizeof(t_program));
	if (program == NULL)
		return (NULL);
	program->turn = 0;
	program->eat_amount = 0;
	program->philo_amount = 0;
	program->time_to_die = 0;
	program->time_to_eat = 0;
	program->time_to_sleep = 0;
	return (program);
}

t_program	*program_get(void)
{
	static t_program	*program = NULL;

	if (program == NULL)
	{
		program = _program_init();
		if (program == NULL)
			return (NULL);
	}
	return (program);
}

t_program	*program_parse(int argc, char **argv)
{
	t_program	*program;

	program = program_get();
	if (program == NULL)
		return (NULL);
	program->start_time = time_get_micro();
	program->philo_amount = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]) * 1000;
	program->time_to_eat = ft_atoi(argv[3]) * 1000;
	program->time_to_sleep = ft_atoi(argv[4]) * 1000;
	program->eat_amount = -1;
	if (argc == 6)
		program->eat_amount = ft_atoi(argv[5]);
	return (program);
}

void	program_destroy(void)
{
	t_program	*program;

	program = program_get();
	if (program != NULL)
		free(program);
}
