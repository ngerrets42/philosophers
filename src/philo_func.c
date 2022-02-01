/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_func.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 17:24:49 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/01/26 18:28:06 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_usleep(t_philo *p, t_ul usec)
{
	t_ul	time_actually_slept;
	t_ul	time_start;

	usec *= 1000;
	while (usec > 5000)
	{
		time_start = time_get_usec();
		usleep(5000);
		time_actually_slept = time_get_usec() - time_start;
		if (usec > time_actually_slept)
			usec -= time_actually_slept;
		else
			usec = 0;
	}
	if (usec > 0)
		usleep(usec);
}

t_bool	philo_check_death(t_philo *p)
{
	t_program	*program;
	t_bool		death;

	program = p->program;
	pthread_mutex_lock(&(program->lock));
	death = program->death;
	pthread_mutex_unlock(&(program->lock));
	return (death);
}

static t_bool	philo_check_done_eating(t_philo *p)
{
	t_program	*program;
	t_bool		done_eating;
			
	program = p->program;
	pthread_mutex_lock(&(program->lock));
	if (program->numb_eat < 0)
		done_eating = FALSE;
	else
	{
		if (p->numb_eaten < program->numb_eat)
			done_eating = FALSE;
		else
			done_eating = TRUE;
	}
	pthread_mutex_unlock(&(program->lock));
	return (done_eating);
}

t_bool	philo_is_done(t_philo *p)
{
	if (philo_check_death(p))
		return (TRUE);
	if (philo_check_done_eating(p))
		return (TRUE);
	return (FALSE);
}
