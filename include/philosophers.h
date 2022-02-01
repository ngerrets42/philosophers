/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 16:06:01 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/01 16:57:14 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include "structs.h"

/* Other Functions */

int				parse_input(t_input *input, int argc, char **argv);
void			message(t_philo *philo, t_msg msg);

/* Philo Routine Functions */

void			*philo_thread(void *arg);
void			*monitor_thread(void *arg);

int				right_index(t_philo *philo);
int				left_index(t_philo *philo);

/* Thread Functions */

void			monitor_threads(t_program *program);
int				threads_create(t_program *program);
int				threads_join(t_program *program);

/* Mutex Functions */

int				mutexes_init(t_program *program);
void			mutexes_destroy(t_program *program);

/* Time Functions */

void			sleep_for(t_philo *philo, long ms);
void			philo_wait(t_philo *philo, long ms);
long			time_difference(struct timeval start);
struct timeval	time_get(void);

/* Utillity Functions */

int				ft_atoi(char *s);
char			*ft_itoa(int n);
void			ft_bzero(void *dst, size_t size);
int				ft_strcmp(char *a, char *b);
int				ft_error(char *a, char *b);
int				ft_perror(char *s);
void			ft_swap_int(int *a, int *b);
int				ft_putstr_fd(int fd, char *str);

#endif
