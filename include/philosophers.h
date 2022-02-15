/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 16:06:01 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/15 13:26:57 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include "structs.h"
# include "str.h"

/*
**	Constants to define how long the "sleep_for" function and the monitor must
**	usleep.
*/
# define SLEEP_CONSTANT 1000
# define MONITOR_SLEEP_CONSTANT 1000

/* message.c */
void			message(t_philo *philo, t_msg msg);

/* monitor.c */
int				monitor_thread_init(t_philo *philo);
void			*monitor_thread(void *arg);

/* mutexes.c */
int				mutexes_init(t_program *program);
void			mutexes_destroy(t_program *program);

/* parse.c */
int				parse_input(t_input *input, int argc, char **argv);

/* philo_thread.c */
void			*philo_thread(void *arg);

/* philo_util.c */
int				philo_check_death(t_philo *philo);
int				neighbour_index(t_philo *philo);

/* threads_create.c */
int				threads_create(t_program *program);
int				threads_join(t_program *program);

/* time.c */
struct timeval	time_get(void);
long			time_diff(struct timeval start);
void			sleep_for(t_philo *philo, long usec);

#endif
