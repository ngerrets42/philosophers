/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/05 20:34:57 by mraasvel      #+#    #+#                 */
/*   Updated: 2022/02/01 16:56:14 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Input is sanitized by converting to string and back
*/

static int	parse_arg(int *dst, char *src)
{
	int		n;
	char	*temp;

	n = ft_atoi(src);
	if (n < 0)
		return (ERROR);
	temp = ft_itoa(n);
	if (temp == NULL)
		return (ERROR);
	if (ft_strcmp(temp, src) != 0)
	{
		free(temp);
		return (ERROR);
	}
	free(temp);
	*dst = n;
	return (SUCCES);
}

int	parse_input(t_input *input, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ERROR);
	if (parse_arg(&input->amount_philo, argv[1]))
		return (ERROR);
	if (parse_arg(&input->time_to_die, argv[2]))
		return (ERROR);
	if (parse_arg(&input->time_to_eat, argv[3]))
		return (ERROR);
	if (parse_arg(&input->time_to_sleep, argv[4]))
		return (ERROR);
	if (argc == 6)
		if (parse_arg(&input->amount_to_eat, argv[5]) == ERROR)
			return (ERROR);
	if (input->amount_philo <= 0)
		return (ERROR);
	return (SUCCES);
}
