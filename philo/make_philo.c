/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:30:56 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/13 15:44:47 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philo(int ac, char **av, int num_philo, t_data *data)
{
	int		i;
	t_thre	*tid;
	t_share	share;

	tid = (t_thre *)malloc(sizeof(t_thre) * num_philo);
	if (tid == 0)
		return (error_print("malloc error"));
	if (share_init(&share, num_philo) == -1)
		return (error_print("malloc error"));
	i = -1;
	while (++i < num_philo)
	{
		if (data_init(&(data[i]), i, ac, av) == -1)
			return (error_print("input error"));
		data[i].share = &share;
		pthread_create(&(tid[i]), 0, sit_table, &(data[i]));
	}
	end_philo(data, tid);
	return (1);
}

int	share_init(t_share *share, int num_philo)
{
	int	i;

	pthread_mutex_init(&(share->die_mutex), 0);
	share->die = 0;
	share->start_time = 0;
	share->count = 0;
	share->total = num_philo;
	share->mutex = (t_mutex *)malloc(sizeof(t_mutex) * num_philo);
	if (share->mutex == 0)
		return (-1);
	i = 0;
	while (i < num_philo)
		pthread_mutex_init(&(share->mutex[i++]), 0);
	pthread_mutex_init(&(share->die_mutex), 0);
	return (0);
}

int	data_init(t_data *data, int i, int ac, char **av)
{
	data->sit = i;
	data->last_eat = 0;
	data->t.die = ph_atoi(av[2]) * 1000;
	data->t.eat = ph_atoi(av[3]) * 1000;
	data->t.sleep = ph_atoi(av[4]) * 1000;
	if (data->t.die < 0 || data->t.eat < 0 || data->t.sleep < 0)
		return (-1);
	if (ac == 6)
		data->must_eat = ph_atoi(av[5]);
	else
		data->must_eat = 2147483647;
	return (0);
}

void	end_philo(t_data *data, t_thre *tid)
{
	int	i;
	int	total;

	total = data[0].share->total;
	i = -1;
	while (++i < total)
		while (data[i].last_eat == 0)
			;
	while (42)
	{
		i = -1;
		while (++i < total)
		{
			if ((time_stamp() - data[i].last_eat) * 1000 > data[i].t.die
				|| data[i].must_eat <= 0)
				break ;
		}
		if (i != total)
			break ;
	}
	if (data[i].must_eat > 0)
		printf("\033[0;31m%lld %d died\n",
			time_stamp() - data[0].share->start_time, i + 1);
	clean_all(data, tid, total);
}

void	clean_all(t_data *data, t_thre *tid, int total)
{
	int		i;
	void	*re;

	pthread_mutex_lock(&(data[0].share->die_mutex));
	data[0].share->die = 1;
	pthread_mutex_unlock(&(data[0].share->die_mutex));
	i = 0;
	while (i < total)
	{
		pthread_join(tid[i], &re);
		pthread_mutex_destroy(&(data->share->mutex[i++]));
	}
	pthread_mutex_destroy(&(data->share->die_mutex));
	free(data->share->mutex);
	free(data);
	free(tid);
}
