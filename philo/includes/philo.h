/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 21:13:52 by roaraujo          #+#    #+#             */
/*   Updated: 2022/08/19 20:44:06 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "colors.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define TRUE 1
# define FALSE 0
# define DIE "died"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"

typedef struct s_philo_info	t_philo_info;
typedef struct s_philo
{
	int				id;
	int				n_eat;
	long int		last_meal;
	t_philo_info	*philo_info;
	pthread_t		thread;
	long int		pgm_start;
	pthread_mutex_t	fork;
	pthread_mutex_t	*neighbours_fork;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	mutex_last_meal;
}	t_philo;

typedef struct s_philo_info
{
	long int			control;
	long int			first_to_die;
	int					num_philos;
	long int			ms_to_die;
	int					ms_to_eat;
	int					ms_to_sleep;
	int					num_meals;
	t_philo				*philo;
	pthread_mutex_t		mutex_control;
	pthread_mutex_t		mutex_first_to_die;
	pthread_mutex_t		print_out;
}	t_philo_info;

//parser
void		parse_args(t_philo_info *info, int argc, char **argv);

//check_params
int			check_params(int argc, char **argv);

// free_all.c
void		free_all(t_philo_info *info);

// utils_check
int			ft_isdigit(int c);
long int	ft_atol(const char *nptr);
size_t		ft_strlen(const char *s);
int			validate_number(char **argv, int i);
int			ft_strcmp(const char *s1, const char *s2);

// utils
int			ft_atoi(const char *nptr);
void		*ft_memset(void *b, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
long int	get_t_stamp(void);
long int	get_current_time(long int ts_baseline);
long int	read_var(long int *var, pthread_mutex_t *mutex);
void		write_var(long int *var, pthread_mutex_t *mutex, long int status);
void		create_threads(t_philo_info *info);
void		join_threads(t_philo_info *info);
void		philo_die_in_lunch(t_philo *philo);
void		release_forks(t_philo *philo);

//init
void		init_all(t_philo_info *info);
void		init_philo(t_philo_info *info);
void		init_forks(t_philo_info *info);

//philo_actions
void		*actions(void *args);
int			is_alive(t_philo *philo);
int			has_enough_time(t_philo *philo, int action);
void		*one_philo(t_philo *philo);
void		print_action(t_philo *philo, char *action);

//error
int			print_error(char *msg);

#endif
