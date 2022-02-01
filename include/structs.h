/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 16:05:56 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/01 16:39:28 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define SUCCES 0
# define ERROR -1

# include <sys/time.h>
# include <pthread.h>

typedef struct s_program	t_program;

typedef enum e_msg
{
	MSG_EAT,
	MSG_SLEEP,
	MSG_THINK,
	MSG_FORK,
	MSG_DEAD
}	t_msg;

typedef enum e_status
{
	active,
	inactive,
	joined
}	t_status;

typedef struct s_input
{
	int	amount_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	amount_to_eat;
}	t_input;

typedef struct s_philo
{
	int				id;
	t_program		*program;
	pthread_mutex_t	search_lock;
	pthread_mutex_t	lock;
	struct timeval	time_eaten;
	int				amount_eaten;
	enum e_status	status;
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
