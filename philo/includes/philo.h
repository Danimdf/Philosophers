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

typedef struct s_philo_info t_philo_info;
typedef struct s_philo
{
	int				id;
	int				n_eat;
	int				l_fork;
	int				r_fork;
	int				last_meal;
	t_philo_info	*philo_info;
	pthread_t		thread;
	pthread_mutex_t	sleep_mutex;
	pthread_mutex_t	fork;
	pthread_mutex_t	*neighbours_fork;
}	t_philo;

typedef struct s_philo_info
{
	int					control;
	int					num_philos;
	int					ms_to_die;
	int					ms_to_eat;
	int					ms_to_sleep;
	int					num_meals;
	t_philo				*philo;
	long int			pgm_start;
	pthread_mutex_t		main_mutex;
} t_philo_info;


//parser
void		parse_args(t_philo_info *info, int argc, char **argv);

//check_params
int			check_params(int argc, char **argv);

// utils_check
int			ft_isdigit(int c);
long int	ft_atol(const char *nptr);
size_t		ft_strlen(const char *s);
int			validate_number(char **argv, int i);

// utils
int			ft_atoi(const char *nptr);
void		*ft_memset(void *b, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
long int			get_t_stamp(void);
long int	get_current_time(t_philo *philo);

//init
void		init_all(t_philo_info *info);
void		init_philo(t_philo_info *info);
void		init_forks(t_philo_info *info);

//philo_actions
void		create_threads(t_philo_info *info);
void		join_threads(t_philo_info *info);
void		*actions(void *args);
int			is_alive(t_philo *philo);
int	has_enough_time(t_philo *philo, int action);

//error
int			print_error(char *msg);


#endif
