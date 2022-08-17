/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dmonteir < dmonteir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:31:49 by Dmonteir          #+#    #+#             */
/*   Updated: 2022/08/18 01:29:06 by Dmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_params(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (print_error("philos must have at least 4 arguments."));
	while (i < argc)
	{
		if (validate_number(argv, i) != 0)
			return (print_error("All arguments must be numbers"
					"with positive values!"));
		i++;
	}
	return (TRUE);
}
