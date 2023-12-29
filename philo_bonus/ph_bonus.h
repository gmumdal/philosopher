/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_bonus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:29:03 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/29 21:01:02 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_BONUS_H
# define PH_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct timeval	t_te;
typedef pthread_t		t_thre;

typedef struct s_time
{
	int	die;
	int	eat;
	int	sleep;
}	t_time;

typedef struct s_data
{
	int			sit;
	int			num_philo;
	int			must_eat;
	long long	last_eat;
	long long	start_time;
	char		*sem_name;
	sem_t		*sem;
	sem_t		*print_sem;
	sem_t		*must_sem;
	t_time		t;
	pid_t		*pid;
}	t_data;

/* ph_bonus */
int			data_init(t_data *data, char **av);
int			ph_atoi(char *str);

/* ph_sema_bonus */
void		make_sem_file(t_data *data);
void		make_print_sem_file(t_data *data);
void		make_must_sem_file(t_data *data);
char		*ph_name_make(char *base, int i);

/* ph_make_bonus */
void		make_philo(t_data *data);
void		make_child(t_data *data);
void		*monitoring(void *tmp);
void		wait_children(t_data *data, pid_t *pid);
void		*must_monitor(void *tmp);

/* ph_utils_bonus */
long long	time_stamp(void);
void		error_print(int flag);
int			ph_usleep(int time);
void		start_setting(t_data *data);

/* ph_print_bonus */
void		print_eat(t_data *data);
void		print_sleep(t_data *data);
void		print_think(t_data *data);
void		print_fork(t_data *data);
void		write_state(long long lld, int d, char *state);

#endif