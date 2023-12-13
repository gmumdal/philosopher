/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:29:03 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/13 15:05:45 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct timeval	t_te;
typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thre;

typedef struct s_share
{
	int			total;
	int			count;
	int			die;
	t_mutex		*mutex;
	t_mutex		die_mutex;
	long long	start_time;
}	t_share;

typedef struct s_time
{
	int	die;
	int	eat;
	int	sleep;
}	t_time;

typedef struct s_data
{
	int			sit;
	int			must_eat;
	long long	last_eat;
	t_time		t;
	t_share		*share;
}	t_data;

/* philo.c */
int			ph_atoi(char *str);
long long	time_stamp(void);
int			error_print(char *str);

/* make_philo.c */
int			make_philo(int ac, char **av, int num_philo, t_data *data);
int			share_init(t_share *share, int num_philo);
int			data_init(t_data *data, int i, int ac, char **av);
void		end_philo(t_data *data, t_thre *tid);
void		clean_all(t_data *data, t_thre *tid, int total);

/* start_eating.c */
void		*sit_table(void *tmp);
void		start_eating(t_data *data, int right, int left);
int			ph_mutex_lock(t_data *data, int right, int left);
int			ft_usleep(int time);

/* print_state.c */
void		print_eat(t_data *data);
void		print_sleep(t_data *data);
void		print_think(t_data *data);
void		print_fork(t_data *data);

#endif
