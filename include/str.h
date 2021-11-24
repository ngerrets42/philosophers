/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 11:06:18 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/11/24 15:21:36 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <unistd.h>
# include <stdlib.h>

int		ft_atoi(const char *str);
void	putstr(const char *str);
char	*ft_itoa(int n);

#endif
