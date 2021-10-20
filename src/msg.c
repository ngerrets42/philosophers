/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msg.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 09:40:43 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/20 16:00:04 by ngerrets      ########   odam.nl         */
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

void	message_status(t_philo *me, t_msg msg)
{
	static int				init = 1;
	static pthread_mutex_t	lock;
	unsigned long			current_time_micro;
	static char				*str[MSG_LAST] =
	{
		[MSG_EATING] = " is now eating. (HAS GRABBED FORKS)\n",
		[MSG_SLEEPING] = " is now sleeping. (HAS RELEASED FORKS)\n",
		[MSG_THINKING] = " is now thinking. (IS WAITING FOR FORKS)\n",
		[MSG_DEATH] = " is now dead.\n"
	};

	if (init != 0)
		init = pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	current_time_micro = time_get_micro() - me->program->start_time;
	putstr("[");
	putstr(ft_itoa(current_time_micro / 1000));
	putstr("] Philosopher ");
	putstr(ft_itoa(me->index + 1));
	putstr(str[msg]);
	pthread_mutex_unlock(&lock);
}