/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <iel-amra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:17:49 by iel-amra          #+#    #+#             */
/*   Updated: 2023/01/07 13:01:32 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINCIPAL_H
# define PRINCIPAL_H

# include "../libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				*forks[2];
	pthread_mutex_t	*m_forks[2];
	int				eaten;
	struct timeval	start_eat;
	struct timeval	start_sleep;
	t_table			*t;
}	t_philo;

struct s_table
{
	t_philo			*philosophers;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	m_end;
	pthread_mutex_t	m_start;
	int				end;
	int				*forks;
	int				nb_philo;
	struct timeval	time_to_die;
	struct timeval	time_to_eat;
	struct timeval	time_to_sleep;
	int				must_eat;
	struct timeval	time_start;
};

int				forks_take(t_philo *philo, int i);
void			forks_put(t_philo *philo, int i);
int				thinking(t_philo *philo);
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);
void			destroy_all_mutex(t_table *table);
void			free_memory(t_table *table);
int				memory_alloc(t_table *table);
int				create_mutex(t_table *table);
int				init(t_table *table, int argc, char **argv);
void			waiting_finish(t_table *table);
int				check_overflow(int argc, char **argv);
int				parse(t_table *table, int argc, char **argv);
int				check_end(t_philo *philo);
void			check_death(t_philo *philo);
int				forks_take(t_philo *philo, int i);
void			forks_put(t_philo *philo, int i);
int				thinking(t_philo *philo);
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);
void			*thread_philo(t_philo *philo);
int				start_one_philo(t_table *table, t_philo *philo, int i);
int				start_philosophers(t_table *table);
int				time_is_inf(struct timeval t1, struct timeval t2);
struct timeval	time_add(struct timeval t1, struct timeval t2);
struct timeval	ms_to_timeval(unsigned long ms);
struct timeval	time_minus(struct timeval t1, struct timeval t2);
void			print_t(char *msg, t_philo *philo);

#endif
