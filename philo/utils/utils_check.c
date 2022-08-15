#include "../includes/philo.h"

int	ft_isdigit(int c)
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

int    ft_strcmp(const char *s1, const char *s2)
{
    size_t            i;
    unsigned char    *s_s1;
    unsigned char    *s_s2;

    if (!s1 || !s2)
        return (-1);
    i = 0;
    s_s1 = (unsigned char *)s1;
    s_s2 = (unsigned char *)s2;
    while (s_s1[i] || s_s2[i])
    {
        if (s_s1[i] != s_s2[i])
            return (s_s1[i] - s_s2[i]);
        i++;
    }
    return (0);
}
