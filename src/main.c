/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 16:05:46 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/01/26 18:56:26 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>

static void _print_philos(t_program *program)
{
	int		i;
	t_philo	p;

	i = 0;
	while (i < program->numb_philo)
	{
		p = program->philos[i];
		printf("PHILO %d\naddr left: %p\naddr right: %p\n", p.index, p.fork_l, p.fork_r);
		i++;
	}
}

static void	wait_for_death(t_program *program)
{
	int		i;
	t_ul	time;

	while (program->death == FALSE)
	{
		usleep(2000);
		pthread_mutex_lock(&program->lock);
		i = 0;
		time = time_get_usec();
		while (i < program->numb_philo)
		{
			if (program->time_die * 1000 + program->philos[i].time_eaten < time)
			{
				program->death = TRUE;
				pthread_mutex_unlock(&program->lock);
				philo_msg_send(&program->philos[i], MSG_DEATH);
				break ;
			}
			i++;
		}
		pthread_mutex_unlock(&program->lock);
	}
}

int	main(int argc, char **argv)
{
	t_program	*program;
	
	if (argc < 5 || argc > 6)
		return (1);
	program = alloc_size(sizeof(t_program));
	if (program == NULL)
		return (1);
	if (parse(program, argc, argv) == FALSE)
	{
		//free program
		return (1);
	}
	if (init(program) == FALSE)
	{
		//free program
		return (1);
	}
	philo_threads_start(program);
	wait_for_death(program);
	philo_threads_join(program);
	//_print_philos(program);
	//free program
}