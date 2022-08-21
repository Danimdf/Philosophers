/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dmonteir < dmonteir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:13:34 by roaraujo          #+#    #+#             */
/*   Updated: 2022/08/21 22:10:12 by Dmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_all(t_philo_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philos)
	{
		pthread_mutex_destroy(&((info->philo)[i].fork));
		pthread_mutex_destroy(&(info->philo)[i].mutex_last_meal);
		pthread_mutex_destroy(&(info->philo)[i].mutex_n_eat);
	}
	pthread_mutex_destroy(&(info->mutex_control));
	pthread_mutex_destroy(&(info->mutex_first_to_die));
	pthread_mutex_destroy(&(info->print_out));
	ft_free_ptr((void *)&info->philo);
}
