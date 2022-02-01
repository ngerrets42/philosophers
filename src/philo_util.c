/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/08 14:56:17 by mraasvel      #+#    #+#                 */
/*   Updated: 2022/02/01 16:54:20 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	right_index(t_philo *philo)
{
	int	index;

	index = philo->id;
	if (philo->id == philo->program->input.amount_philo)
		index = 0;
	return (index);
}

int	left_index(t_philo *philo)
{
	return (philo->id - 1);
}
