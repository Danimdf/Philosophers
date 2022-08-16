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
	pthread_mutex_destroy(&(info->mutex_control));
	pthread_mutex_destroy(&(info->mutex_first_to_die));
	pthread_mutex_destroy(&(info->print_out));
	ft_free_ptr((void *)&info->philo);
}