/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 11:18:19 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/28 10:56:36 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "program.h"
#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc < 5 || argc > 6)
	{
		putstr("Wrong numbers of arguments. 5 Minimum, 6 maximum! Format:\n");
		putstr("	./philo amount_of_philo die eat sleep [times_to_eat]\n");
		return (1);
	}
	program = program_parse(argc, argv);
	philosophers_start(program);
	program_destroy();
	return (0);
}
