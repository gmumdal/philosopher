/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_make.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 20:16:28 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/29 15:01:09 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philo(int ac, char **av, int num_philo, t_data *data)
{
	int		i;
	int		error_check;
	t_thre	*tid;
	t_share	share;

	error_check = share_init(&share, num_philo, av);
	if (error_check == -1)
		return (error_print());
	tid = (t_thre *)malloc(sizeof(t_thre) * num_philo);
	if (tid == 0)
		return (error_free(tid, &share));
	i = -1;
	while (++i < num_philo)
	{
		if (data_init(&(data[i]), i, ac, av) == -1)
			return (error_free(tid, &share));
		data[i].share = &share;
		if (num_philo == 1)
			pthread_create(&(tid[i]), 0, sit_one, &(data[i]));
		else
			pthread_create(&(tid[i]), 0, sit_table, &(data[i]));
	}
	return (end_philo(data, tid));
}

int	share_init(t_share *share, int num_philo, char **av)
{
	int	i;

	share->die = 0;
	share->print = 0;
	share->start_time = 0;
	share->count = 0;
	share->total = num_philo;
	share->t.die = ph_atoi(av[2]) * 1000;
	share->t.eat = ph_atoi(av[3]) * 1000;
	share->t.sleep = ph_atoi(av[4]) * 1000;
	if (share->t.die < 0 || share->t.eat < 0 || share->t.sleep < 0)
		return (-1);
	share->mutex = (t_mutex *)malloc(sizeof(t_mutex) * num_philo);
	if (share->mutex == 0)
		return (-1);
	i = 0;
	while (i < num_philo)
		pthread_mutex_init(&(share->mutex[i++]), 0);
	pthread_mutex_init(&(share->start_mutex), 0);
	pthread_mutex_init(&(share->die_mutex), 0);
	pthread_mutex_init(&(share->print_mutex), 0);
	return (0);
}

int	data_init(t_data *data, int i, int ac, char **av)
{
	data->sit = i;
	data->last_eat = 0;
	if (ac == 6)
		data->must_eat = ph_atoi(av[5]);
	else
		data->must_eat = -2;
	if (data->must_eat == -1)
		return (-1);
	return (0);
}

int	end_philo(t_data *data, t_thre *tid)
{
	int		i;
	int		eat_num;
	t_share	*share;

	share = data[0].share;
	i = -1;
	while (++i < share->total)
		while (data[i].last_eat == 0)
			usleep(10);
	while (42)
	{
		i = -1;
		eat_num = 0;
		while (++i < share->total)
		{
			if ((time_stamp() - data[i].last_eat) * 1000 > share->t.die)
				return (clean_all(data, i, tid, share->total));
			if (data[i].must_eat == 0)
				eat_num++;
			if (eat_num == share->total)
				return (clean_all(data, i, tid, share->total));
		}
	}
	return (1);
}

int	clean_all(t_data *data, int j, t_thre *tid, int total)
{
	int		i;
	void	*re;

	pthread_mutex_lock(&(data[0].share->die_mutex));
	pthread_mutex_lock(&(data[0].share->print_mutex));
	if (data[j].must_eat == -2)
		printf("\033[0;31m%lld %d died\n",
			time_stamp() - data[0].share->start_time, j + 1);
	data[0].share->die = 1;
	data[0].share->print = 1;
	pthread_mutex_unlock(&(data[0].share->print_mutex));
	pthread_mutex_unlock(&(data[0].share->die_mutex));
	i = 0;
	while (i < total)
	{
		pthread_join(tid[i], &re);
		pthread_mutex_destroy(&(data[0].share->mutex[i++]));
	}
	pthread_mutex_destroy(&(data[0].share->die_mutex));
	free(data[0].share->mutex);
	free(tid);
	return (0);
}
