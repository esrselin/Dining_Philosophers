/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:10:50 by esakgul           #+#    #+#             */
/*   Updated: 2026/01/31 18:44:26 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo	*phi;

	phi = (t_philo *)philo;
	while (1)
	{
		if (check_dead(phi))
			break ;
		if (take_forks(phi))
			return (NULL);
		eat(phi);
		sleep_think(phi);
	}
	return (NULL);
}

void	*monitor(void *general)
{
	t_general	*gen;

	gen = (t_general *)general;
	while (1)
	{
		if (check_stop(gen))
			return (NULL);
		if (check_death(gen))
			return (NULL);
		if (check_all_full(gen))
			return (NULL);
		usleep(1000);
	}
}
