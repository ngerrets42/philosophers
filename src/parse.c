/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:57:26 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/02/09 14:36:33 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

static int	_argument(int *output, char *src)
{
	int		n;
	char	*str;

	n = ft_atoi(src);
	str = ft_itoa(n);
	if (n < 0 || str == NULL)
		return (ERROR);
	if (_strcmp(str, src) != 0)
	{
		free(str);
		return (ERROR);
	}
	free(str);
	*output = n;
	return (SUCCES);
}

int	parse_input(t_input *input, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ERROR);
	if (_argument(&input->nphilo, argv[1]))
		return (ERROR);
	if (input->nphilo <= 0)
		return (ERROR);
	if (_argument(&input->time_to_die, argv[2]))
		return (ERROR);
	if (_argument(&input->time_to_eat, argv[3]))
		return (ERROR);
	if (_argument(&input->time_to_sleep, argv[4]))
		return (ERROR);
	if (argc == 6 && _argument(&input->amount_to_eat, argv[5]) == ERROR)
		return (ERROR);
	return (SUCCES);
}
