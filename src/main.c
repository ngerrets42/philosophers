/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:01:24 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/24 14:54:28 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc < 5 || argc > 6)
	{
		putstr("Wrong numbers of arguments. 5 Minimum, 6 maximum! Format:\n");
		putstr("	./philo amount_of_philo die eat sleep [times_to_eat]\n");
		return (FAILURE);
	}
	program = program_alloc();
	message_status(NULL, 0);
	if (program == NULL)
		return (1);
	if (parse(program, argc, argv) == FAILURE)
		return (program_free(program));
	run(program);
	return (SUCCESS);
}
