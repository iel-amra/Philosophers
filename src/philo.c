/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:07:18 by iel-amra          #+#    #+#             */
/*   Updated: 2022/12/06 17:07:27 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_end(t_philo *philo)
{
	pthread_mutex_lock(philo->m_end);
	if (*philo->end == 1)
	{
		pthread_mutex_unlock(philo->m_end);
		return (1);
	}
	pthread_mutex_unlock(philo->m_end);
	return (0);
}

void	check_death(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, (void *) 0);
	if (time_is_inf(time_add(philo->start_eat, *philo->time_to_die), time))
	{
		pthread_mutex_lock(philo->m_end);
		*philo->end = 1;
		pthread_mutex_unlock(philo->m_end);
		gettimeofday(&time, (void *) 0);
		printf("%lu,%03lu %i died\n", time.tv_sec, time.tv_usec / 1000, philo->id);
	}
}

int	forks_take(t_philo *philo, int i)
{
	int	ret;

	ret = 1;
	pthread_mutex_lock(philo->m_forks[i]);
	if (*philo->forks[i])
		ret = 0;
	else
		*philo->forks[i] = 1;
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

	if (forks_take(philo, 0))
	{
		if (forks_take(philo, 1))
		{
			gettimeofday(&time, (void *) 0);
			printf("%lu,%03lu %i has taken a fork\n", time.tv_sec, time.tv_usec / 1000, philo->id);
			printf("%lu,%03lu %i has taken a fork\n", time.tv_sec, time.tv_usec / 1000, philo->id);
			printf("%lu,%03lu %i is eating\n", time.tv_sec, time.tv_usec / 1000, philo->id);
			gettimeofday(&philo->start_eat, (void *) 0);
			return (0);
		}
		else
			forks_put(philo, 0);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	struct timeval	*time;

	time = &philo->start_sleep;
	gettimeofday(time, (void *) 0);
	if (time_is_inf(time_add(philo->start_eat, *philo->time_to_eat), *time))
	{
		gettimeofday(time, (void *) 0);
		printf("%lu,%03lu %i is sleeping\n", time->tv_sec, time->tv_usec / 1000, philo->id);
		forks_put(philo, 0);
		forks_put(philo, 1);
		return (0);
	}
	return (1);
}

int	sleeping(t_philo *philo)
{
	(void) philo;
	struct timeval	time;

	gettimeofday(&time, (void *) 0);
	if (time_is_inf(time_add(philo->start_sleep, *philo->time_to_sleep), time))
	{
		printf("%lu,%03lu %i is thinking\n", time.tv_sec, time.tv_usec / 1000, philo->id);
		return (0);
	}
	return (1);
}

void	*thread_philo(t_philo *philo)
{
	while (!check_end(philo))
	{
		if (!check_end(philo))
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
	philo->m_end = &table->m_end;
	philo->end = &table->end;
	gettimeofday(&philo->start_eat, (void *) 0);
	philo->time_to_die = &table->time_to_die;
	philo->time_to_eat = &table->time_to_eat;
	philo->time_to_sleep = &table->time_to_sleep;
	philo->must_eat = table->must_eat;
	pthread_create(&philo->thread, (void *) 0, (void *) thread_philo, philo);
	return (0);
}

int	start_philosophers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (start_one_philo(table, table->philosophers + i, i))
		{
			ft_dprintf(2, "Thread init Error\n");
			return (1);
		}
		i++;
	}
	return (0);
}
