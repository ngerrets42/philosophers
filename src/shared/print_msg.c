/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_msg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/03 16:03:23 by mraasvel      #+#    #+#                 */
/*   Updated: 2022/02/01 16:57:37 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putstr_fd(int fd, char *str)
{
	return ((int)(write(fd, str, ft_strlen(str))));
}

void	message(t_philo *philo, t_msg msg)
{
	static const char	*msgs[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	pthread_mutex_lock(&philo->program->lock);
	if (!philo->program->philo_dead)
	{
		printf("%ld %d %s\n",
			time_difference(philo->program->start_time), philo->id, msgs[msg]);
		if (msg == MSG_DEAD)
			philo->program->philo_dead = true;
	}
	pthread_mutex_unlock(&philo->program->lock);
}
