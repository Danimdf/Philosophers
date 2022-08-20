/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:27:13 by jfrancis          #+#    #+#             */
/*   Updated: 2022/08/19 20:51:04 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo_info *info)
{
	int	i;

	i = 0;
	info->philo = ft_calloc(info->num_philos, sizeof(t_philo));
	while (i < info->num_philos)
	{
		(info->philo)[i].philo_info = info;
		(info->philo)[i].id = i + 1;
		(info->philo)[i].n_eat = 0;
		(info->philo)[i].last_meal = get_t_stamp();
		(info->philo)[i].pgm_start = get_t_stamp();
		i++;
	}
}

void	init_forks(t_philo_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->mutex_control, NULL);
	pthread_mutex_init(&info->mutex_first_to_die, NULL);
	pthread_mutex_init(&info->print_out, NULL);
	while (i < info->num_philos)
	{
		pthread_mutex_init(&(info->philo)[i].fork, NULL);
		(info->philo)[i].neighbours_fork = &((info->philo)[(i + 1)
				% info->num_philos].fork);
		pthread_mutex_init(&(info->philo)[i].mutex_last_meal, NULL);
		if ((info->philo)[i].id % 2)
		{
			(info->philo)[i].first_fork = (info->philo)[i].neighbours_fork;
			(info->philo)[i].second_fork = &(info->philo)[i].fork;
		}
		else
		{
			(info->philo)[i].first_fork = &(info->philo)[i].fork;
			(info->philo)[i].second_fork = (info->philo)[i].neighbours_fork;
		}
		i++;
	}
}

void	init_all(t_philo_info *info)
{
	info->control = TRUE;
	info->first_to_die = FALSE;
	init_philo(info);
	init_forks(info);
}
