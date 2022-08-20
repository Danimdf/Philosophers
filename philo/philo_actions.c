/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dmonteir < dmonteir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:08:49 by roaraujo          #+#    #+#             */
/*   Updated: 2022/08/20 18:20:04 by Dmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo)
{
	print_action(philo, THINK);
	usleep(50);
	return ;
}

static void	doze_off(t_philo *philo)
{
	print_action(philo, SLEEP);
	usleep(philo->philo_info->ms_to_sleep * 1000);
	return ;
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_action(philo, FORK);
	pthread_mutex_lock(philo->second_fork);
	print_action(philo, FORK);
	write_var(&philo->last_meal, &philo->mutex_last_meal, get_t_stamp());
	print_action(philo, EAT);
	usleep(philo->philo_info->ms_to_eat * 1000);
	philo->n_eat++;
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return ;
}

void	*actions(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->philo_info->num_philos == 1)
		return (one_philo(philo));
	while (philo->n_eat < philo->philo_info->num_meals && !read_var(&philo->philo_info->first_to_die, &philo->philo_info->mutex_first_to_die))
	{
		eat(philo);
		doze_off(philo);
		think(philo);
	}
	return (0);
}
