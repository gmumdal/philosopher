/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_eating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 23:37:26 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/13 15:45:48 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		;
	data->last_eat = time_stamp();
	if (data->sit % 2 == 1)
		ft_usleep(data->t.eat);
	start_eating(data, right, left);
	return (data);
}

void	start_eating(t_data *data, int right, int left)
{
	if (data->share->start_time == 0)
		data->share->start_time = time_stamp();
	while (42)
	{
		if (data->share->die == 1)
			return ;
		if (ph_mutex_lock(data, right, left) == 0)
			return ;
		data->last_eat = time_stamp();
		data->must_eat--;
		print_eat(data);
		pthread_mutex_unlock(&(data->share->mutex[right]));
		pthread_mutex_unlock(&(data->share->mutex[left]));
		print_sleep(data);
		print_think(data);
	}
}

int	ph_mutex_lock(t_data *data, int right, int left)
{
	pthread_mutex_lock(&(data->share->mutex[left]));
	print_fork(data);
	pthread_mutex_lock(&(data->share->mutex[right]));
	print_fork(data);
	return (1);
}

int	ft_usleep(int time)
{
	long long	target;

	target = (long long)time / 1000 + time_stamp();
	while (target > time_stamp())
		usleep(100);
	return (0);
}
