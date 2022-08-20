/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_data_race.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:16:59 by roaraujo          #+#    #+#             */
/*   Updated: 2022/08/19 20:38:30 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	read_var(long int *var, pthread_mutex_t *mutex)
{
	long int	temp;

	pthread_mutex_lock(mutex);
	temp = *var;
	pthread_mutex_unlock(mutex);
	return (temp);
}

void	write_var(long int *var, pthread_mutex_t *mutex, long int status)
{
	pthread_mutex_lock(mutex);
	*var = status;
	pthread_mutex_unlock(mutex);
}
