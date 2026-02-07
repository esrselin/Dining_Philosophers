/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:53:25 by esakgul           #+#    #+#             */
/*   Updated: 2026/02/07 05:38:55 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fill_general_data(t_general *gen, int argc, char **argv)
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
	gen->all_philos = malloc(sizeof(pthread_t) * gen->number_of_philosophers);
	gen->forks = malloc(sizeof(pthread_mutex_t) * gen->number_of_philosophers);
	gen->philo_data = malloc(sizeof(t_philo) * gen->number_of_philosophers);
	if (!gen->all_philos || !gen->forks || !gen->philo_data)
		return (1);
	return (0);
}
void	create_all(t_general *general)
{
	int	i;

	pthread_mutex_init(&general->print_lock, NULL);
	pthread_mutex_init(&general->is_dead_lock, NULL);
	pthread_mutex_init(&general->meal_lock, NULL);
	pthread_create(&general->is_dead_thread, NULL, monitor, general);
	i = 0;
	while (i < general->number_of_philosophers)
	{
		general->philo_data[i].philo_id = i + 1;
		general->philo_data[i].l_fork = &general->forks[i];
		general->philo_data[i].r_fork = &general->forks[(i + 1)
			% general->number_of_philosophers];
		general->philo_data[i].last_meal_time = general->start_time;
		general->philo_data[i].meal_count = 0;
		general->philo_data[i].general_data = general;
		pthread_mutex_init(&general->forks[i], NULL);
		pthread_create(&general->all_philos[i], NULL, routine,
			&general->philo_data[i]);
		i++;
	}
}

void	init_philo(t_general *general, int argc, char **argv)
{
	if (fill_general_data(general, argc, argv))
		return ;
	create_all(general);
}
