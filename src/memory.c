/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:15:47 by iel-amra          #+#    #+#             */
/*   Updated: 2022/12/20 13:15:48 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_memory(t_table *table)
{
	free(table->forks_mutex);
	free(table->forks);
	free(table->philosophers);
}

int	memory_alloc(t_table *table)
{
	table->philosophers
		= malloc(sizeof(*table->philosophers) * table->nb_philo);
	table->forks_mutex
		= malloc(sizeof(*table->forks_mutex) * table->nb_philo);
	table->forks = malloc(sizeof(*table->forks) * table->nb_philo);
	if (!table->philosophers || !table->forks_mutex || !table->forks)
	{
		ft_dprintf(2, "Malloc error\n");
		free_memory(table);
		return (1);
	}
	return (0);
}
