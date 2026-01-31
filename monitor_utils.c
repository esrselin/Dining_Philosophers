/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:41:09 by esakgul           #+#    #+#             */
/*   Updated: 2026/01/31 19:01:10 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop(t_general *gen)
{
	pthread_mutex_lock(&gen->is_dead_lock);
	if (gen->is_dead)
	{
		pthread_mutex_unlock(&gen->is_dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&gen->is_dead_lock);
	return (0);
}

int	check_death(t_general *gen)
{
	int			i;
	long long	last;

	i = 0;
	while (i < gen->number_of_philosophers)
	{
		pthread_mutex_lock(&gen->meal_lock);
		last = gen->philo_data[i].last_meal_time;
		pthread_mutex_unlock(&gen->meal_lock);
		if (now_time() - last > gen->time_to_die)
		{
			set_stop(gen);
			print_dead(&gen->philo_data[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_full(t_general *gen)
{
	int	i;
	int	all_full;

	if (gen->must_eat_count <= 0)
		return (0);
	i = 0;
	all_full = 1;
	while (i < gen->number_of_philosophers)
	{
		pthread_mutex_lock(&gen->meal_lock);
		if (gen->philo_data[i].meal_count < gen->must_eat_count)
			all_full = 0;
		pthread_mutex_unlock(&gen->meal_lock);
		if (!all_full)
			return (0);
		i++;
	}
	set_stop(gen);
	return (1);
}
