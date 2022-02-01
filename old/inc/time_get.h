/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_get.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:31:57 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/17 11:37:45 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_GET_H
# define TIME_GET_H

# include <sys/time.h>

unsigned long	time_get_msec(void);
unsigned long	time_get_usec(void);
unsigned long	time_start_get(void);

#endif
