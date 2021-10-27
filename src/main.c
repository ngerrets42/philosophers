/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 11:18:19 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/27 13:56:38 by ngerrets      ########   odam.nl         */
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
	putstr("back in main thread\n");
	program_destroy();
	return (0);
}
