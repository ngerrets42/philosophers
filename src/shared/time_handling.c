/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 17:58:21 by mraasvel      #+#    #+#                 */
/*   Updated: 2022/02/01 16:29:05 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

struct timeval	time_get(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval);
}

long	time_difference(struct timeval start)
{
	struct timeval	diff;
	long			t;

	diff = time_get();
	t = ((diff.tv_sec - start.tv_sec) * 1000 +
		(diff.tv_usec - start.tv_usec) / 1000);
	return (t);
}

void	sleep_for(t_philo *philo, long ms)
{
	struct timeval	time;

	time = time_get();
	while (time_difference(time) < ms && !philo->program->philo_dead)
		usleep(100);
}
