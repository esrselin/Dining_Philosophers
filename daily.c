/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:10:50 by esakgul           #+#    #+#             */
/*   Updated: 2026/01/24 04:36:00 by esakgul          ###   ########.fr       */
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
		// threade structın kopyasını değil, adresini vermeliyiz.
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
	pthread_mutex_init(general->print_lock, NULL);
	// mutexleri freele.
}
/*
al → ye → bırak → uyu → düşün → tekrar dene

*/

void	*routine(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	while (1)
	{
		if (phi->philo_id % 2 == 0)
		{
			pthread_mutex_lock(phi->l_fork);
			ft_printf(phi, "has taken a fork.\n");
			pthread_mutex_lock(phi->r_fork);
			ft_printf(phi, "has taken a fork.\n");
		}
		else
		{
			pthread_mutex_lock(phi->r_fork);
			ft_printf(phi, "has taken a fork.\n");
			pthread_mutex_lock(phi->l_fork);
			ft_printf(phi, "has taken a fork.\n");
		}
		phi->last_meal_time = now_time();
		ft_printf(phi, "is eating.\n");
		my_sleep(phi->general_data->time_to_eat);
		pthread_mutex_unlock(phi->l_fork);
		pthread_mutex_unlock(phi->r_fork);
		ft_printf(phi, "is sleeping.\n");
		my_sleep(phi->general_data->time_to_sleep);
		ft_printf(phi, "is thinking.\n");
	}
}
