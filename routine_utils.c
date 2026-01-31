/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:35:34 by esakgul           #+#    #+#             */
/*   Updated: 2026/02/01 01:19:35 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *phi)
{
	pthread_mutex_lock(&phi->general_data->is_dead_lock);
	if (phi->general_data->is_dead == 1)
	{
		pthread_mutex_unlock(&phi->general_data->is_dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&phi->general_data->is_dead_lock);
	return (0);
}

int	take_forks(t_philo *phi)
{
	if (phi->general_data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(phi->r_fork);
		ft_printf(phi, "has taken a fork.\n");
		my_sleep(phi->general_data->time_to_die);
		pthread_mutex_unlock(phi->r_fork);
		pthread_mutex_lock(&phi->general_data->is_dead_lock);
		phi->general_data->is_dead = 1;
		pthread_mutex_unlock(&phi->general_data->is_dead_lock);
		return (1);
	}
	if (phi->philo_id % 2 == 0)
	{
		my_sleep(phi->general_data->time_to_eat / 10);
		pthread_mutex_lock(phi->l_fork);
		ft_printf(phi, "has taken a fork.\n");
		pthread_mutex_lock(phi->r_fork);
	}
	else
	{
		pthread_mutex_lock(phi->r_fork);
		ft_printf(phi, "has taken a fork.\n");
		pthread_mutex_lock(phi->l_fork);
	}
	return (ft_printf(phi, "has taken a fork.\n"), 0);
}

void	eat(t_philo *phi)
{
	pthread_mutex_lock(&phi->general_data->meal_lock);
	phi->last_meal_time = now_time();
	pthread_mutex_unlock(&phi->general_data->meal_lock);
	ft_printf(phi, "is eating.\n");
	pthread_mutex_lock(&phi->general_data->meal_lock);
	phi->meal_count++;
	pthread_mutex_unlock(&phi->general_data->meal_lock);
	my_sleep(phi->general_data->time_to_eat);
	pthread_mutex_unlock(phi->l_fork);
	pthread_mutex_unlock(phi->r_fork);
}

void	sleep_think(t_philo *phi)
{
	ft_printf(phi, "is sleeping.\n");
	my_sleep(phi->general_data->time_to_sleep);
	ft_printf(phi, "is thinking.\n");
}
