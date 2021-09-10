/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:17:49 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/09/09 13:48:38 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_check_params(t_env *env, int argc, char *argv[])
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_isint(argv[i]))
			return (0);
		if (ft_atoi(argv[i]) < 0)
			return (0);
	}
	env->count = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->eat_count_max = ft_atoi(argv[5]);
	else
		env->eat_count_max = 0;
	if (env->count < 1 || env->time_to_die < 0 || env->time_to_eat < 0
		|| env->time_to_sleep < 0 || env->eat_count_max < 0)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_env	env;

	env.max_ate = 0;
	env.stop_condition = 0;
	printf("test 1\n");
	if (argc < 5 || argc > 6)
	{
		write(2, ERR_USAGE, 112);
		return (0);
	}
	printf("test 2\n");
	if (!ft_check_params(&env, argc, argv))
	{
		write(2, "Incorrect parameters.\n", 22);
		return (0);
	}
	printf("test 3\n");
	if (!ft_init(&env))
	{
		write(2, "init error.\n", 12);
		return (0);
	}
	printf("count: %d\n", env.count);
	if (start_threads(&env))
	{
		write(2, "threads error.\n", 15);
		return (0);
	}
	printf("test 5\n");
	return (0);
}
