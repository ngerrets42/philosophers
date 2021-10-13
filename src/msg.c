/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msg.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 09:40:43 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/13 10:36:37 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>
void	message_status(t_philo *me)
{
	unsigned long	current_time_micro;

	static char	*str[S_DEAD + 1] =
	{
		[S_EATING] = "is now eating",
		[S_SLEEPING] = "is now sleeping",
		[S_THINKING] = "is now thinking",
		[S_DEAD] = "is now dead"
	};

	current_time_micro = time_get_micro() - me->program->start_time;
	printf("[%lu] [%d] %s\n", current_time_micro / 1000,
		me->index + 1, str[me->status]);
}