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
	(void) philo;
	return (0);
}

void	check_death(t_philo *philo)
{
	(void) philo;
	return (0);
}

int	thinking(philo)
{
	(void) philo;
	return (0);
}

int	eating(philo)
{
	(void) philo;
	return (0);
}

int	sleeping(philo)
{	
	(void) philo;
	return (0);
}

void	*thread_philo(t_philo *philo)
{
	struct timeval	time;
	while (!check_end(philo))
	{
		gettimeofday(&time, (void *) 0);
		if (!check_end(philo))
			printf("%u,%u %i is thinking\n", time.tv_sec, time.tv_usec / 1000);
		while (!check_end(philo) && thinking(philo))
			check_death(philo);
		gettimeofday(&time, (void *) 0);
		if (!check_end(philo))
			printf("%u,%u %i is eating\n", time.tv_sec, time.tv_usec / 1000);
		while (!check_end(philo) && eating(philo))
			check_death(philo);
		gettimeofday(&time, (void *) 0);
		if (!check_end(philo))
			printf("%u,%u %i is sleeping\n", time.tv_sec, time.tv_usec / 1000);
		while (!check_end(philo) && sleeping(philo))
			check_death(philo);
	}	
}	

int	start_one_philo(t_table *table, t_philo *philo, int i)
{
	philo->id = (i * 2 + (i > table->nb_philo  / 2)) % nb->philo;
	philo->m_forks[0] = table->forks_mutex + i;
	philo->m_forks[1] = table->forks_mutex + (i % table->nb_philo);
	philo->forks[0] = table->forks + i;
	philo->forks[1] = table->forks + (i % table->nb_philo);
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
		if (start_one_philo(table, table->philosophers + i, i++))
		{
			ft_dprintf(2, "Thread init Error\n");
			return (1);
		}
	}
	return (0);
