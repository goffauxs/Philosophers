/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:17:49 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/07/14 15:49:50 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void ft_init_philo(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		env->philos[i].is_eating = 0;
		env->philos[i].pos = i;
		env->philos[i].lfork = i;
		env->philos[i].rfork = (i + 1) % env->count;
		pthread_mutex_init(&env->philos[i].mutex, NULL);
	}
}

static int	ft_init(t_env *env, int argc, char *argv[])
{
	env->count = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->eat_count_min = ft_atoi(argv[5]);
	else
		env->eat_count_min = 0;
	if (env->count < 2 || env->count > 200 || env->time_to_die < 60
		|| env->time_to_eat < 60 || env->time_to_sleep < 60
		|| env->eat_count_min < 0)
		return (0);
	env->philos = (t_philo *)malloc(sizeof(t_philo) * env->count);
	if (!env->philos)
		return (0);
	ft_init_philo(env);
}

int	main(int argc, char *argv[])
{
	t_env	env;
	t_philo	**philos;
	
	if (argc < 5 || argc > 6)
		return (ft_return_error(ERR_USAGE));
	if (!ft_init(&env, argc, argv))
		return (ft_return_error("init error.\n"));
	philos = (t_philo **)malloc(sizeof(t_philo *) * env.count);
}