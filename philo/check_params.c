/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dmonteir < dmonteir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:31:49 by Dmonteir          #+#    #+#             */
/*   Updated: 2022/08/10 00:56:07 by Dmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c);

#include "includes/philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long int	ft_atol(const char *nptr)
{
	long int	s;
	long int	res;

	s = 1;
	res = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			s *= -1;
		nptr++;
	}
	while (ft_isdigit((int)*nptr))
	{
		res = (res * 10) + (*nptr - 48);
		nptr++;
	}
	return (res * s);
}

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (*s != '\0')
	{
		s++;
		n++;
	}
	return (n);
}

int	validate_number(char **argv, int i)
{
	long int	j;
	int			index;
	int			arg_size;

	j = 0;
	index = 0;
	arg_size = ft_strlen(argv[i]);
	if (argv[i][index] == '-')
		index++;
	while (index < arg_size)
	{
		if (!ft_isdigit(argv[i][index]))
			return (1);
		index++;
	}
	j = ft_atol(argv[i]);
	if (j > MAX_INT || j < MIN_INT)
		print_error("Invalid number!");
	return (0);
}

int	check_params(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (print_error("philos must have at least 4 arguments."));
	while (i < argc)
	{
		if (validate_number(argv, i) != 0)
			return (print_error("All arguments must be numbers"));
		i++;
	}
	return (0);
}
