/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   program.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 11:22:12 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/04 15:13:42 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_H
# define PROGRAM_H

# include <stddef.h>
# include <stdlib.h>
# include "nerror.h"

typedef struct s_program
{
	int	philo_amount;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_amount;
}		t_program;

t_program	*program_get(void);
t_program	*program_parse(int argc, char **argv);
void		program_destroy(void);

int			parse_int(char *str);

#endif
