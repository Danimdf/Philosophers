/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:27:13 by jfrancis          #+#    #+#             */
/*   Updated: 2022/08/11 21:41:56 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	init_all(t_philo_info *info)
{
		init_philo(info);
		init_forks(info);
}

void	init_philo(t_philo_info *info)
{
	int i;

	i = 0;
	info->philo = ft_calloc(info->num_philos, sizeof(t_philo));
	while(i < info->num_philos)
	{
		(info->philo)[i].id = i + 1;
		(info->philo)[i].n_eat = 0;
		(info->philo)[i].l_fork = i;
		if (i == info->num_philos - 1)
			(info->philo)[i].r_fork = 0;
		else
			(info->philo)[i].r_fork = i + 1;

		(info->philo)[i].neighbours_fork = &((info->philo)[(i + 1) % info->num_philos].fork);
		(info->philo)[i].timestamp = get_t_stamp();
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
		i++;
	}
}

void	*actions(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->neighbours_fork);
	printf("Filosofo %i fazendo alguma coisa.\n", philo->id);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->neighbours_fork);
	return (0);
}

void	create_threads(t_philo_info *info)
{
	int i;

	i = 0;
	while(i < info->num_philos)
	{
		pthread_create(&info->philo[i].thread, NULL, &actions, &info->philo[i]);
		i++;
	}
}

void	join_threads(t_philo_info *info)
{
	int i;

	i = 0;
	while(i < info->num_philos) {
		pthread_join(info->philo[i].thread, NULL);
		i++;
	}
}
