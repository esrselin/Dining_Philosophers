/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:41:09 by esakgul           #+#    #+#             */
/*   Updated: 2026/02/07 05:38:30 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *phi)
{
	if (phi->general_data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(phi->r_fork);
		ft_printf(phi, "has taken a fork.");
		my_sleep(phi->general_data->time_to_die);
		pthread_mutex_unlock(phi->r_fork);
		return (1);
	}
	if (phi->philo_id % 2 == 0)
	{
		pthread_mutex_lock(phi->l_fork);
		pthread_mutex_lock(phi->r_fork);
	}
	else
	{
		pthread_mutex_lock(phi->r_fork);
		pthread_mutex_lock(phi->l_fork);
	}
	ft_printf(phi, "has taken a fork.");
	ft_printf(phi, "has taken a fork.");
	return (0);
}

void	eat_sleep_n_think(t_philo *phi)
{
	long long	thinking_time;

	pthread_mutex_lock(&phi->general_data->meal_lock);
	phi->last_meal_time = now_time();
	pthread_mutex_unlock(&phi->general_data->meal_lock);
	ft_printf(phi, "is eating.");
	pthread_mutex_lock(&phi->general_data->meal_lock);
	phi->meal_count++;
	pthread_mutex_unlock(&phi->general_data->meal_lock);
	my_sleep(phi->general_data->time_to_eat);
	pthread_mutex_unlock(phi->l_fork);
	pthread_mutex_unlock(phi->r_fork);
	ft_printf(phi, "is sleeping.");
	my_sleep(phi->general_data->time_to_sleep);
	ft_printf(phi, "is thinking.");
	my_sleep(1);
}

int	check_dead(t_philo *phi)
{
	pthread_mutex_lock(&phi->general_data->is_dead_lock);
	if (phi->general_data->is_dead)
	{
		pthread_mutex_unlock(&phi->general_data->is_dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&phi->general_data->is_dead_lock);
	return (0);
}

int	check_starving(t_general *gen)
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
			/*
			printf ile set_stop'un yerini değiştirdik.
			Mesajı yazdırdığım o mikrosaniyede
			is_dead hala 0 olacağı için ft_printf içindeki
			en üstteki check_dead engeline takılmayacak.
			Mesaj ekrana basılacak,
			hemen sonra bayrak kalkacak ve diğer herkes susacak.
			*/
			ft_printf(&gen->philo_data[i], "died.");
			set_stop(gen);
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
