/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_thread.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 17:11:26 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/01 15:54:07 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	_thread_identify(t_philo p)
{
	printf("HI IM PHILO %d\naddr left: %p\naddr right: %p\n",
		p.index, p.fork_l, p.fork_r);
}

void	*philo_thread(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	//_thread_identify(*p);
	if (p->index % 2)
		usleep(1000);
	//usleep(200 * p->index + 1000 * (p->index % 2));
	while (!philo_is_done(p))
	{
		usleep(1000);
		philo_grab_forks(p);
		//if (philo_check_death(p))
		//	break ;
		philo_eat(p);
		//if (philo_is_done(p))
		//	break ;
		philo_sleep(p);
		//if (philo_check_death(p))
		//	break ;
		philo_msg_send(p, MSG_THINKING);
	}
	philo_drop_forks(p);
	return (NULL);
}

t_bool	philo_threads_start(t_program *program)
{
	int		i;
	t_ul	start_time;

	i = 0;
	start_time = time_start_get();
	while (i < program->numb_philo)
	{
		program->philos[i].time_eaten = start_time;
		if (pthread_create(&program->philos[i].thread, NULL,
			&philo_thread, &program->philos[i]) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	philo_threads_join(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->numb_philo)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}