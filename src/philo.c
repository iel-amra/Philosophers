/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:07:18 by iel-amra          #+#    #+#             */
/*   Updated: 2022/12/16 17:42:51 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	print_msg(char *str, int id)
{
	struct timeval	time;

	gettimeofday(&time, (void *) 0);
	printf("%s %lu%03d %i\n", str, time.tv_sec, time.tv_usec / 1000, id);
}

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
		philo->t->end = -1;
		gettimeofday(&time, (void *) 0);
		printf("%lu%03d %i died\n", time.tv_sec, time.tv_usec / 1000, philo->id);
		pthread_mutex_unlock(&philo->t->m_end);
	}
	if (philo->t->must_eat != -1 && philo->eaten >= philo->t->must_eat)
	{
		pthread_mutex_lock(&philo->t->m_end);
		philo->t->end++;
		philo->eaten = -1;
		pthread_mutex_unlock(&philo->t->m_end);
	}
}

int	forks_take(t_philo *philo, int i)
{
	int		ret;
	struct timeval	time;

	ret = 1;
	pthread_mutex_lock(philo->m_forks[i]);
	if (*philo->forks[i] == 0)
	{
		*philo->forks[i] = philo->id + 1;
		pthread_mutex_unlock(philo->m_forks[i]);
		pthread_mutex_lock(&philo->t->m_end);
		gettimeofday(&time, (void *) 0);
		printf("%lu%03d %i has taken a fork\n", time.tv_sec,
			time.tv_usec / 1000, philo->id);
		pthread_mutex_unlock(&philo->t->m_end);
	}
	else if (*philo->forks[i] != philo->id + 1)
	{
		pthread_mutex_unlock(philo->m_forks[i]);
		ret = 0;
	}
	else
		pthread_mutex_unlock(philo->m_forks[i]);
	return (ret);
}

void	forks_put(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->m_forks[i]);
	*philo->forks[i] = 0;
	pthread_mutex_unlock(philo->m_forks[i]);
}

int	thinking(t_philo *philo)
{
	struct timeval	time;

	if (forks_take(philo, philo->id % 2))
	{
		if (philo->m_forks[0] != philo->m_forks[1] && forks_take(philo, 1 - (philo->id % 2)))
		{
			pthread_mutex_lock(&philo->t->m_end);
			gettimeofday(&time, (void *) 0);
			gettimeofday(&philo->start_eat, (void *) 0);
			pthread_mutex_unlock(&philo->t->m_end);
			return (0);
		}
	return (1);
}

int	eating(t_philo *philo)
{
	struct timeval	*time;

	time = &philo->start_sleep;
	gettimeofday(time, (void *) 0);
	{
		pthread_mutex_lock(&philo->t->m_end);
		gettimeofday(time, (void *) 0);
		printf("%lu%03d %i is sleeping\n", time->tv_sec, time->tv_usec / 1000, philo->id);
		pthread_mutex_unlock(&philo->t->m_end);
		if (philo->eaten != -1)
			philo->eaten++;
		forks_put(philo, 0);
		forks_put(philo, 1);
		return (0);
	}
	return (1);
}

int	sleeping(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, (void *) 0);
	if (time_is_inf(time_add(philo->start_sleep, philo->t->time_to_sleep), time))
	{
		pthread_mutex_lock(&philo->t->m_end);
		gettimeofday(&time, (void *) 0);
		printf("%lu%03d %i is thinking\n", time.tv_sec, time.tv_usec / 1000, philo->id);
		pthread_mutex_unlock(&philo->t->m_end);
		return (0);
	}
	return (1);
}

void	*thread_philo(t_philo *philo)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->t->m_start);
	pthread_mutex_unlock(&philo->t->m_start);
	gettimeofday(&philo->start_eat, (void *) 0);
	pthread_mutex_lock(&philo->t->m_end);
	gettimeofday(&time, (void *) 0);
	printf("%lu%03d %i is thinking\n", time.tv_sec, time.tv_usec / 1000, philo->id);
	pthread_mutex_unlock(&philo->t->m_end);
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
	philo->id = ((i * 2 + (i * 2 > table->nb_philo - 1 && table->nb_philo % 2 == 0))) % table->nb_philo;
	philo->m_forks[0] = table->forks_mutex + philo->id;
	philo->m_forks[1] = table->forks_mutex + ((philo->id + 1) % table->nb_philo);
	philo->forks[0] = table->forks + philo->id;
	philo->forks[1] = table->forks + ((philo->id + 1) % table->nb_philo);
	philo->t = table;
	philo->eaten = 0;
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
	pthread_mutex_unlock(&table->m_start);
	return (0);
}
