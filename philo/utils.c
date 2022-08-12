/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancis <jfrancis@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:01:53 by jfrancis          #+#    #+#             */
/*   Updated: 2022/08/11 20:39:10 by jfrancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int	s;
	int	res;

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

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*s;

	s = b;
	while (n--)
	{
		*s++ = (unsigned char)c;
	}
	return (b);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}

int	get_t_stamp(void)
{
	struct timeval	tv;
	int		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}
