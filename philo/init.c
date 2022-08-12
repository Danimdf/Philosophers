/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dmonteir < dmonteir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:27:13 by jfrancis          #+#    #+#             */
/*   Updated: 2022/08/13 01:58:42 by Dmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static long int get_current_time(t_philo *philo);

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
		(info->philo)[i].philo_info = info;
		(info->philo)[i].id = i + 1;
		(info->philo)[i].n_eat = 0;

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

void	*actions(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;

	if (philo->id % 2 == 0)
		usleep(500);

	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(philo->neighbours_fork);

	printf("%li : Filosofo %i ta comendo.\n", get_current_time(philo), philo->id);
	usleep(philo->philo_info->ms_to_eat * 1000);
	
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->neighbours_fork);

	printf("%li : Filosofo %i ta dormindo.\n", get_current_time(philo), philo->id);
	usleep(philo->philo_info->ms_to_sleep * 1000);

	printf("%li : Filosofo %i to pensando.\n", get_current_time(philo), philo->id);
	
	//Arrumar os prints (igual pdf pede)
	//ver quando o proximo filosofo precisa pegar os garfos e comer

	return (0);
}

static long int get_current_time(t_philo *philo)
{
	long int time_now;

	time_now = get_t_stamp() - philo->philo_info->timestamp;
	return time_now;
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
