/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dmonteir < dmonteir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:17:27 by roaraujo          #+#    #+#             */
/*   Updated: 2022/08/20 22:12:49 by Dmonteir         ###   ########.fr       */
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
	long int	in_ms;

	in_ms = get_current_time(philo->last_meal);
	if ((philo->philo_info->ms_to_die - in_ms)
		> action)
		return (TRUE);
	else
		return (FALSE);
}

void	print_action(t_philo *p, char *action)
{
	long int	t;

	pthread_mutex_lock(&p->philo_info->print_out);
	t = get_current_time(p->pgm_start);
	if (ft_strcmp(action, FORK) == 0
		&& read_var(&p->philo_info->control, &p->philo_info->mutex_control))
		printf("%s%ld %i %s%s\n", YEL, t, p->id, FORK, RESET);
	if (ft_strcmp(action, EAT) == 0
		&& read_var(&p->philo_info->control, &p->philo_info->mutex_control))
		printf("%s%ld %i %s%s\n", GRN, t, p->id, EAT, RESET);
	if (ft_strcmp(action, THINK) == 0
		&& read_var(&p->philo_info->control, &p->philo_info->mutex_control))
		printf("%s%ld %i %s%s\n", CYN, t, p->id, THINK, RESET);
	if (ft_strcmp(action, SLEEP) == 0
		&& read_var(&p->philo_info->control, &p->philo_info->mutex_control))
		printf("%s%ld %i %s%s\n", BLU, t, p->id, SLEEP, RESET);
	if (ft_strcmp(action, DIE) == 0
		&& read_var(&p->philo_info->first_to_die,
			&p->philo_info->mutex_first_to_die) == 0)
	{
		write_var(&p->philo_info->first_to_die,
			&p->philo_info->mutex_first_to_die, 1);
		printf("%s%ld %i %s%s\n", RED, t, p->id, DIE, RESET);
	}
	pthread_mutex_unlock(&p->philo_info->print_out);
}
