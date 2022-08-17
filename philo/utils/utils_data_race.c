/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data_race.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:16:59 by roaraujo          #+#    #+#             */
/*   Updated: 2022/08/16 21:29:04 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	read_var(int *var, pthread_mutex_t *mutex)
{
	int	temp;

	pthread_mutex_lock(mutex);
	temp = *var;
	pthread_mutex_unlock(mutex);
	return (temp);
}

// int	read_first_to_die(t_philo *philo)
// {
// 	int	first_to_die;

// 	pthread_mutex_lock(&philo->philo_info->mutex_first_to_die);
// 	first_to_die = philo->philo_info->first_to_die;
// 	pthread_mutex_unlock(&philo->philo_info->mutex_first_to_die);
// 	return (first_to_die);
// }

void	write_control(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->philo_info->mutex_control);
	philo->philo_info->control = status;
	pthread_mutex_unlock(&philo->philo_info->mutex_control);
}

void	write_first_to_die(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->philo_info->mutex_first_to_die);
	philo->philo_info->first_to_die = value;
	pthread_mutex_unlock(&philo->philo_info->mutex_first_to_die);
}
