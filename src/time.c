/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:57:36 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/09 14:38:54 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

struct timeval	time_get(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval);
}

long	time_diff(struct timeval start)
{
	struct timeval	diff;
	long			t;

	diff = time_get();
	t = ((diff.tv_sec - start.tv_sec) * 1000
			+ (diff.tv_usec - start.tv_usec) / 1000);
	return (t);
}

void	sleep_for(t_philo *philo, long ms)
{
	struct timeval	time_start;

	time_start = time_get();
	while (time_diff(time_start) < ms)
	{
		// if (philo_check_death(philo) > 0)
		// 	return ;
		usleep(SLEEP_CONSTANT);
	}
}
