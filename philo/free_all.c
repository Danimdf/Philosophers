#include "includes/philo.h"

void	ft_free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_all(t_philo_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philos)
		pthread_mutex_destroy(&((info->philo)[i].fork));
	ft_free_ptr((void *)&info->philo);
}