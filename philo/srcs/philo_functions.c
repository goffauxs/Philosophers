/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:53:57 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/09/09 13:45:55 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_print(char *msg, t_philo *philo)
{
	char	*timestamp;
	char	*philo_num;

	pthread_mutex_lock(&philo->env->writing);
	timestamp = ft_itoa(time_diff_milli(philo->env->start_time, get_time()));
	philo_num = ft_itoa((int)philo->pos);
	if (!philo->env->stop_condition && !philo->env->max_ate)
	{
		write(1, timestamp, ft_strlen(timestamp));
		write(1, " ", 1);
		write(1, philo_num, ft_strlen(philo_num));
		write(1, " ", 1);
		write(1, msg, ft_strlen(msg));
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(&philo->env->writing);
	free(timestamp);
	free(philo_num);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->forks[philo->ffork]);
	philo_print("has taken a fork", philo);
	pthread_mutex_lock(&philo->env->forks[philo->sfork]);
	philo_print("has taken a fork", philo);
	pthread_mutex_lock(&philo->env->meal);
	philo_print("is eating", philo);
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->env->meal);
	new_sleep(philo->env->time_to_eat * 1000, philo->env);
	philo->ate_times++;
	pthread_mutex_unlock(&philo->env->forks[philo->sfork]);
	pthread_mutex_unlock(&philo->env->forks[philo->ffork]);
}

void	philo_dead(t_env *env, t_philo *philo)
{
	int	i;

	while (!env->max_ate)
	{
		i = -1;
		while (++i < env->count && !env->stop_condition)
		{
			pthread_mutex_lock(&env->meal);
			if (time_diff_micro(env->philos[i].last_ate, get_time())
				>= (unsigned long)env->time_to_die)
			{
				philo_print("died", &philo[i]);
				pthread_mutex_lock(&env->writing);
				env->stop_condition = 1;
			}
			pthread_mutex_unlock(&env->meal);
		}
		if (env->stop_condition)
			break ;
		i = 0;
		while (env->eat_count_max && i < env->count
			&& philo[i].ate_times >= env->eat_count_max)
			i++;
		env->max_ate = (i == env->count);
	}
}
