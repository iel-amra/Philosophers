/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:05:36 by iel-amra          #+#    #+#             */
/*   Updated: 2023/01/07 15:57:21 by iel-amra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_overflow(int argc, char **argv)
{
	if (!fit_in_int(argv[1]) || !fit_in_int(argv[2])
		|| !fit_in_int(argv[3]) || !fit_in_int(argv[4])
		|| (argc == 6 && !fit_in_int(argv[5])))
	{
		ft_dprintf(2, "Int Overflow\n");
		return (1);
	}
	if (!ft_strcmp(argv[1], "0") || !ft_strcmp(argv[2], "0")
		|| !ft_strcmp(argv[3], "0") || !ft_strcmp(argv[4], "0")
		|| (argc == 6 && !ft_strcmp(argv[5], "0")))
	{
		ft_dprintf(2, "No zero allowed\n");
		return (1);
	}
	if (argv[1][0] == '\0' || argv[2][0] == '\0' || argv[3][0] == '\0'
		|| argv[4][0] == '\0' || (argc == 6 && argv[5][0] == '\0'))
	{
		ft_dprintf(2, "No empty Arguments allowed\n");
		return (1);
	}
	return (0);
}

int	parse(t_table *table, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		ft_dprintf(2, "Bad number of arguments\n");
		return (1);
	}
	if (!ft_s_isdigit(argv[1]) || !ft_s_isdigit(argv[2])
		|| !ft_s_isdigit(argv[3]) || !ft_s_isdigit(argv[4])
		|| (argc == 6 && !ft_s_isdigit(argv[5])))
	{
		ft_dprintf(2, "Arguments must be numerical (no - sign)\n");
		return (1);
	}
	if (check_overflow(argc, argv))
		return (1);
	table->nb_philo = ft_atoi(argv[1]);
	table->time_to_die = ms_to_timeval(ft_atoi(argv[2]));
	table->time_to_eat = ms_to_timeval(ft_atoi(argv[3]));
	table->time_to_sleep = ms_to_timeval(ft_atoi(argv[4]));
	table->must_eat = -1;
	table->end = 0;
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	return (0);
}
