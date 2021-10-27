/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 15:16:29 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/27 14:05:41 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	**_philosophers_destroy(t_philo **philos, int i)
{
	int	n;

	n = i;
	while (i > 0)
	{
		i--;
		philos[i]->kill = 1;
	}
	while (n > 0)
	{
		n--;
		pthread_join(philos[n]->thread, NULL);
		///
		printf("philo %d stopped!\n", philos[n]->index);
		pthread_mutex_destroy(&(philos[n]->fork_mutex));
		free(philos[n]);
	}
	return (NULL);
}

static t_philo	**_philosophers_init(t_program *program)
{
	t_philo	**philos;
	t_philo	*neighbour;
	int		i;

	neighbour = NULL;
	philos = malloc(sizeof(t_philo *) * program->philo_amount);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < program->philo_amount)
	{
		philos[i] = philosopher_create(program, i);
		philos[i]->neighbour = neighbour;
		neighbour = philos[i];
		if (philos[i] == NULL)
			return (_philosophers_destroy(philos, i));
		i++;
	}
	philos[0]->neighbour = philos[i - 1];
	return (philos);
}

static int		_check_if_end(t_program *program, t_philo **philos)
{
	int				i;
	unsigned long	current_time;

	i = 0;
	current_time = time_get_micro();
	while (i < program->philo_amount)
	{
		program->turn = i;
		if (philos[i]->time_of_death < current_time)
		{
			message_status(philos[i], MSG_DEATH);
			_philosophers_destroy(philos, program->philo_amount);
			return (1);
		}
		if (philosophers_have_eaten(philos, program) == 1)
		{
			_philosophers_destroy(philos, program->philo_amount);
			return (1);
		}
		i++;
	}
	return (0);
}

void	philosophers_start(t_program *program)
{
	t_philo			**philos;
	int				i;

	philos = _philosophers_init(program);
	if (philos == NULL)
	{
		putstr("Malloc error!\n");
		return ;
	}
	while (1)
	{
		i = 0;
		if (_check_if_end(program, philos) == 1)
			return ;
		usleep(1000);
	}
}
