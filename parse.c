/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:13:34 by esakgul           #+#    #+#             */
/*   Updated: 2026/01/28 20:27:09 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
void	init_philo(t_general *general, int argc, char **argv)
{
	int	i;

	general->number_of_philosophers = ft_atoi(argv[1]);
	general->time_to_die = ft_atoi(argv[2]);
	general->time_to_eat = ft_atoi(argv[3]);
	general->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		general->must_eat_count = ft_atoi(argv[5]);
	else
		general->must_eat_count = -1;
	general->all_philos = malloc(sizeof(pthread_t)
			* general->number_of_philosophers);
	general->forks = malloc(sizeof(pthread_mutex_t)
			* general->number_of_philosophers);
	general->philo_data = malloc(sizeof(t_philo)
			* general->number_of_philosophers);
	general->start_time = now_time();
	general->is_dead = 0;
	i = 0;
	while (i < general->number_of_philosophers)
	{
		general->philo_data[i].last_meal_time = general->start_time;
		general->philo_data[i].meal_count = 0;
		i++;
	}
	if (!general->all_philos || !general->forks || !general->philo_data)
		return ;
	create_forks(general);
	create_philo(general);
	creating_monitor(general);
}
