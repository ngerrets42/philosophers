/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msg.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 09:40:43 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/24 15:54:14 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include "str.h"

static void	_putstr_free(char *str)
{
	putstr(str);
	free(str);
}

static void	_putmsg(char *time, char *index, char *msg)
{
	putstr("[");
	_putstr_free(time);
	putstr("] Philosopher ");
	_putstr_free(index);
	putstr(msg);
}

void	message_status(t_philo *me, t_msg msg)
{
	static pthread_mutex_t	lock;
	static char				*str[MSG_LAST] =
	{
		[MSG_EATING] = " is now eating.\n",
		[MSG_SLEEPING] = " is now sleeping.\n",
		[MSG_THINKING] = " is now thinking.\n",
		[MSG_DEATH] = " is now dead.\n"
	};

	if (me == NULL)
	{
		pthread_mutex_init(&lock, NULL);
		return ;
	}
	mlock(&(me->program->lock));
	if (me->program->exit == 0)
	{
		pthread_mutex_lock(&lock);
		_putmsg(ft_itoa((time_get_usec() - me->program->starttime) / 1000),
			ft_itoa(me->index + 1), str[msg]);
		pthread_mutex_unlock(&lock);
	}
	munlock(&(me->program->lock));
}
