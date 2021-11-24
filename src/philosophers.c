/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/24 10:28:31 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/24 17:03:00 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*make_philo(t_program *program, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->deathtime = time_get_usec() + program->time_die;
	philo->program = program;
	philo->index = index;
	philo->exit = 0;
	philo->neighbour = NULL;
	pthread_mutex_init(&(philo->lock), NULL);
	pthread_mutex_init(&(philo->fork), NULL);
	mlock(&(philo->lock));
	pthread_create(&(philo->thread), NULL, philo_thread, philo);
	return (philo);
}

static void	setnull(t_philo **philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		philos[i] = NULL;
		i++;
	}
}

static void	_unlock_all(t_philo **philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (philos[i] != NULL)
			munlock(&(philos[i]->lock));
		i++;
	}
}

static void	_set_exit(t_philo **philos, int count)
{
	int	i;

	i = 0;
	_unlock_all(philos, count);
	while (i < count)
	{
		if (philos[i] != NULL)
		{
			printf("Set exit %d\n", i);
//			mlock(&(philos[i]->lock));
			philos[i]->exit = 1;
			//munlock(&(philos[i]->lock));
		}
		i++;
	}
}

static t_philo	**philos_init(t_program *program)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = malloc(sizeof(t_philo *) * program->n_philos);
	if (philos == NULL)
		return (NULL);
	setnull(philos, program->n_philos);
	while (i < program->n_philos)
	{
		philos[i] = make_philo(program, i);
		if (philos[i] == NULL)
		{
			program->exit = 1;
			return (philos);
		}
		if (i > 0)
			philos[i]->neighbour = philos[i - 1];
		i++;
	}
	philos[0]->neighbour = philos[i - 1];
	_unlock_all(philos, program->n_philos);
	return (philos);
}

static void	philos_join_and_free(t_program *program)
{
	int		i;
	t_philo	**philos;

	philos = program->philos;
	i = 0;
	_unlock_all(philos, program->n_philos);
	while (i < program->n_philos)
	{
		printf("waiting for %d\n", i);
		pthread_join(philos[i]->thread, NULL);
		//pthread_mutex_destroy(&(philos[i]->fork));
		//pthread_mutex_destroy(&(philos[i]->lock));
		//free(philos[i]);
		i++;
	}
}

static int	_check_exit(t_program *program)
{
	int				i;
	unsigned long	deathtime;
	unsigned long	time;
	int				exit;

	i = 0;
	exit = 0;
	time = time_get_usec();
	//mlock(&(program->lock));
	while (i < program->n_philos)
	{
		if (program->philos[i] != NULL)
		{
			//printf("CURRENT TIME: %lu\n",
			//		time_get_usec() - program->starttime);
			mlock(&(program->philos[i]->lock));
			deathtime = program->philos[i]->deathtime;
			munlock(&(program->philos[i]->lock));
			if (time >= deathtime)
			{
				printf("DEATHTIME: %lu\nCURRENT TIME: %lu\n",
					deathtime - program->starttime,
					time - program->starttime);
				message_status(program->philos[i], MSG_DEATH);
				//mlock(&(program->lock));
				program->exit = 1;
				exit = 1;
				return (1);
			}
		}
		i++;
	}
	//munlock(&(program->lock));
	return (exit);
}

int	run(t_program *program)
{
	//CREATE
	mlock(&(program->lock));
	program->philos = philos_init(program);
	if (program->philos == NULL)
		return (FAILURE);
	if (program->exit == 1)
		_set_exit(program->philos, program->n_philos);
	munlock(&(program->lock));
	//print("Program starttime: %lu\n", program->starttime);
	//WAIT FOR END
	while (_check_exit(program) == 0)
		usleep(1000);
	printf("SETTING EXIT!!!!\n");
	_set_exit(program->philos, program->n_philos);
	//FREE
	philos_join_and_free(program);
	return (SUCCESS);
}
