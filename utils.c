/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:51:08 by esakgul           #+#    #+#             */
/*   Updated: 2026/02/04 16:15:25 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	now_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	my_sleep(int time)
{
	long long	dest_time;

	dest_time = now_time() + time;
	while (now_time() < dest_time)
		usleep(100);
}
void	ft_printf(t_philo *philo, char *s)
{
	if (check_dead(philo))
		return ;
	pthread_mutex_lock(&philo->general_data->print_lock);
	printf("%llu ms %d %s\n", now_time() - philo->general_data->start_time,
		philo->philo_id, s);
	pthread_mutex_unlock(&philo->general_data->print_lock);
}

void	set_stop(t_general *gen)
{
	pthread_mutex_lock(&gen->is_dead_lock);
	gen->is_dead = 1;
	pthread_mutex_unlock(&gen->is_dead_lock);
}

void	freendestroy(t_general *general)
{
	int	i;

	i = 0;
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
