/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 16:05:22 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/01 16:52:20 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	free_program(t_program *program)
{
	free(program->philos);
	free(program->threads);
	free(program->forks);
	return (ERROR);
}

static int	program_initialize(t_program *program)
{
	program->philos = malloc(program->input.amount_philo * sizeof(t_philo));
	if (program->philos == NULL)
		return (ERROR);
	program->forks = malloc(program->input.amount_philo * sizeof(pthread_mutex_t));
	if (program->forks == NULL)
		return (free_program(program));
	program->threads = malloc(program->input.amount_philo * sizeof(pthread_t));
	if (program->threads == NULL)
		return (free_program(program));
	if (mutexes_init(program) == ERROR)
		return (free_program(program));
	program->start_time = time_get();
	return (SUCCES);
}

static int	program_exit(t_program *program, int exit_status)
{
	mutexes_destroy(program);
	free_program(program);
	return (exit_status);
}

int	main(int argc, char **argv)
{
	t_program	program;

	ft_bzero(&program, sizeof(t_program));
	if (parse_input(&program.input, argc, argv) == ERROR)
		return (ERROR);
	if (program_initialize(&program) == ERROR)
		return (ERROR);
	if (threads_create(&program) == ERROR)
		return (program_exit(&program, ERROR));
	threads_join(&program);
	return (program_exit(&program, SUCCES));
}
