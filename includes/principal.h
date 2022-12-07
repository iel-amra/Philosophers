#ifndef PRINCIPAL_H
# define PRINCIPAL_H

# include "../libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				*forks[2];
	pthread_mutex_t	*m_forks[2];
	pthread_mutex_t *m_end;
	int				*end;
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
	pthread_mutex_t	m_end;
	int				end;
	int				*forks;
	int				nb_philo;
	struct timeval	time_to_die;
	struct timeval	time_to_eat;
	struct timeval	time_to_sleep;
	int				must_eat;
}	t_table;
void			destroy_all_mutex(t_table *table);
void			free_memory(t_table *table);
int				memory_alloc(t_table *table);
int				create_forks(t_table *table);
int				init(t_table *table, int argc, char **argv);
int				check_overflow(int argc, char **argv);
int				parse(t_table *table, int argc, char **argv);
int				start_one_philo(t_table *table, t_philo *philo, int i);
int				start_philosophers(t_table *table);
int				time_is_inf(struct timeval t1, struct timeval t2);
struct timeval			time_add(struct timeval t1, struct timeval t2);
struct timeval			ms_to_timeval(unsigned long ms);

#endif
