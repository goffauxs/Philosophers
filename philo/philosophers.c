/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:17:49 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/07/13 15:32:42 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		return (1);
	env->philos
}

int	main(int argc, char *argv[])
{
	t_env	env;
	t_philo	**philos;
	
	if (argc < 5 || argc > 6)
		return (ft_return_error(ERR_USAGE));
	if (ft_init(&env, argc, argv))
		return (ft_return_error("init error.\n"));
	philos = (t_philo **)malloc(sizeof(t_philo *) * env.count);
}