/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 15:16:29 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/20 15:54:37 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	**_structs_destroy(t_philo **p_array, int i)
{
	while (i > 0)
	{
		i--;
		philosopher_destroy(p_array[i]);
	}
	return (NULL);
}

static t_philo	**_philosophers_init(t_program *program)
{
	t_philo	**p_array;
	t_philo	*neighbour;
	int		i;

	neighbour = NULL;
	p_array = malloc(sizeof(t_philo *) * program->philo_amount);
	if (p_array == NULL)
		return (NULL);
	i = 0;
	while (i < program->philo_amount)
	{
		p_array[i] = philosopher_create(program, i);
		p_array[i]->neighbour = neighbour;
		neighbour = p_array[i];
		if (p_array[i] == NULL)
			return (_structs_destroy(p_array, i));
		i++;
	}
	p_array[0]->neighbour = p_array[i - 1];
	return (p_array);
}

t_status	*_status_array(int amount)
{
	t_status	*s_array;
	int			i;

	s_array = malloc(sizeof(t_status) * amount);
	if (s_array == NULL)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		s_array[i] = S_THINKING;
		i++;
	}
	return (s_array);
}

void	philosophers_start(t_program *program)
{
	t_philo		**p_array;
	t_status	*s_array;
	int			i;
	unsigned long	current_time;

	p_array = _philosophers_init(program);
	if (p_array == NULL)
	{
		//throw error
		return ;
	}
	s_array = _status_array(program->philo_amount);
	if (s_array == NULL)
	{
		//throw error
		return ;
	}
	while (1)
	{
		i = 0;
		current_time = time_get_micro();
		while (i < program->philo_amount)
		{
			program->turn = i;
			if (p_array[i]->time_of_death < current_time)
			{
				//p_array[i]->status = S_DEAD;
				message_status(p_array[i], MSG_DEATH);
				exit(1);
				free(s_array);
				_structs_destroy(p_array, program->philo_amount);
				return ;
			}
			if (program->eat_amount > 0 && p_array[i]->times_eaten >= program->eat_amount)
			{
				free(s_array);
				_structs_destroy(p_array, program->philo_amount);
				return ;
			}
			i++;
		}
	}
	free(s_array);
	_structs_destroy(p_array, program->philo_amount);
}
