/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:17:49 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/08/30 11:59:04 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

static void	*routine(void *params)
{
	
}

static int	start_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		if (pthread_create(&(env->philos[i].thread_id),
			NULL, routine, &(env->philos[i])))
			return (1);
		env->philos[i].last_ate = get_time();
		env->philos[i].limit = env->philos[i].last_ate + env->time_to_die;
	}
}

static int	ft_init_mutex(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		if (pthread_mutex_init(&(env->forks[i]), NULL))
			return (1);
	}
	return (0);
}

static void ft_init_philo(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		env->philos[i].is_eating = 0;
		env->philos[i].pos = i + 1;
		env->philos[i].lfork = i;
		env->philos[i].rfork = (i + 1) % env->count;
		env->philos[i].env = env;
		i++;
	}
}

static int	ft_init(t_env *env, int argc, char *argv[])
{
	env->count = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		env->eat_count_max = ft_atoi(argv[5]);
		if (env->eat_count_max < 0)
			return (1);
	}
	else
		env->eat_count_max = 0;
	if (env->count < 2 || env->count > 200 || env->time_to_die < 60
		|| env->time_to_eat < 60 || env->time_to_sleep < 60
		|| env->eat_count_max < 0)
		return (0);
	env->philos = malloc(sizeof(t_philo) * env->count);
	if (!env->philos)
		return (0);
	env->forks = malloc(sizeof(pthread_mutex_t) * env->count);
	if (!env->forks)
		return (0);
	ft_init_mutex(env);
	ft_init_philo(env);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_env	env;
	
	if (argc < 5 || argc > 6)
		return (ft_return_error(ERR_USAGE));
	if (!ft_init(&env, argc, argv))
		return (ft_return_error("init error.\n"));
	if (start_threads(&env))
		return (ft_return_error("threads error.\n"));
}