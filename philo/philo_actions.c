#include "includes/philo.h"

static void	think(t_philo *philo)
{
	printf("%li %i is thinking.\n", get_current_time(philo), philo->id);
	return ;
}

static void	doze_off(t_philo *philo)
{
	printf("%li %i is sleeping.\n", get_current_time(philo), philo->id);
	if (!has_enough_time(philo, philo->philo_info->ms_to_sleep))
	{
		usleep((philo->philo_info->ms_to_die - (get_t_stamp() - philo->last_meal)) * 1000);
		philo->philo_info->control = FALSE;
		printf("%li %i died while sleeping.\n", get_current_time(philo), philo->id);
		return ;
	}
	else
	{
		usleep(philo->philo_info->ms_to_sleep * 1000);
		printf("%li %i end sleeping.\n", get_current_time(philo), philo->id);
	}
	return ;
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (!is_alive(philo))
	{
		philo->philo_info->control = FALSE;
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	printf("%li %i has taken a fork.\n", get_current_time(philo), philo->id);
	pthread_mutex_lock(philo->neighbours_fork);
	if (!is_alive(philo))
	{
		philo->philo_info->control = FALSE;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->neighbours_fork);
		return ;
	}
	printf("%li %i has taken a neighbours_fork.\n", get_current_time(philo), philo->id);
	philo->last_meal = get_t_stamp();
	printf("%li %i is eating.\n", get_current_time(philo), philo->id);
	if (philo->philo_info->ms_to_eat > philo->philo_info->ms_to_die)
	{
		usleep((philo->philo_info->ms_to_eat > philo->philo_info->ms_to_die) * 1000);
		philo->philo_info->control = FALSE;
		printf("%li %i died while eating.\n", get_current_time(philo), philo->id);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->neighbours_fork);
		return ;
	}
	usleep(philo->philo_info->ms_to_eat * 1000);
	philo->n_eat++;
	pthread_mutex_unlock(&philo->fork);
	printf("%li %i has put a fork.\n", get_current_time(philo), philo->id);
	pthread_mutex_unlock(philo->neighbours_fork);
	printf("%li %i has put a neighbours_fork.\n", get_current_time(philo), philo->id);
	philo->philo_info->control = TRUE;
	return ;
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

void	*actions(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		usleep(500);
	while (philo->philo_info->control)
	{
		eat(philo);
		if(!philo->philo_info->control)
			break ;
		doze_off(philo);
		if(!philo->philo_info->control)
			break ;
		think(philo);
	}
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
