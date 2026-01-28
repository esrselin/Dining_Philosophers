/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:10:50 by esakgul           #+#    #+#             */
/*   Updated: 2026/01/28 12:04:08 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo(t_general *general)
{
	int	i;

	// printf("%d\n", general->time_to_sleep);
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
	pthread_mutex_init(&general->print_lock, NULL);
	pthread_mutex_init(&general->is_dead_lock, NULL);
	pthread_mutex_init(&general->meal_lock, NULL);
	// mutexleri freele(?)
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
		pthread_mutex_lock(&phi->general_data->is_dead_lock);
		if (phi->general_data->is_dead == 1)
		{
			pthread_mutex_unlock(&phi->general_data->is_dead_lock);
			break ;
		}
		pthread_mutex_unlock(&phi->general_data->is_dead_lock);
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
		pthread_mutex_lock(&phi->general_data->meal_lock);
		phi->last_meal_time = now_time();
		pthread_mutex_unlock(&phi->general_data->meal_lock);
		ft_printf(phi, "is eating.\n");
		my_sleep(phi->general_data->time_to_eat);
		pthread_mutex_unlock(phi->l_fork);
		pthread_mutex_unlock(phi->r_fork);
		ft_printf(phi, "is sleeping.\n");
		my_sleep(phi->general_data->time_to_sleep);
		ft_printf(phi, "is thinking.\n");
	}
	return (NULL);
}

void	creating_monitor(t_general *general)
{
	pthread_create(&general->is_dead_thread, NULL, monitor, general);
}
static void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->general_data->print_lock);
	printf("%lld %d %s", now_time() - philo->general_data->start_time,
		philo->philo_id, "died.\n");
	pthread_mutex_unlock(&philo->general_data->print_lock);
}
void	*monitor(void *general)
{
	t_general	*gen;
	int			i;
			long long last;

	gen = (t_general *)general;
	while (1)
	{
		i = 0;
		while (i < gen->number_of_philosophers)
		{
			pthread_mutex_lock(&gen->is_dead_lock);
			if (gen->is_dead)
			{
				pthread_mutex_unlock(&gen->is_dead_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&gen->is_dead_lock);
			// last_meal_time okumasını meal_lock ile koru
			pthread_mutex_lock(&gen->meal_lock);
			last = gen->philo_data[i].last_meal_time;
			pthread_mutex_unlock(&gen->meal_lock);
			if (now_time() - last > gen->time_to_die)
			{
				pthread_mutex_lock(&gen->is_dead_lock);
				gen->is_dead = 1;
				pthread_mutex_unlock(&gen->is_dead_lock);
				print_dead(&gen->philo_data[i]);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
}
