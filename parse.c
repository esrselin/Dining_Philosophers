/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:13:34 by esakgul           #+#    #+#             */
/*   Updated: 2026/02/04 15:46:13 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	s;
	int	r;

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

static int	is_digit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	is_zero(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) == 0)
		{
			printf("Error: Argument must be higher than zero.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac < 5 || ac > 6)
		return (1);
	if (is_zero(av))
		return (1);
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!is_digit(av[i][j]) && av[i][j] != '+')
			{
				printf("Error: Invalid argument '%s'\n", av[i]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
