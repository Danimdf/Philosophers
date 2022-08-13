#include "includes/philo.h"

static void	think(t_philo *philo)
{
	printf("%li %i is thinking.\n", get_current_time(philo), philo->id);
}

static int	doze_off(t_philo *philo)
{
	// pthread_mutex_lock(&philo->sleep_mutex);
	printf("%li %i is sleeping.\n", get_current_time(philo), philo->id);
	if (has_enough_time(philo, philo->philo_info->ms_to_sleep))
	{
		usleep((philo->philo_info->ms_to_die - (get_t_stamp() - philo->last_meal)) * 1000);
		printf("%li %i died.\n", get_current_time(philo), philo->id);
	}
	else
	{
		usleep(philo->philo_info->ms_to_sleep * 1000);
		printf("%li %i end sleeping.\n", get_current_time(philo), philo->id);
	}
	return (TRUE);
	// pthread_mutex_unlock(&philo->sleep_mutex);
}

static int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (!is_alive(philo))
		return (FALSE);
	printf("%li %i has taken a fork.\n", get_current_time(philo), philo->id);
	pthread_mutex_lock(philo->neighbours_fork);
	if (!is_alive(philo))
		return (FALSE);
	printf("%li %i has taken a neighbours_fork.\n", get_current_time(philo), philo->id);
	philo->last_meal = get_t_stamp();
	printf("%li %i is eating.\n", get_current_time(philo), philo->id);
	if (!has_enough_time(philo, philo->philo_info->ms_to_eat))
	{
		philo->philo_info->control = FALSE;
		return (FALSE);
	}
	usleep(philo->philo_info->ms_to_eat * 1000);
	philo->n_eat++;
	pthread_mutex_unlock(&philo->fork);
	printf("%li %i has put a fork.\n", get_current_time(philo), philo->id);
	pthread_mutex_unlock(philo->neighbours_fork);
	printf("%li %i has put a neighbours_fork.\n", get_current_time(philo), philo->id);
	philo->philo_info->control = TRUE;
	return (TRUE);
}

int	is_alive(t_philo *philo)
{
	if ((philo->philo_info->ms_to_die - get_current_time(philo)) > 0)
		return (TRUE);
	else
		return (FALSE);
}

int	has_enough_time(t_philo *philo, int action)
{
	if ((philo->philo_info->ms_to_die - get_current_time(philo)) >= action)
		return (TRUE);
	else
		return (FALSE);
}

void	philo_dies(t_philo *philo)
{
	printf("%li %i died.\n", get_current_time(philo), philo->id);
}

void	*actions(void *args)
{
	t_philo	*philo;
	philo = (t_philo *)args;

	if (philo->id % 2 == 0)
		usleep(500);
	while (philo->philo_info->control)
	{
		philo->philo_info->control = eat(philo);
		if(!philo->philo_info->control)
			break ;
		philo->philo_info->control = doze_off(philo);
		if(!philo->philo_info->control)
			break ;
		think(philo);
	}
	if(!philo->philo_info->control)
		philo_dies(philo);
	return (0);
}

void	create_threads(t_philo_info *info)
{
	int i;

	i = 0;
	while(i < info->num_philos)
	{
		pthread_create(&info->philo[i].thread, NULL, &actions, &info->philo[i]);
		i++;
	}
}

void	join_threads(t_philo_info *info)
{
	int i;

	i = 0;
	while(i < info->num_philos) {
		pthread_join(info->philo[i].thread, NULL);
		i++;
	}
}
