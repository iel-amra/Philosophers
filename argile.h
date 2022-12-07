#ifndef PRINCIPAL_H
# define PRINCIPAL_H

# include "../libft/libft.h"
# include <limits.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				*forks[2];
	pthread_mutex_t	*m_forks[2];
	struct timeval 	start_eat;
	struct timeval	start_sleep;
	struct timeval	*time_to_die;
	struct timeval	*time_to_eat;
	struct timeval	*time_to_sleep;
	int				must_eat;
}	t_philo;

typedef struct s_table
{
	t_philo			*philosophers;
	pthread_mutex_t	*forks_mutex;
	int				*forks;
	int				nb_philo;
	struct timeval	time_to_die;
	struct timeval	time_to_eat;
	struct timeval	time_to_sleep;
	int				must_eat;
}	t_table;
