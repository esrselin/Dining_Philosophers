/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:10:50 by esakgul           #+#    #+#             */
/*   Updated: 2026/01/21 22:02:50 by esakgul          ###   ########.fr       */
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
			
		pthread_create(&general->all_philos[i], NULL, routine,
			&general->philo_data[i]);
			//threade structın kopyasını değil, adresini vermeliyiz.
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
	//mutexleri freele. 
}

void	*routine(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	while (1)
	{
		if (phi->philo_id % 2 == 0)
		{
			pthread_mutex_lock(phi->l_fork);
			printf("llu %d has taken a fork.\n", phi->philo_id);
			pthread_mutex_lock(phi->r_fork); 
			printf("llu %d has taken a fork.\n", phi->philo_id);
		}
		else
		{
			pthread_mutex_lock(phi->r_fork);
			printf("llu %d has taken a fork.\n", phi->philo_id);
			pthread_mutex_lock(phi->l_fork);
			printf("llu %d has taken a fork.\n", phi->philo_id);
		}
		pthread_mutex_unlock(phi->l_fork);
		pthread_mutex_unlock(phi->l_fork);
		
		// eating
		// pthread_mutex_lock(phi->general_data->meal);
		// my_usleep(phi->general_data.time_to_eat);
		// printf("llu %d has is eating.\n", phi->philo_id);
		// pthread_mutex_unlock(phi->general_data->meal);
		// phi->is_death = 1;
		// pthread_mutex_unlock(phi->general_data->meal);
	}
}
