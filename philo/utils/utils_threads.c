/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dmonteir < dmonteir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:16:01 by roaraujo          #+#    #+#             */
/*   Updated: 2022/08/18 00:40:04 by Dmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		pthread_create(&info->philo[i].thread, NULL, &actions, &info->philo[i]);
		i++;
	}
}

void	join_threads(t_philo_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		if (pthread_join(info->philo[i].thread, NULL))
			printf("join failed\n");
		i++;
	}
}

void	philo_die_in_lunch(t_philo *philo)
{
	if (philo->philo_info->ms_to_eat > philo->philo_info->ms_to_die)
	{
		usleep(philo->philo_info->ms_to_die * 1000);
		write_var(&philo->philo_info->control, &philo->philo_info->mutex_control, FALSE);
		print_action(philo, DIE);
		release_forks(philo);
		return ;
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}
