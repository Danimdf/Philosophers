/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:27:13 by jfrancis          #+#    #+#             */
/*   Updated: 2022/08/13 15:21:05 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	init_philo(t_philo_info *info)
{
	int i;

	i = 0;
	info->philo = ft_calloc(info->num_philos, sizeof(t_philo));
	while(i < info->num_philos)
	{
		(info->philo)[i].philo_info = info;
		(info->philo)[i].id = i + 1;
		(info->philo)[i].n_eat = 0;
		(info->philo)[i].last_meal = info->pgm_start;
		pthread_mutex_init(&(info->philo)[i].sleep_mutex, NULL);
		i++;
	}
}

void init_forks(t_philo_info *info)
{
	int i;

	i = 0;
	// info->forks = ft_calloc(info->num_philos, sizeof(pthread_mutex_t));
	while(i < info->num_philos)
	{
		pthread_mutex_init(&(info->philo)[i].fork, NULL);
		(info->philo)[i].neighbours_fork = &((info->philo)[(i + 1) % info->num_philos].fork);
		i++;
	}
}

void	init_all(t_philo_info *info)
{
	info->control = 1;
	info->pgm_start = get_t_stamp();
	init_philo(info);
	init_forks(info);
}
