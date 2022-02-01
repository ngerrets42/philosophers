/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 16:16:11 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/01 13:36:48 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "str.h"
# include "func.h"
# include "time_get.h"
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>

typedef unsigned long	t_ul;

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef enum e_msg
{
	MSG_EATING,
	MSG_SLEEPING,
	MSG_THINKING,
	MSG_DEATH,
	MSG_FORK_L,
	MSG_FORK_R,
	MSG_LAST
}	t_msg;

typedef struct s_philo
{
	void			*program;
	pthread_t		thread;
	int				index;
	t_ul			time_eaten;
	int				numb_eaten;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	
}					t_philo;

typedef struct s_program
{
	pthread_mutex_t	lock;
	t_bool			death;
	int				numb_philo;
	int				times_eaten;
	int				times_eaten_total;
	t_ul			time_die;
	t_ul			time_eat;
	t_ul			time_sleep;
	int				numb_eat;
	t_philo			*philos;
	pthread_mutex_t *forks;
}					t_program;

/* parse */
t_bool	parse(t_program *program, int argc, char **argv);

/* philo_init */
t_bool	init(t_program *program);

/* philo_thread */
t_bool	philo_threads_start(t_program *program);
t_bool	philo_threads_join(t_program *program);

/* philo_func */
void	philo_usleep(t_philo *p, t_ul usec);
t_bool	philo_check_death(t_philo *p);
t_bool	philo_is_done(t_philo *p);

/* philo_loop */
void	philo_msg_send(t_philo *p, t_msg m);
void	philo_grab_forks(t_philo *p);
void	philo_drop_forks(t_philo *p);
void	philo_eat(t_philo *p);
void	philo_sleep(t_philo *p);

#endif
