/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:10:50 by esakgul           #+#    #+#             */
/*   Updated: 2026/02/07 05:37:13 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo		*phi;


	phi = (t_philo *)philo;
	while (1)
	{
		if (take_forks(phi))
			return (NULL);
		if (check_dead(phi))
		{
			pthread_mutex_unlock(phi->l_fork);
			pthread_mutex_unlock(phi->r_fork);
			break ;
		}
		eat_sleep_n_think(phi);
	}
	return (NULL);
}

void	*monitor(void *general)
{
	t_general	*gen;

	/* Monitor, filozofun ne yaptığıyla
	(uyuyor mu,çatal mı bekliyor),
	ilgilenmez. Sadece saate bakar. */
	gen = (t_general *)general;
	while (1)
	{
		if (check_starving(gen))
			return (NULL);
		if (check_all_full(gen))
			return (NULL);
	}
}
