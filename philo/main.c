/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:31:24 by Dmonteir          #+#    #+#             */
/*   Updated: 2022/08/13 17:28:58 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/philo.h"

int	main(int argc, char **argv)
{

	t_philo_info	info;

	if (!check_params(argc, argv))
		return (-1);
	parse_args(&info, argc, argv);
	init_all(&info);
	create_threads(&info);
	join_threads(&info);
	free_all(&info);
	return (0);
}
