/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:57:32 by iel-amra          #+#    #+#             */
/*   Updated: 2022/12/01 17:58:50 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

void	destroy_all_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
		pthread_mutex_destroy(table->forks_mutex + i++);
	pthread_mutex_destroy(&table->m_end);
}

void	free_memory(t_table *table)
{
	free(table->forks_mutex);
	free(table->forks);
	free(table->philosophers);
}

int	memory_alloc(t_table *table)
{
	table->philosophers =
		malloc(sizeof(*table->philosophers) * table->nb_philo);
	table->forks_mutex =
		malloc(sizeof(*table->forks_mutex) * table->nb_philo);
	table->forks = malloc(sizeof(*table->forks) * table->nb_philo);
	if (!table->philosophers || !table->forks_mutex || !table->forks)
	{
		ft_dprintf(2, "Malloc error\n");
		free_memory(table);
		return (1);
	}
	return (0);
}

int	create_mutex(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->m_end, (void *) 0))
	{
		ft_dprintf(2, "Mutex init error\n");
		return (1);
	}
	table->end = 0;
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
			return (1);
		}
		i++;
	}
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
