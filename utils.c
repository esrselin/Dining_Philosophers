/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:51:08 by esakgul           #+#    #+#             */
/*   Updated: 2026/01/28 21:03:40 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	s;
	int	r;

	s = 1;
	r = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '-')
	{
		s = (-1);
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && '9' >= *str)
	{
		r = (r * 10) + (*str - '0');
		str++;
	}
	return (r * s);
}

void	ft_printf(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->general_data->is_dead_lock);
	if (philo->general_data->is_dead)
	{
		pthread_mutex_unlock(&philo->general_data->is_dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->general_data->is_dead_lock);
	pthread_mutex_lock(&philo->general_data->print_lock);
	printf("%llu %d %s", now_time() - philo->general_data->start_time,
		philo->philo_id, s);
	pthread_mutex_unlock(&philo->general_data->print_lock);
}
void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->general_data->print_lock);
	printf("%lld %d %s", now_time() - philo->general_data->start_time,
		philo->philo_id, "died.\n");
	pthread_mutex_unlock(&philo->general_data->print_lock);
}
void	freendestroy(t_general *general)
{
	int i = 0;
	while (i < general->number_of_philosophers)
	{
		pthread_mutex_destroy(&general->forks[i]);
		i++;
	}

	pthread_mutex_destroy(&general->print_lock);
	pthread_mutex_destroy(&general->is_dead_lock);
	pthread_mutex_destroy(&general->meal_lock);

	free(general->forks);
	free(general->all_philos);
	free(general->philo_data);
	free(general);
}