/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/24 11:01:40 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/24 13:02:29 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "time_get.h"

#define STANDARD_SLEEP_TIME 5000

void	philo_sleep(t_philo *philo, useconds_t usec)
{
	int			time_diff;
	useconds_t	time_last;
	useconds_t	time_now;
	useconds_t	time_to_sleep;

	time_diff = 0;
	time_last = time_get_usec();
	while (1)
	{
		//printf("...sleeping... philo %d usec = %u\n", philo->index, usec);
		time_to_sleep = STANDARD_SLEEP_TIME - time_diff;
		if (usec < STANDARD_SLEEP_TIME)
			time_to_sleep = usec;
		//mlock(&(philo->lock));
		usleep(time_to_sleep);
		//munlock(&(philo->lock));
		if (usec < STANDARD_SLEEP_TIME)
			break ;
		time_now = time_get_usec();
		if (time_now - time_last > usec)
			break ;
		usec -= time_now - time_last;
		time_diff = time_now - time_last - time_to_sleep;
		time_last = time_now;
	}
	//printf("...done sleeping... philo %d\n", philo->index);
}

void	_think(t_philo *philo)
{
	printf("Philo %d thinking...\n", philo->index);
	//GET FORKS
	mlock(&(philo->fork));
	mlock(&(philo->neighbour->fork));


	//EAT
	printf("Philo %d eating...\n", philo->index);
	philo_sleep(philo, philo->program->time_eat);

	//LET GO FORKS
	munlock(&(philo->fork));
	munlock(&(philo->neighbour->fork));

	//SLEEP
	printf("Philo %d sleeping...\n", philo->index);
	philo_sleep(philo, philo->program->time_sleep);
}

static int	_check_exit(t_program *program)
{
	int	r;

	mlock(&(program->lock));
	r = program->exit;
	munlock(&(program->lock));
	return (r);
}

void	*philo_thread(void *arg)
{
	t_philo		*philo;
	t_program	*program;

	//usleep(10000);
	philo = (t_philo *)arg;
	mlock(&(philo->lock));
	program = philo->program;
	if (philo->index % 2 == 1)
		usleep(1000);
	munlock(&(philo->lock));
	while (_check_exit(philo->program) != 1)
	{
		_think(philo);
	}
	return (NULL);
}
