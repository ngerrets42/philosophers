/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:07:37 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/24 15:29:04 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include "time_get.h"
# include "str.h"

# define SUCCESS 0
# define FAILURE 1

typedef unsigned long t_ulong;

typedef enum e_msg
{
	MSG_EATING,
	MSG_SLEEPING,
	MSG_THINKING,
	MSG_DEATH,
	MSG_LAST
}	t_msg;

typedef struct s_program
{
	pthread_mutex_t	lock;
	struct s_philo	**philos;
	int				n_philos;
	int				n_eat;
	t_ulong			time_die;
	t_ulong			time_eat;
	t_ulong			time_sleep;
	t_ulong			starttime;
	int				exit;
}					t_program;

typedef struct s_philo
{
	t_program		*program;
	int				index;
	int				exit;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	lock;
	struct s_philo	*neighbour;
	t_ulong			deathtime;
}					t_philo;

t_program	*program_alloc(void);
int			program_free(t_program *program);
int			parse(t_program *program, int argc, char **argv);
int			run(t_program *program);

void		message_status(t_philo *me, t_msg msg);
void		*philo_thread(void *arg);

//	philo_functions.c
int	mlock(pthread_mutex_t *mutex);
int	munlock(pthread_mutex_t *mutex);

#endif
