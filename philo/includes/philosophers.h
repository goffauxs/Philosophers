/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:06:45 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/07/13 16:12:52 by sgoffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define ERR_USAGE "Usage: ./philo <# philosophers> <time to die> <time to eat>\
 <time to sleep> [# times each philosopher must eat]\n"

typedef struct s_philo
{
	
}				t_philo;

typedef struct s_env
{
	int	count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_count_min;
	
}				t_env;

int	ft_atoi(const char *nptr);
int	ft_return_error(const char *msg);

#endif