/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:07:37 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/17 11:29:16 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H

# include "str.h"

# define SUCCESS 0
# define FAILURE 1

typedef unsigned long t_ulong;

typedef struct s_program
{
	int		n_philos;
	int		n_eat;
	t_ulong	time_die;
	t_ulong	time_eat;
	t_ulong	time_sleep;
}			t_program;

t_program	*program_alloc(void);
int			program_free(t_program *program);
int			parse(t_program *program, int argc, char **argv);

#endif
