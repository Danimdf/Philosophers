#include "includes/philo.h"

static void	*one_philo(t_philo *philo);
static void	print_action(t_philo *philo, char *action);

static void	think(t_philo *philo)
{
	print_action(philo, THINK);
	return ;
}

static int read_control(t_philo *philo)
{
	int control;

	pthread_mutex_lock(&philo->philo_info->mutex_control);
	control = philo->philo_info->control;
	pthread_mutex_unlock(&philo->philo_info->mutex_control);
	return (control);
}

static void write_control(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->philo_info->mutex_control);
	philo->philo_info->control = status;
	pthread_mutex_unlock(&philo->philo_info->mutex_control);
}

static int read_first_to_die(t_philo *philo)
{
	int first_to_die;

	pthread_mutex_lock(&philo->philo_info->mutex_first_to_die);
	first_to_die = philo->philo_info->first_to_die;
	pthread_mutex_unlock(&philo->philo_info->mutex_first_to_die);
	return (first_to_die);
}

static void write_first_to_die(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->philo_info->mutex_first_to_die);
	philo->philo_info->first_to_die = value;
	pthread_mutex_unlock(&philo->philo_info->mutex_first_to_die);
}

static void	doze_off(t_philo *philo)
{
	print_action(philo, SLEEP);
	if (!has_enough_time(philo, philo->philo_info->ms_to_sleep)
		&& read_first_to_die(philo) != 1)
	{
		int conta = philo->philo_info->ms_to_die - (get_t_stamp() - philo->last_meal);
		// printf("conta: %i\n", conta);
		usleep(conta * 1000);
		write_control(philo, FALSE);
		print_action(philo, DIE);
		return ;
	}
	else
		usleep(philo->philo_info->ms_to_sleep * 1000);
	return ;
}

static void	print_action(t_philo *philo, char *action)
{
	long int	t;

	pthread_mutex_lock(&philo->philo_info->print_out);
	t =  get_current_time(philo->pgm_start);
	if (ft_strcmp(action, FORK) == 0 && read_control(philo))
		printf("%s%ld %i %s%s\n", YEL, t, philo->id, FORK, RESET);
	if (ft_strcmp(action, EAT) == 0 && read_control(philo))
		printf("%s%ld %i %s%s\n", GRN, t, philo->id, EAT, RESET);
	if (ft_strcmp(action, THINK) == 0 && read_control(philo))
		printf("%s%ld %i %s%s\n", CYN, t, philo->id, THINK, RESET);
	if (ft_strcmp(action, SLEEP) == 0 && read_control(philo))
		printf("%s%ld %i %s%s\n", BLU, t, philo->id, SLEEP, RESET);
	if (ft_strcmp(action, DIE) == 0 && read_first_to_die(philo) == 0)
	{
		write_first_to_die(philo, 1);
		printf("%s%ld %i %s%s\n", RED, t, philo->id, DIE, RESET);
	}
	pthread_mutex_unlock(&philo->philo_info->print_out);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	if (!is_alive(philo) || !read_control(philo))
	{
		write_control(philo, FALSE);
		pthread_mutex_unlock(philo->first_fork);
		return ;
	}
	print_action(philo, FORK);
	pthread_mutex_lock(philo->second_fork);
	if (!is_alive(philo) || !read_control(philo))
	{
		write_control(philo, FALSE);
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return ;
	}
	print_action(philo, FORK);
	philo->last_meal = get_t_stamp();
	print_action(philo, EAT);
	if (philo->philo_info->ms_to_eat > philo->philo_info->ms_to_die)
	{
		usleep(philo->philo_info->ms_to_die * 1000);
		write_control(philo, FALSE);
		print_action(philo, DIE);
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		return ;
	}
	usleep(philo->philo_info->ms_to_eat * 1000);
	philo->n_eat++;
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return ;
}

int	is_alive(t_philo *philo)
{
	if ((philo->philo_info->ms_to_die - get_current_time(philo->last_meal)) > 0)
		return (TRUE);
	else
		return (FALSE);
}

int	has_enough_time(t_philo *philo, int action)
{
	if ((philo->philo_info->ms_to_die - get_current_time(philo->last_meal)) >= action)
		return (TRUE);
	else
		return (FALSE);
}

void	*actions(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if(philo->philo_info->num_philos == 1)
		return (one_philo(philo));
	while (read_control(philo) && philo->n_eat < philo->philo_info->num_meals)
	{
		if (read_control(philo))
			eat(philo);
		if(!read_control(philo))
			break ;
		if (read_control(philo))
			doze_off(philo);
		if(!read_control(philo))
			break ;
		think(philo);
	}
	return (0);
}

static void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_action(philo, FORK);
	usleep(philo->philo_info->ms_to_die * 1000);
	print_action(philo, DIE);
	pthread_mutex_unlock(&philo->fork);
	return NULL;
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
		if (pthread_join(info->philo[i].thread, NULL))
			printf("join failed\n");
		i++;
	}
}
