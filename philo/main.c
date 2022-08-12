/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dmonteir < dmonteir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:31:24 by Dmonteir          #+#    #+#             */
/*   Updated: 2022/08/13 01:30:18 by Dmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/philo.h"

int	main(int argc, char **argv)
{

	t_philo_info	info;

	check_params(argc, argv);
	parse_args(&info, argc, argv);
	init_all(&info);
	create_threads(&info);
	join_threads(&info);
	// teste minimo ./philo 2 1 1 1
	// saber a hora que o philo tem que pegar os garfos e comer
	// tempo de dormir
	// soltar os garfos
	// e se não comer é hora de morrer
	return (0);
}
