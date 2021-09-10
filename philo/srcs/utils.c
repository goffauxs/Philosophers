/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:01:47 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/09/09 13:34:39 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

struct timeval	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time);
}

void	new_sleep(unsigned long duration, t_env *env)
{
	struct timeval	start;

	start = get_time();
	while (!env->stop_condition)
	{
		if (time_diff_micro(start, get_time()) >= duration)
			break ;
		if (time_diff_micro(start, get_time()) / (double)duration > 0.9)
			usleep(100);
		else
			usleep(1000);
	}
}

unsigned long	time_diff_micro(struct timeval start, struct timeval end)
{
	unsigned long	microseconds;

	microseconds = (end.tv_sec - start.tv_sec) * 1000000;
	microseconds += (end.tv_usec - start.tv_usec);
	return (microseconds);
}

int	time_diff_milli(struct timeval start, struct timeval end)
{
	int milliseconds;

	milliseconds = (end.tv_sec - start.tv_sec) * 1000;
	milliseconds += (end.tv_usec - start.tv_usec) / 1000;
	return (milliseconds);
}

int	ft_isint(const char *nptr)
{
	int		i;
	int		neg;
	long	value;

	i = 0;
	value = 0;
	neg = 0;
	while ((nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '-')
		neg = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && (nptr[i] >= 48 && nptr[i] <= 57))
	{
		if (value > 214748364 || (value == 214748364
				&& ((!neg && nptr[i] - '0' > 7) || (neg && nptr[i] - '0' > 8))))
			return (0);
		else
			value = (value * 10) + nptr[i++] - '0';
	}
	return (1);
}
