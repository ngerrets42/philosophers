/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/24 11:01:40 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/24 17:07:39 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define STANDARD_SLEEP_TIME 1000

void	philo_sleep(t_philo *philo, unsigned long usec)
{
	int			time_diff;
	unsigned long	time_last;
	unsigned long	time_now;
	unsigned long	time_to_sleep;

	time_diff = 0;
	time_last = time_get_usec();
	while (1)
	{
		//printf("...sleeping... philo %d usec = %u\n", philo->index, usec);
		time_to_sleep = STANDARD_SLEEP_TIME - time_diff;
		if (usec < STANDARD_SLEEP_TIME)
		time_to_sleep = usec;
		usleep(time_to_sleep);
		if (usec < STANDARD_SLEEP_TIME)
			break ;
		time_now = time_get_usec();
		//if (time_now - time_last > usec)
		//	break ;
		usec -= time_now - time_last;
		time_diff = time_now - time_last - time_to_sleep;
		time_last = time_now;
	}
	////print("...done sleeping... philo %d\n", philo->index);
}

static int	_check_exit(t_philo *philo)
{
	int	r;

	mlock(&(philo->lock));
	r = philo->exit;
	munlock(&(philo->lock));
	return (r);
}

void	_think(t_philo *philo)
{
	message_status(philo, MSG_THINKING);
	//GET FORKS
	mlock(&(philo->fork));
	mlock(&(philo->neighbour->fork));
	if (_check_exit(philo) == 1)
	{
		munlock(&(philo->fork));
		munlock(&(philo->neighbour->fork));
		return ;
	}
	//EAT
	mlock(&(philo->lock));
	philo->deathtime = time_get_usec() + philo->program->time_die;
	munlock(&(philo->lock));
	//printf("Duration: %lu\n", time_get_usec() - duration);
	message_status(philo, MSG_EATING);
	philo_sleep(philo, philo->program->time_eat);

	//LET GO FORKS
	munlock(&(philo->fork));
	munlock(&(philo->neighbour->fork));
	if (_check_exit(philo) == 1)
		return ;

	//SLEEP
	message_status(philo, MSG_SLEEPING);
	philo_sleep(philo, philo->program->time_sleep);
}

void	*philo_thread(void *arg)
{
	t_philo		*philo;
	t_program	*program;

	philo = (t_philo *)arg;
	mlock(&(philo->lock));
	program = philo->program;
	if (philo->index % 2 == 1)
		usleep(1000);
	usleep(100 * philo->index);
	munlock(&(philo->lock));
	while (_check_exit(philo) != 1)
	{
		_think(philo);
	}
	printf("END THREAD\n");
	return (NULL);
}
