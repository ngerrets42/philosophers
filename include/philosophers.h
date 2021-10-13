/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 15:17:18 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/13 12:45:41 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "program.h"
# include <pthread.h>

typedef enum e_status
{
	S_EATING,
	S_SLEEPING,
	S_THINKING,
	S_DEAD,
	S_NONE
}	t_status;

typedef struct s_philo
{
	pthread_t		thread;
	t_program		*program;
	int				index;
	int				fork_has;
	pthread_mutex_t	fork_mutex;
	t_status		status;
	struct s_philo	*neighbour;
	unsigned long	time_of_death;
	unsigned long	time_of_action;
}					t_philo;


t_philo	*philosopher_create(t_program *program, int index);
void	philosopher_destroy(t_philo *philo);
void	philosophers_start(t_program *program);

void	*philo_thread(void *arg);

void	message_status(t_philo *me);

#endif
