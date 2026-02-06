/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:03:14 by esakgul           #+#    #+#             */
/*   Updated: 2026/02/07 00:39:15 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_general
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	pthread_t			*all_philos;
	pthread_mutex_t		*forks;
	t_philo				*philo_data;
	pthread_t			is_dead_thread;
	long long			start_time;
	int					is_dead;
	pthread_mutex_t		is_dead_lock;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		meal_lock;
}						t_general;

typedef struct s_philo
{
	int					philo_id;
	int					meal_count;
	long long			last_meal_time;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	t_general			*general_data;
}						t_philo;

int						parse(int ac, char **av);
int						ft_atoi(const char *str);

void					init_philo(t_general *general, int argc, char **argv);
int						fill_general_data(t_general *gen, int argc,
							char **argv);
void					create_all(t_general *general);

long long				now_time(void);
void					my_sleep(int time);

int						check_dead(t_philo *phi);
int						take_forks(t_philo *phi);
void					eat_sleep_n_think(t_philo *phi);

void					*routine(void *philo);
void					*monitor(void *general);
int						check_dead(t_philo *phi);
int						check_stop(t_general *gen);
int						check_starving(t_general *gen);
int						check_all_full(t_general *gen);
void					set_stop(t_general *gen);

void					ft_printf(t_philo *philo, char *s);

void					freendestroy(t_general *general);

#endif
