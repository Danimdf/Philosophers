/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:32:39 by Dmonteir          #+#    #+#             */
/*   Updated: 2022/08/13 15:18:59 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	print_error(char *msg)
{
	printf("%s%s%s\n", RED, msg, RESET);
	return (FALSE);
}
