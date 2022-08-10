/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dmonteir < dmonteir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:45:39 by Dmonteir          #+#    #+#             */
/*   Updated: 2022/08/10 00:54:18 by Dmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	parse_args(t_philo_info *info, int argc, char **argv)
{
	info->num_philos = ft_atol(argv[1]);
	info->ms_to_die = ft_atol(argv[2]);
	info->ms_to_eat = ft_atol(argv[3]);
	info->ms_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		info->num_meals = ft_atol(argv[5]);
	else
		info->num_meals = MAX_INT;
}
