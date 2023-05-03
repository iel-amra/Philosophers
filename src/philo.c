/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:07:18 by iel-amra          #+#    #+#             */
/*   Updated: 2023/01/07 15:22:08 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_end(t_philo *philo)
{
	usleep(10 * philo->t->nb_philo);
	pthread_mutex_lock(&philo->t->m_end);
	if (philo->t->end == -1 || philo->t->end == philo->t->nb_philo)
	{	
		pthread_mutex_unlock(&philo->t->m_end);
		return (1);
	}
	pthread_mutex_unlock(&philo->t->m_end);
	return (0);
}

void	check_death(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, (void *) 0);
	if (time_is_inf(time_add(philo->start_eat, philo->t->time_to_die), time))
	{
		pthread_mutex_lock(&philo->t->m_end);
		print_t("died", philo);
		philo->t->end = -1;
		gettimeofday(&time, (void *) 0);
		pthread_mutex_unlock(&philo->t->m_end);
	}
}

void	*thread_philo(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->t->m_start);
	pthread_mutex_unlock(&philo->t->m_start);
	gettimeofday(&philo->start_eat, (void *) 0);
	pthread_mutex_lock(&philo->t->m_end);
	gettimeofday(&time, (void *) 0);
	print_t("is thinking", philo);
	pthread_mutex_unlock(&philo->t->m_end);
	if (philo->id % 2 != 1)
		usleep(10000);
	while (!check_end(philo))
	{	
		while (!check_end(philo) && thinking(philo))
			check_death(philo);
		while (!check_end(philo) && eating(philo))
			check_death(philo);
		while (!check_end(philo) && sleeping(philo))
			check_death(philo);
	}
	return ((void *) 0);
}	

int	start_one_philo(t_table *table, t_philo *philo, int i)
{
	philo->id = ((i * 2 + (i * 2 > table->nb_philo - 1
					&& table->nb_philo % 2 == 0))) % table->nb_philo;
	philo->m_forks[0] = table->forks_mutex + philo->id;
	philo->m_forks[1] = table->forks_mutex + ((philo->id + 1)
			% table->nb_philo);
	philo->forks[0] = table->forks + philo->id;
	philo->forks[1] = table->forks + ((philo->id + 1) % table->nb_philo);
	philo->t = table;
	philo->eaten = 0;
	if (philo->t->must_eat == -1)
		philo->eaten = -1;
	pthread_create(&philo->thread, (void *) 0, (void *) thread_philo, philo);
	return (0);
}

int	start_philosophers(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->m_start);
	while (i < table->nb_philo)
	{
		if (start_one_philo(table, table->philosophers + i, i))
		{
			ft_dprintf(2, "Thread init Error\n");
			return (1);
		}
		i++;
	}
	gettimeofday(&table->time_start, (void *) 0);
	pthread_mutex_unlock(&table->m_start);
	return (0);
}
