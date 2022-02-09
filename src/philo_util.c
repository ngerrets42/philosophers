/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:56:57 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/09 14:56:31 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_check_death(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->program->lock);
	dead = philo->program->philo_dead;
	pthread_mutex_unlock(&philo->program->lock);
	return (dead);
}

int	neighbour_id(t_philo *philo)
{
	int	index;

	index = philo->index + 1;
	if (philo->index == philo->program->input.nphilo)
		index = 0;
	return (index);
}
