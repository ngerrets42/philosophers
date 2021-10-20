/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 15:17:18 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/20 15:55:58 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "program.h"
# include <pthread.h>

# define STANDARD_SLEEP_TIME 10000

typedef struct s_queue
{
	struct s_queue	*next;
}		t_queue;

typedef enum e_status
{
	S_EATING,
	S_SLEEPING,
	S_THINKING,
	S_DEAD,
	S_NONE
}	t_status;

typedef enum e_msg
{
	MSG_EATING,
	MSG_SLEEPING,
	MSG_THINKING,
	MSG_DEATH,
	MSG_LAST
}	t_msg;

typedef struct s_philo
{
	pthread_t		thread;
	t_program		*program;
	int				index;
	pthread_mutex_t	fork_mutex;
	t_status		status;
	struct s_philo	*neighbour;
	unsigned long	time_of_death;
	int				times_eaten;
}					t_philo;


t_philo	*philosopher_create(t_program *program, int index);
void	philosopher_destroy(t_philo *philo);
void	philosophers_start(t_program *program);

void	*philo_thread(void *arg);

void	putstr(char *str);
void	message_status(t_philo *me, t_msg msg);

#endif
