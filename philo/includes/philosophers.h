/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:06:45 by sgoffaux          #+#    #+#             */
/*   Updated: 2021/09/01 15:09:30 by sgoffaux         ###   ########.fr       */
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

struct s_env;

typedef struct s_philo
{
	int				ate_times;
	int				pos;
	int				lfork;
	int				rfork;
	unsigned long	last_ate;
	unsigned long	limit;
	struct s_env	*env;
	pthread_t		thread_id;
}				t_philo;

typedef struct s_env
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count_max;
	unsigned long	start_time;
	int				stop_condition;
	int				max_ate;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	writing;
}				t_env;

int		ft_atoi(const char *nptr);
int		ft_return_error(char *msg);
int		ft_strlen(char *str);
char	*ft_itoa(int nbr);
int		ft_isint(const char *nptr);

#endif