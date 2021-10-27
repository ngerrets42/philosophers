/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msg.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 09:40:43 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/27 14:12:23 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include "str.h"

void	putstr(char *str)
{
	int	l;

	l = 0;
	while (str[l] != '\0')
		l++;
	write(STDOUT_FILENO, str, l * sizeof(char));
}

void	_putstr_free(char *str)
{
	putstr(str);
	free(str);
}

void	_putmsg(char *time, char *index, char *msg)
{
	putstr("[");
	_putstr_free(time);
	putstr("] Philosopher ");
	_putstr_free(index);
	putstr(msg);
}

void	message_status(t_philo *me, t_msg msg)
{
	static int				init = 1;
	static pthread_mutex_t	lock;
	static int				death = 0;
	static char				*str[MSG_LAST] =
	{
		[MSG_EATING] = " is now eating. (HAS GRABBED FORKS)\n",
		[MSG_SLEEPING] = " is now sleeping. (HAS RELEASED FORKS)\n",
		[MSG_THINKING] = " is now thinking. (IS WAITING FOR FORKS)\n",
		[MSG_DEATH] = " is now dead.\n"
	};

	if (init != 0)
		init = pthread_mutex_init(&lock, NULL);
	if (death == 1)
		return ;
	pthread_mutex_lock(&lock);
	_putmsg(ft_itoa((time_get_micro() - me->program->start_time) / 1000),
		ft_itoa(me->index + 1), str[msg]);
	pthread_mutex_unlock(&lock);
	if (msg == MSG_DEATH)
		death = 1;
}
