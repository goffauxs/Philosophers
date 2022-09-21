/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 10:10:05 by sgoffaux          #+#    #+#             */
/*   Updated: 2022/09/21 11:31:18 by sgoffaux         ###   ########.fr       */
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
	if (pthread_mutex_init(&env->meal, NULL))
		return (1);
	if (pthread_mutex_init(&env->writing, NULL))
		return (1);
	return (0);
}

static int	ft_init_philo(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		env->philos[i].ate_times = 0;
		env->philos[i].pos = i + 1;
		env->philos[i].pos_str = ft_itoa(i + 1);
		if (!env->philos[i].pos_str)
			break ;
		env->philos[i].ffork = i;
		env->philos[i].sfork = (i + 1) % env->count;
		env->philos[i].env = env;
		i++;
	}
	if (i != env->count)
	{
		while (i >= 0)
		{
			free(env->philos[i].pos_str);
			i--;
		}
		return (1);
	}
	return (0);
}

int	ft_init(t_env *env)
{
	env->philos = malloc(sizeof(t_philo) * env->count);
	if (!env->philos)
		return (0);
	env->forks = malloc(sizeof(pthread_mutex_t) * env->count);
	if (!env->forks)
	{
		free(env->philos);
		return (0);
	}
	if (ft_init_mutex(env))
	{
		free(env->philos);
		free(env->forks);
		return (0);
	}
	if (ft_init_philo(env))
	{
		free(env->philos);
		free(env->forks);
		return (0);
	}
	return (1);
}
