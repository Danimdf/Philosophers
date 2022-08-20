/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:31:24 by Dmonteir          #+#    #+#             */
/*   Updated: 2022/08/19 21:13:10 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int				i;
	t_philo_info	info;

	if (!check_params(argc, argv))
		return (-1);
	parse_args(&info, argc, argv);
	init_all(&info);
	create_threads(&info);
	i = -1;
	while (1)
	{
		i = (i + 1) % info.num_philos;
		// if (read_var(&info.control, &info.mutex_control) == FALSE)
		// {
		// 	print_action(&(info.philo)[i], DIE);
		// 	break ;
		// }
		if (get_current_time(read_var(&(info.philo)[i].last_meal, &(info.philo)[i].mutex_last_meal)) >= info.ms_to_die)
		{
			write_var(&info.control, &info.mutex_control, FALSE);
			print_action(&(info.philo)[i], DIE);
			break ;
		}
		usleep(500);
	}
	join_threads(&info);
	free_all(&info);
	return (0);
}
