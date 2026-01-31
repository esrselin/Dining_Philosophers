/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:38:17 by esakgul           #+#    #+#             */
/*   Updated: 2026/01/31 19:01:38 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->number_of_philosophers)
	{
		general->philo_data[i].philo_id = i + 1;
		general->philo_data[i].l_fork = &general->forks[i];
		general->philo_data[i].r_fork = &general->forks[(i + 1)
			% general->number_of_philosophers];
		general->philo_data[i].general_data = general;
		pthread_create(&general->all_philos[i], NULL, routine,
			&general->philo_data[i]);
		i++;
	}
}

void	create_forks(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->number_of_philosophers)
	{
		pthread_mutex_init(&general->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&general->print_lock, NULL);
	pthread_mutex_init(&general->is_dead_lock, NULL);
	pthread_mutex_init(&general->meal_lock, NULL);
}

void	creating_monitor(t_general *general)
{
	pthread_create(&general->is_dead_thread, NULL, monitor, general);
}
