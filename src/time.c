/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:57:36 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/15 13:01:44 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	Simply calls the gettimeofday function and returns the timeval struct.
*/
struct timeval	time_get(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval);
}

/*
**	Returns the time difference in MICROseconds between the given start time and
**	the time of calling this function (time it is NOW). 
*/
long	time_diff(struct timeval start)
{
	struct timeval	diff;
	long			t;

	diff = time_get();
	t = ((diff.tv_sec - start.tv_sec) * 1000
			+ (diff.tv_usec - start.tv_usec) / 1000);
	return (t);
}

/*
**	Sleep for given amount of MICROseconds. It does so by looping over usleep
**	using a constant amount of time until it surpasses given usec.
**
**	Checking for philosopher death during sleep seems unneccesary.
**	" if (philo_check_death(philo) > 0) "
*/
void	sleep_for(t_philo *philo, long usec)
{
	struct timeval	time_start;

	time_start = time_get();
	while (time_diff(time_start) < usec)
		usleep(SLEEP_CONSTANT);
}
