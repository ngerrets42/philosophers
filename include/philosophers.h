/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:07:37 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/24 12:45:02 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include "str.h"

# define SUCCESS 0
# define FAILURE 1

typedef unsigned long t_ulong;

typedef struct s_program
{
	pthread_mutex_t	lock;
	struct s_philo	**philos;
	int				n_philos;
	int				n_eat;
	t_ulong			time_die;
	t_ulong			time_eat;
	t_ulong			time_sleep;
	int				exit;
}					t_program;

typedef struct s_philo
{
	t_program		*program;
	int				index;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	lock;
	struct s_philo	*neighbour;
}					t_philo;

t_program	*program_alloc(void);
int			program_free(t_program *program);
int			parse(t_program *program, int argc, char **argv);
int			run(t_program *program);

void		*philo_thread(void *arg);

//	philo_functions.c
int	mlock(pthread_mutex_t *mutex);
int	munlock(pthread_mutex_t *mutex);

#endif
