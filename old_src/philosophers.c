/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 15:16:29 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/28 11:28:29 by ngerrets      ########   odam.nl         */
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
		philo_lock(philos[n]);
		philos[i]->kill = 1;
		philo_unlock(philos[n]);
	}
	while (n > 0)
	{
		n--;
		pthread_join(philos[n]->thread, NULL);
		pthread_mutex_destroy(&(philos[n]->fork_mutex));
		pthread_mutex_destroy(&(philos[n]->thread_mutex));
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
	message_status(NULL, 0);
	philos = malloc(sizeof(t_philo *) * program->philo_amount);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < program->philo_amount)
	{
		philos[i] = philosopher_create(program, i);
		if (philos[i] == NULL)
			return (_philosophers_destroy(philos, i));
		philos[i]->neighbour = neighbour;
		neighbour = philos[i];
		philo_unlock(philos[i]);
		i++;
	}
	philo_lock(philos[0]);
	philos[0]->neighbour = philos[i - 1];
	philo_unlock(philos[0]);
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
		philo_lock(philos[i]);
		if (philos[i]->time_of_death < current_time)
		{
			message_status(philos[i], MSG_DEATH);
			philo_unlock(philos[i]);
			_philosophers_destroy(philos, program->philo_amount);
			return (1);
		}
		if (philosophers_have_eaten(philos, program) == 1)
		{
			philo_unlock(philos[i]);
			_philosophers_destroy(philos, program->philo_amount);
			return (1);
		}
		philo_unlock(philos[i]);
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
