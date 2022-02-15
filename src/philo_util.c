/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:56:57 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/15 13:06:45 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	Checks the philo_dead variable. Nothing special except for a mutex lock to
**	avoid data-races.
*/
int	philo_check_death(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->program->lock);
	dead = philo->program->philo_dead;
	pthread_mutex_unlock(&philo->program->lock);
	return (dead);
}

/*
**	gets the index of the neighbour of giveb philosopher.
**	-	the neighbour is the one that's virtually on the right.
*/
int	neighbour_index(t_philo *philo)
{
	int	index;

	index = philo->index + 1;
	if (philo->index == philo->program->input.nphilo)
		index = 0;
	return (index);
}
