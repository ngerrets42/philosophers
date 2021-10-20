/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 11:18:19 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/20 15:55:07 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "program.h"
#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc < 5 || argc > 6)
	{
		//REMOVE
		printf("amount_of_philo die eat sleep [times_eat]\n");
		printf("Wrong numbers of arguments. 5 Minimum, 6 maximum!\n");
		return (1);
	}
	program = program_parse(argc, argv);
	// _program_print(program);
	philosophers_start(program);
	program_destroy();
	return (0);
}
