#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_general
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	int					mutex_lock;
	pthread_t			*all_philos;
	pthread_mutex_t		*forks;
	struct s_philo		*philo_data;

}						t_general;

typedef struct s_philo
{
	pthread_mutex_t		meal;
	int					philo_id;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	struct s_general	*general_data;
}						t_philo;

int						parse(int ac, char **av);
int						ft_atoi(const char *str);
void					init_philo(int argc, char **argv);
void					*routine(void *philo);
void					create_philo(t_general *general);
void					create_forks(t_general *general);
#endif