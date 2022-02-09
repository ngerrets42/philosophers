/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 16:05:56 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/09 14:56:31 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define SUCCES 0
# define ERROR -1

# include <sys/time.h>
# include <pthread.h>

typedef enum e_msg
{
	MSG_EAT,
	MSG_SLEEP,
	MSG_THINK,
	MSG_FORK,
	MSG_DEAD
}	t_msg;

typedef struct s_input
{
	int	nphilo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	amount_to_eat;
}		t_input;

typedef struct s_program	t_program;

typedef struct s_philo
{
	int				index;
	t_program		*program;
	pthread_mutex_t	lock;
	struct timeval	time_eaten;
	int				amount_eaten;
	pthread_t		monitor;
}					t_philo;

typedef struct s_program
{
	t_philo			*philos;
	t_input			input;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	struct timeval	start_time;
	int				philo_dead;
	bool			start;
}					t_program;

#endif
