/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dmonteir < dmonteir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:31:24 by Dmonteir          #+#    #+#             */
/*   Updated: 2022/08/10 02:24:42 by Dmonteir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/philo.h"

static long int	get_t_stamp(void);

int main(int argc, char **argv)
{
    
	t_philo_info	info;

	check_params(argc, argv);
	parse_args(&info, argc, argv);
    
    init_philo (&info);


    // teste minimo ./philo 2 1 1 1
    // saber a hora que o philo tem que pegar os garfos e comer
    // tempo de dormir
    // soltar os garfos 
    // e se não comer é hora de morrer
    return (0);
}

void    init_philo(t_philo_info *info)
{
    int i;
    
    i = 0;
    pthread_mutex_init(&info->main_mutex);
    info->forks = ft_calloc(info->num_philos, sizeof(pthread_mutex_t));
    info->philos = ft_calloc(info->num_philos, sizeof(t_philo));
    while(i < info->num_philos)
    {
        info->philo->id = i + 1;
        info->philo->n_eat = 0;
        info->philo->l_fork = i;
        info->philo->r_fork = i + 1;
        if (i == info->num_philos - 1)
            info->philo->r_fork = 0;
        info->philo->timestamp = get_t_stamp();
        //pthread_mutex_init(&info->forks[i], NULL);
        //info->philo->thread = pthread_create();
        //pthread_mutex_init(&info->philo[i]->mutex, NULL);

        // Verificar se devemos abrir um mutex para cada filosofo 
        // e para cada garfo

        i++;
    }
}

static long int	get_t_stamp(void)
{
	struct timeval	tv;
	long int		ms;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}
