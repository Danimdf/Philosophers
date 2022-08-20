/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:16:01 by roaraujo          #+#    #+#             */
/*   Updated: 2022/08/20 17:24:49 by Dmonteir         ###   ########.fr       */
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
