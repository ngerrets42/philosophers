/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   program.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 11:22:12 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/13 11:51:15 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_H
# define PROGRAM_H

# include <stddef.h>
# include <stdlib.h>
# include "nerror.h"

typedef struct s_program
{
	int				philo_amount;
	int				turn;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				eat_amount;
	unsigned long	start_time;
}					t_program;

t_program		*program_get(void);
t_program		*program_parse(int argc, char **argv);
void			program_destroy(void);
unsigned long	time_get_micro(void);

int				parse_int(char *str);

#endif
