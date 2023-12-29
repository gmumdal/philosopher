/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sitting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 20:17:38 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/29 21:32:20 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*sit_one(void *tmp)
{
	t_data	*data;

	data = (t_data *)tmp;
	data->share->start_time = time_stamp();
	data->last_eat = time_stamp();
	while (42)
	{
		pthread_mutex_lock(&(data->share->die_mutex));
		if (data->share->die == 1)
		{
			pthread_mutex_unlock(&(data->share->die_mutex));
			return (data);
		}
		pthread_mutex_unlock(&(data->share->die_mutex));
		pthread_mutex_lock(&(data->share->mutex[0]));
		print_fork(data);
		while (data->share->die == 0)
			usleep(100);
		pthread_mutex_unlock(&(data->share->mutex[0]));
	}
	return (data);
}

void	*sit_table(void *tmp)
{
	t_data	*data;
	int		right;
	int		left;

	data = (t_data *)tmp;
	right = data->sit;
	if (data->sit == 0)
		left = data->share->total - 1;
	else
		left = data->sit - 1;
	pthread_mutex_lock(&(data->share->die_mutex));
	data->share->count++;
	pthread_mutex_unlock(&(data->share->die_mutex));
	while (data->share->count != data->share->total)
		usleep(10);
	data->last_eat = time_stamp();
	if (data->sit % 2 == 1)
		ft_usleep(data->share->t.eat / 2, data);
	start_eating(data, right, left);
	return (data);
}

void	start_eating(t_data *data, int right, int left)
{
	int	die;

	die = 0;
	pthread_mutex_lock(&(data->share->start_mutex));
	if (data->share->start_time == 0)
		data->share->start_time = time_stamp();
	pthread_mutex_unlock(&(data->share->start_mutex));
	while (42)
	{
		ph_mutex_lock(data, right, left);
		data->last_eat = time_stamp();
		print_eat(data);
		if (data->must_eat > 0)
			data->must_eat--;
		pthread_mutex_unlock(&(data->share->mutex[right]));
		pthread_mutex_unlock(&(data->share->mutex[left]));
		print_sleep(data);
		print_think(data);
		pthread_mutex_lock(&(data->share->die_mutex));
		if (data->share->die == 1)
			die = 1;
		pthread_mutex_unlock(&(data->share->die_mutex));
		if (die == 1)
			return ;
	}
}

void	ph_mutex_lock(t_data *data, int right, int left)
{
	pthread_mutex_lock(&(data->share->mutex[left]));
	print_fork(data);
	pthread_mutex_lock(&(data->share->mutex[right]));
	print_fork(data);
}

int	ft_usleep(int time, t_data *data)
{
	long long	target;

	target = (long long)time / 1000 + time_stamp();
	while (target > time_stamp())
	{
		pthread_mutex_lock(&(data->share->die_mutex));
		if (data->share->die == 1)
		{
			pthread_mutex_unlock(&(data->share->die_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(data->share->die_mutex));
		usleep(100);
	}
	return (0);
}
