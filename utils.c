/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:51:08 by esakgul           #+#    #+#             */
/*   Updated: 2026/01/09 20:56:59 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int s;
	int r;

	s = 1;
	r = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-')
	{
		s = (-1);
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && '9' >= *str)
	{
		r = (r * 10) + (*str - '0');
		str++;
	}
	return (r * s);
}