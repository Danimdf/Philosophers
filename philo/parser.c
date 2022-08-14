/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dmonteir < dmonteir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:45:39 by Dmonteir          #+#    #+#             */
/*   Updated: 2022/08/15 00:52:28 by Dmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	parse_args(t_philo_info *info, int argc, char **argv)
{
	info->num_philos = ft_atoi(argv[1]);
	info->ms_to_die = ft_atoi(argv[2]);
	info->ms_to_eat = ft_atoi(argv[3]);
	info->ms_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_meals = ft_atoi(argv[5]);
	else
		info->num_meals = MAX_INT;
}
