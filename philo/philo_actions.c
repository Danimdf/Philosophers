/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:08:49 by roaraujo          #+#    #+#             */
/*   Updated: 2022/08/19 21:03:48 by roaraujo         ###   ########.fr       */
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
	// int	cal;

	print_action(philo, SLEEP);
	// if (!has_enough_time(philo, philo->philo_info->ms_to_sleep)
	// 	&& read_var(&philo->philo_info->first_to_die, 
	// 	&philo->philo_info->mutex_first_to_die) != 1)
	// {
	// 	cal = philo->philo_info->ms_to_die - (get_t_stamp() - philo->last_meal);
	// 	usleep(cal * 1000);
	// 	write_var(&philo->philo_info->control, 
	// 		&philo->philo_info->mutex_control, FALSE);
	// 	// print_action(philo, DIE);
	// 	return ;
	// }
	// else
	usleep(philo->philo_info->ms_to_sleep * 1000);
		
	return ;
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	// if (!is_alive(philo) || !read_var(&philo->philo_info->control, 
	// &philo->philo_info->mutex_control))
	// {
	// 	write_var(&philo->philo_info->control, &philo->philo_info->mutex_control, FALSE);
	// 	pthread_mutex_unlock(philo->first_fork);
	// 	return ;
	// }
	print_action(philo, FORK);
	pthread_mutex_lock(philo->second_fork);
	// if (!is_alive(philo) || !read_var(&philo->philo_info->control, &philo->philo_info->mutex_control))
	// {
	// 	write_var(&philo->philo_info->control, &philo->philo_info->mutex_control, FALSE);
	// 	release_forks(philo);
	// 	return ;
	// }
	print_action(philo, FORK);
	write_var(&philo->last_meal, &philo->mutex_last_meal, get_t_stamp());
	print_action(philo, EAT);
	// philo_die_in_lunch(philo);
	usleep(philo->philo_info->ms_to_eat * 1000);
	philo->n_eat++;
	// release_forks(philo);
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
	// while (read_var(&philo->philo_info->control, &philo->philo_info->mutex_control) && philo->n_eat < philo->philo_info->num_meals)
	while (philo->n_eat < philo->philo_info->num_meals && !read_var(&philo->philo_info->first_to_die, &philo->philo_info->mutex_first_to_die))
	{
		// if (read_var(&philo->philo_info->control, &philo->philo_info->mutex_control))
		eat(philo);
		// if (!read_var(&philo->philo_info->control, &philo->philo_info->mutex_control))
			// break ;
		// if (read_var(&philo->philo_info->control, &philo->philo_info->mutex_control))
		doze_off(philo);
		// if (!read_var(&philo->philo_info->control, &philo->philo_info->mutex_control))
			// break ;
		think(philo);
	}
	return (0);
}
