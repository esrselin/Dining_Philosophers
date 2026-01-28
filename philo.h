#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_general
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	pthread_t			*all_philos;
	pthread_mutex_t		*forks;
	struct s_philo		*philo_data;
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
	struct s_general	*general_data;
}						t_philo;

int						parse(int ac, char **av);
int						ft_atoi(const char *str);
void					init_philo(t_general *general, int argc, char **argv);
void					*routine(void *philo);
void					create_philo(t_general *general);
void					create_forks(t_general *general);
void					my_sleep(int time);
long long				now_time(void);
void					ft_printf(t_philo *philo, char *s);
void					*monitor(void *general);
void					creating_monitor(t_general *general);
void					print_dead(t_philo *philo);
void					freendestroy(t_general *general);
#endif