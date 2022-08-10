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

typedef struct s_philo
{
	int				id;
	int				n_eat;
	int				l_fork;
	int				r_fork;
	long int		timestamp;
	pthread_t		thread;
	pthread_mutex_t	mutex;
}	t_philo;

typedef struct s_philo_info
{
    long int				num_philos;
	long int				ms_to_die;
	long int				ms_to_eat;
	long int				ms_to_sleep;
	long int				num_meals;
	t_philo					*philo;
	pthread_mutex_t			*forks;
	pthread_mutex_t			main_mutex;
} t_philo_info;


//check_params
long int	ft_atol(const char *nptr);
size_t	    ft_strlen(const char *s);
int         validate_number(char **argv, int i);
int	        check_params(int argc, char **argv);
void	    parse_args(t_philo_info *info, int argc, char **argv);

//init Philo and Forks
void    	init_philo_n_Fork(t_philo_info *info);

//error
int         print_error(char *msg);


#endif