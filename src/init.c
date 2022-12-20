/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:57:32 by iel-amra          #+#    #+#             */
/*   Updated: 2022/12/20 13:15:41 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	destroy_all_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
		pthread_mutex_destroy(table->forks_mutex + i++);
	pthread_mutex_destroy(&table->m_end);
	pthread_mutex_destroy(&table->m_start);
}

int	create_mutex_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->forks[i] = 0;
		if (pthread_mutex_init(table->forks_mutex + i, (void *) 0))
		{
			ft_dprintf(2, "Mutex init error\n");
			while (i >= 0)
				pthread_mutex_destroy(table->forks_mutex + i--);
			pthread_mutex_destroy(&table->m_end);
			pthread_mutex_destroy(&table->m_start);
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->m_start, (void *) 0))
	{
		ft_dprintf(2, "Mutex init error\n");
		return (1);
	}
	if (pthread_mutex_init(&table->m_end, (void *) 0))
	{
		pthread_mutex_destroy(&table->m_start);
		ft_dprintf(2, "Mutex init error\n");
		return (1);
	}
	table->end = 0;
	if (create_mutex_forks(table))
		return (1);
	return (0);
}

int	init(t_table *table, int argc, char **argv)
{
	if (parse(table, argc, argv))
		return (1);
	if (memory_alloc(table))
		return (1);
	if (create_mutex(table))
	{
		free_memory(table);
		return (1);
	}
	return (0);
}
