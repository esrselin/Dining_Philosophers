/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:25:54 by esakgul           #+#    #+#             */
/*   Updated: 2026/01/31 19:24:18 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_general	*general;
	int			i;

	general = malloc(sizeof(t_general));
	if (!general)
		return (1);
	if (parse(argc, argv))
		return (1);
	init_philo(general, argc, argv);
	i = 0;
	while (i < general->number_of_philosophers)
		pthread_join(general->all_philos[i++], NULL);
	pthread_join(general->is_dead_thread, NULL);
	freendestroy(general);
	return (0);
}
