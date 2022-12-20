#ifndef PRINCIPAL_H
# define PRINCIPAL_H

# include "../libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_table t_table;

typedef struct s_philo
{
	int		id;
	pthread_t	thread;
	int		*forks[2];
	pthread_mutex_t	*m_forks[2];
	int		eaten;
	struct timeval 	start_eat;
	struct timeval	start_sleep;
	t_table		*t;
}	t_philo;

typedef struct s_table
{
	t_philo		*philosophers;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	m_end;
	pthread_mutex_t m_start;
	int		end;
	int		*forks;
	int		nb_philo;
	struct timeval	time_to_die;
	struct timeval	time_to_eat;
	struct timeval	time_to_sleep;
	int		must_eat;
	struct timeval	time_start;
}	t_table;
