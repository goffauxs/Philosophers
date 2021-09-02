/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:17:49 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/09/02 14:29:53 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

static void new_sleep(unsigned long duration, t_env *env)
{
	unsigned long end;

	end = get_time() + duration;
	while (!env->stop_condition)
	{
		if (get_time() >= end)
			break ;
		usleep(1000);
	}
}

static void	philo_print(char *msg, t_philo *philo)
{
	char	*timestamp;
	char	*philo_num;

	timestamp = ft_itoa(get_time() - philo->env->start_time);
	philo_num = ft_itoa((int)philo->pos);
	pthread_mutex_lock(&philo->env->writing);
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

// static void test_print(t_philo *philo, int fork)
// {
// 	char	*timestamp;
// 	char	*philo_num;
// 	char	*fork_id;
	
// 	timestamp = ft_itoa(get_time() - philo->env->start_time);
// 	philo_num = ft_itoa(philo->pos);
// 	fork_id = ft_itoa(fork);
// 	pthread_mutex_lock(&philo->env->writing);
// 	if (!philo->env->stop_condition && !philo->env->max_ate)
// 	{
// 		write(1, timestamp, ft_strlen(timestamp));
// 		write(1, " ", 1);
// 		write(1, philo_num, ft_strlen(philo_num));
// 		write(1, " has taken fork #", 17);
// 		write(1, fork_id, ft_strlen(fork_id));
// 		write(1, "\n", 1);
// 	}
// 	pthread_mutex_unlock(&philo->env->writing);
// 	free(timestamp);
// 	free(philo_num);
// 	free(fork_id);
// }

static void philo_eat(t_philo *philo)
{
	if (philo->pos % 2)
	{
		pthread_mutex_lock(&philo->env->forks[philo->lfork]);
		philo_print("has taken a fork", philo);
		pthread_mutex_lock(&philo->env->forks[philo->rfork]);
		philo_print("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(&philo->env->forks[philo->rfork]);
		philo_print("has taken a fork", philo);
		pthread_mutex_lock(&philo->env->forks[philo->lfork]);
		philo_print("has taken a fork", philo);
	}
	pthread_mutex_lock(&philo->env->meal);
	philo_print("is eating", philo);
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->env->meal);
	new_sleep(philo->env->time_to_eat, philo->env);
	philo->ate_times++;
	pthread_mutex_unlock(&philo->env->forks[philo->rfork]);
	pthread_mutex_unlock(&philo->env->forks[philo->lfork]);
}

static void philo_dead(t_env *env, t_philo *philo)
{
	int	i;

	while (!env->max_ate)
	{
		i = -1;
		while (++i < env->count && !env->stop_condition)
		{
			pthread_mutex_lock(&env->meal);
			if ((int)(get_time() - philo[i].last_ate) > env->time_to_die)
			{
				philo_print("died", &philo[i]);
				env->stop_condition = 1;
			}
			pthread_mutex_unlock(&env->meal);
			usleep(100);
		}
		if (env->stop_condition)
			break ;
		i = 0;
		while (env->eat_count_max && i < env->count
			&& philo[i].ate_times >= env->eat_count_max)
			i++;
		if (i == env->count)
			env->max_ate = 1;
	}
}

void	*routine(void *params)
{
	int		i;
	t_philo	*philo;
	t_env	*env;

	i = 0;
	philo = (t_philo *)params;
	env = philo->env;
	if (philo->pos % 2)
		usleep(50);
	while (!env->stop_condition && !env->max_ate)
	{
		philo_eat(philo);
		philo_print("is sleeping", philo);
		new_sleep(env->time_to_sleep, env);
		philo_print("is thinking", philo);
	}
	return (NULL);
}

static int	start_threads(t_env *env)
{
	int	i;

	i = 0;
	env->start_time = get_time();
	while (i < env->count)
	{
		if (pthread_create(&(env->philos[i].thread_id),
			NULL, routine, &(env->philos[i])))
			return (1);
		env->philos[i].last_ate = get_time();
		env->philos[i].limit = env->philos[i].last_ate + env->time_to_die;
		i++;
	}
	philo_dead(env, env->philos);
	if (env->count == 1)
		pthread_detach(env->philos[0].thread_id);
	else
	{
		i = -1;
		while (++i < env->count)
			pthread_join(env->philos[i].thread_id, NULL);
	}
	i = -1;
	while (++i < env->count)
		pthread_mutex_destroy(&env->forks[i]);
	pthread_mutex_destroy(&env->meal);
	pthread_mutex_destroy(&env->writing);
	return (0);
}

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

static void ft_init_philo(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		env->philos[i].ate_times = 0;
		env->philos[i].pos = i + 1;
		env->philos[i].lfork = i;
		env->philos[i].rfork = (i + 1) % env->count;
		env->philos[i].env = env;
		i++;
	}
}

static int	ft_init(t_env *env)
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

static int	ft_check_params(t_env *env, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_isint(argv[i]))
			return (0);
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	env->count = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		env->eat_count_max = ft_atoi(argv[5]);
		if (env->eat_count_max <= 0)
			return (0);
	}
	else
		env->eat_count_max = 0;
	if (env->count < 1 || env->count > 200 || env->time_to_die < 60
		|| env->time_to_eat < 60 || env->time_to_sleep < 60
		|| env->eat_count_max < 0)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_env	env;

	env.max_ate = 0;
	env.stop_condition = 0;
	if (argc < 5 || argc > 6)
		return (ft_return_error(ERR_USAGE));
	if (!ft_check_params(&env, argc, argv))
		return (ft_return_error("Incorrect parameters.\n"));
	if (!ft_init(&env))
		return (ft_return_error("init error.\n"));
	if (start_threads(&env))
		return (ft_return_error("threads error.\n"));
	return (0);
}