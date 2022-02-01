/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 17:43:34 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/01 15:36:36 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_msg_send(t_philo *p, t_msg m)
{
	t_program		*program;
	static t_bool	end = FALSE;

	static char				*str[MSG_LAST] =
	{
		[MSG_EATING] = "is now eating",
		[MSG_SLEEPING] = "is now sleeping",
		[MSG_THINKING] = "is now thinking",
		[MSG_DEATH] = "is now dead",
		[MSG_FORK_L] = "picked up left fork",
		[MSG_FORK_R] = "picked up right fork"
	};

	if (end == TRUE)
		return ;
	program = (t_program *)p->program;
	pthread_mutex_lock(&program->lock);
	if (program->death == TRUE)
	{
		end = TRUE;
	}
	printf("[%lu] Philosopher %d %s.\n", time_get_msec() - (time_start_get() / 1000),
		p->index + 1, str[m]);
	pthread_mutex_unlock(&program->lock);
}

t_bool	philo_can_i_eat(t_philo *p)
{
	t_program	*program;
	t_bool		can_i;
	int			sets;
	int			i;
	int			x;

	can_i = FALSE;
	program = (t_program *)(p->program);
	pthread_mutex_lock(&program->lock);
	
	sets = program->numb_philo / 2;
	i = 0;
	while (i <= sets)
	{
		x = p->index + i * sets;
		while (x >= program->numb_philo)
			x -= program->numb_philo;
		if (program->times_eaten_total % program->numb_philo == x)
		{
			can_i = TRUE;
			break;
		}
		i++;
	}
	pthread_mutex_unlock(&((t_program *)(p->program))->lock);
	return (can_i);
}

void	philo_grab_forks(t_philo *p)
{
	//ONLY GRAB FORKS IF ITS YOUR TURN
	// while (TRUE)
	// {
	// 	if (philo_check_death(p))
	// 		return ;
	// 	if (philo_can_i_eat(p))
	// 		break ;
	// 	usleep(1000);
	// }
	if (p->index % 2)
	{
		pthread_mutex_lock(p->fork_l);
		philo_msg_send(p, MSG_FORK_L);
		pthread_mutex_lock(p->fork_r);
		philo_msg_send(p, MSG_FORK_R);
	}
	else
	{
		pthread_mutex_lock(p->fork_r);
		philo_msg_send(p, MSG_FORK_R);
		pthread_mutex_lock(p->fork_l);
		philo_msg_send(p, MSG_FORK_L);
	}
}

void	philo_drop_forks(t_philo *p)
{
	if (p->index % 2)
	{
		pthread_mutex_unlock(p->fork_l);
		pthread_mutex_unlock(p->fork_r);
	}
	else
	{
		pthread_mutex_unlock(p->fork_r);
		pthread_mutex_unlock(p->fork_l);
	}
}

void	philo_eat(t_philo *p)
{
	philo_msg_send(p, MSG_EATING);
	p->time_eaten = time_get_usec();
	(p->numb_eaten)++;
	//UPDATE TIMES EATEN
	/*pthread_mutex_lock(&((t_program *)(p->program))->lock);
	if (((t_program *)(p->program))->times_eaten < p->numb_eaten)
		((t_program *)(p->program))->times_eaten += 1;
	pthread_mutex_unlock(&((t_program *)(p->program))->lock);*/
	philo_usleep(p, ((t_program *)(p->program))->time_eat);
	philo_drop_forks(p);
}

void	philo_sleep(t_philo *p)
{
	philo_msg_send(p, MSG_SLEEPING);
	philo_usleep(p, ((t_program *)(p->program))->time_sleep);
}
