/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:50:42 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/09/09 13:03:18 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_init_mutex(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		if (pthread_mutex_init(&(env->forks[i]), NULL))
			return (1);
		i++;
	}
	pthread_mutex_init(&env->meal, NULL);
	pthread_mutex_init(&env->writing, NULL);
	return (0);
}

static void	ft_init_philo(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		env->philos[i].ate_times = 0;
		env->philos[i].pos = i + 1;
		env->philos[i].ffork = i;
		env->philos[i].sfork = (i + 1) % env->count;
		env->philos[i].env = env;
		i++;
	}
}

int	ft_init(t_env *env)
{
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
