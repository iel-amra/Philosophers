/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:31:00 by iel-amra          #+#    #+#             */
/*   Updated: 2023/01/07 15:06:47 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	forks_take(t_philo *philo, int i)
{
	int				ret;

	ret = 1;
	pthread_mutex_lock(philo->m_forks[i]);
	if (*philo->forks[i] == 0)
	{
		*philo->forks[i] = philo->id + 1;
		pthread_mutex_unlock(philo->m_forks[i]);
		pthread_mutex_lock(&philo->t->m_end);
		print_t("has taken a fork", philo);
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
	int				f1;
	int				f2;

	f1 = forks_take(philo, 0);
	f2 = forks_take(philo, 1);
	if (!f1 || !f2 || philo->m_forks[0] == philo->m_forks[1])
		return (1);
	pthread_mutex_lock(&philo->t->m_end);
	gettimeofday(&philo->start_eat, (void *) 0);
	print_t("is eating", philo);
	pthread_mutex_unlock(&philo->t->m_end);
	return (0);
}

int	eating(t_philo *philo)
{
	struct timeval	*time;

	time = &philo->start_sleep;
	gettimeofday(time, (void *) 0);
	if (time_is_inf(time_add(philo->start_eat, philo->t->time_to_eat), *time))
	{
		pthread_mutex_lock(&philo->t->m_end);
		gettimeofday(time, (void *) 0);
		print_t("is sleeping", philo);
		if (philo->eaten != -1)
			philo->eaten++;
		if (philo->eaten != -1 && philo->eaten >= philo->t->must_eat)
		{
			philo->t->end++;
			philo->eaten = -1;
		}
		pthread_mutex_unlock(&philo->t->m_end);
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
	if (time_is_inf(time_add(philo->start_sleep,
				philo->t->time_to_sleep), time))
	{
		pthread_mutex_lock(&philo->t->m_end);
		gettimeofday(&time, (void *) 0);
		print_t("is thinking", philo);
		pthread_mutex_unlock(&philo->t->m_end);
		return (0);
	}
	return (1);
}
