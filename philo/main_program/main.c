/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dmonteir < dmonteir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:31:24 by Dmonteir          #+#    #+#             */
/*   Updated: 2022/08/21 22:45:51 by Dmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	observer(t_philo_info *info);

int	main(int argc, char **argv)
{
	t_philo_info	info;

	if (!check_params(argc, argv))
		return (-1);
	parse_args(&info, argc, argv);
	init_all(&info);
	create_threads(&info);
	observer(&info);
	join_threads(&info);
	free_all(&info);
	return (0);
}

int	all_philos_ate_enough(t_philo_info *info)
{
	int	i;
	int	full_philos;

	i = -1;
	full_philos = 0;
	while (++i < info->num_philos)
	{
		if (read_var(&(info->philo)[i].n_eat,
			&(info->philo)[i].mutex_n_eat) >= info->num_meals)
			full_philos++;
	}
	if (full_philos == info->num_philos)
		return (TRUE);
	else
		return (FALSE);
}

static void	observer(t_philo_info *info)
{
	int				i;

	i = -1;
	while (1)
	{
		i = (i + 1) % info->num_philos;
		if (info->num_meals != MAX_INT)
		{
			if (all_philos_ate_enough(info))
				break ;
		}
		if (read_var(&(info->philo)[i].n_eat,
			&(info->philo)[i].mutex_n_eat) < info->num_meals
				&& get_current_time(read_var(&(info->philo)[i].last_meal,
					&(info->philo)[i].mutex_last_meal)) > info->ms_to_die)
		{
			write_var(&info->control, &info->mutex_control, FALSE);
			print_action(&(info->philo)[i], DIE);
			break ;
		}
		usleep(450);
	}
}
