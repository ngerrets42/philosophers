/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nerror.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/08 11:24:37 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/10/04 15:05:53 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NERROR_H
# define NERROR_H

# define SPECIFIC_ERROR 1

# include <unistd.h>
# include <stdlib.h>

typedef enum e_error
{
	ERR_MALLOC = 0,
	ERR_DEFAULT
}	t_error;

void	error(t_error err);

#endif
