/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:17:27 by roaraujo          #+#    #+#             */
/*   Updated: 2022/08/16 21:29:33 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *philo)
{
	if ((philo->philo_info->ms_to_die - get_current_time(philo->last_meal)) > 0)
		return (TRUE);
	else
		return (FALSE);
}

int	has_enough_time(t_philo *philo, int action)
{
	if ((philo->philo_info->ms_to_die - get_current_time(philo->last_meal))
		>= action)
		return (TRUE);
	else
		return (FALSE);
}

void	print_action(t_philo *philo, char *action)
{
	long int	t;

	pthread_mutex_lock(&philo->philo_info->print_out);
	t = get_current_time(philo->pgm_start);
	if (ft_strcmp(action, FORK) == 0 && read_var(&philo->philo_info->control, &philo->philo_info->mutex_control))
		printf("%s%ld %i %s%s\n", YEL, t, philo->id, FORK, RESET);
	if (ft_strcmp(action, EAT) == 0 && read_var(&philo->philo_info->control, &philo->philo_info->mutex_control))
		printf("%s%ld %i %s%s\n", GRN, t, philo->id, EAT, RESET);
	if (ft_strcmp(action, THINK) == 0 && read_var(&philo->philo_info->control, &philo->philo_info->mutex_control))
		printf("%s%ld %i %s%s\n", CYN, t, philo->id, THINK, RESET);
	if (ft_strcmp(action, SLEEP) == 0 && read_var(&philo->philo_info->control, &philo->philo_info->mutex_control))
		printf("%s%ld %i %s%s\n", BLU, t, philo->id, SLEEP, RESET);
	if (ft_strcmp(action, DIE) == 0 && read_var(&philo->philo_info->first_to_die, &philo->philo_info->mutex_first_to_die) == 0)
	{
		write_first_to_die(philo, 1);
		printf("%s%ld %i %s%s\n", RED, t, philo->id, DIE, RESET);
	}
	pthread_mutex_unlock(&philo->philo_info->print_out);
}
