/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:08:49 by roaraujo          #+#    #+#             */
/*   Updated: 2022/08/16 21:10:30 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo)
{
	print_action(philo, THINK);
	return ;
}

static void	doze_off(t_philo *philo)
{
	int	cal;

	print_action(philo, SLEEP);
	if (!has_enough_time(philo, philo->philo_info->ms_to_sleep)
		&& read_first_to_die(philo) != 1)
	{
		cal = philo->philo_info->ms_to_die - (get_t_stamp() - philo->last_meal);
		usleep(cal * 1000);
		write_control(philo, FALSE);
		print_action(philo, DIE);
		return ;
	}
	else
		usleep(philo->philo_info->ms_to_sleep * 1000);
	return ;
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	if (!is_alive(philo) || !read_control(philo))
	{
		write_control(philo, FALSE);
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	print_action(philo, FORK);
	pthread_mutex_lock(philo->second_fork);
	if (!is_alive(philo) || !read_control(philo))
	{
		write_control(philo, FALSE);
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return ;
	}
	print_action(philo, FORK);
	philo->last_meal = get_t_stamp();
	print_action(philo, EAT);
	if (philo->philo_info->ms_to_eat > philo->philo_info->ms_to_die)
	{
		usleep(philo->philo_info->ms_to_die * 1000);
		write_control(philo, FALSE);
		print_action(philo, DIE);
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return ;
	}
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
	while (read_control(philo) && philo->n_eat < philo->philo_info->num_meals)
	{
		if (read_control(philo))
			eat(philo);
		if (!read_control(philo))
			break ;
		if (read_control(philo))
			doze_off(philo);
		if (!read_control(philo))
			break ;
		think(philo);
	}
	return (0);
}
