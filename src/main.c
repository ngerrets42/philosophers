/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 11:18:19 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/04 15:16:27 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "program.h"

static int	_program_print(t_program *program)
{
	if (program == NULL)
		return printf("Program is NULL\n");
	return printf("Program:\n	Philosphers: %d\n	Eat-Time: %d\n	Time-to-die: %d\n	Time-to-eat: %d\n	Time-to-sleep: %d\n",
				program->philo_amount, program->eat_amount, program->time_to_die, program->time_to_eat, program->time_to_sleep);
}

int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong numbers of arguments. 5 Minimum, 6 maximum!\n");
		return (1);
	}
	program = program_parse(argc, argv);
	_program_print(program);
	philosophers_start(program);
	program_destroy();
	return (0);
}
