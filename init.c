/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:53:25 by esakgul           #+#    #+#             */
/*   Updated: 2026/01/31 19:00:30 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_general_data(t_general *gen, int argc, char **argv)
{
	gen->number_of_philosophers = ft_atoi(argv[1]);
	gen->time_to_die = ft_atoi(argv[2]);
	gen->time_to_eat = ft_atoi(argv[3]);
	gen->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		gen->must_eat_count = ft_atoi(argv[5]);
	else
		gen->must_eat_count = -1;
	gen->is_dead = 0;
	gen->start_time = now_time();
}

int	allocate_memory(t_general *gen)
{
	gen->all_philos = malloc(sizeof(pthread_t) * gen->number_of_philosophers);
	gen->forks = malloc(sizeof(pthread_mutex_t) * gen->number_of_philosophers);
	gen->philo_data = malloc(sizeof(t_philo) * gen->number_of_philosophers);
	if (!gen->all_philos || !gen->forks || !gen->philo_data)
		return (1);
	return (0);
}

void	init_philo_data(t_general *gen)
{
	int	i;

	i = 0;
	while (i < gen->number_of_philosophers)
	{
		gen->philo_data[i].last_meal_time = gen->start_time;
		gen->philo_data[i].meal_count = 0;
		i++;
	}
}

void	init_philo(t_general *general, int argc, char **argv)
{
	fill_general_data(general, argc, argv);
	if (allocate_memory(general))
		return ;
	init_philo_data(general);
	create_forks(general);
	create_philo(general);
	creating_monitor(general);
}
