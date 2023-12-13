/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:31:53 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/13 13:35:11 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_eat(t_data *data)
{
	int	die;

	die = 0;
	pthread_mutex_lock(&(data->share->die_mutex));
	if (data->share->die == 1)
		die = 1;
	pthread_mutex_unlock(&(data->share->die_mutex));
	if (die == 1)
		return ;
	printf("\033[0;32m%lld %d is eating\n",
		time_stamp() - data->share->start_time, data->sit + 1);
	ft_usleep(data->t.eat);
}

void	print_sleep(t_data *data)
{
	int	die;

	die = 0;
	pthread_mutex_lock(&(data->share->die_mutex));
	if (data->share->die == 1)
		die = 1;
	pthread_mutex_unlock(&(data->share->die_mutex));
	if (die == 1)
		return ;
	printf("\033[0;33m%lld %d is sleeping\n",
		time_stamp() - data->share->start_time, data->sit + 1);
	ft_usleep(data->t.sleep);
}

void	print_think(t_data *data)
{
	int	die;

	die = 0;
	pthread_mutex_lock(&(data->share->die_mutex));
	if (data->share->die == 1)
		die = 1;
	pthread_mutex_unlock(&(data->share->die_mutex));
	if (die == 1)
		return ;
	printf("\033[0;34m%lld %d is thinking\n",
		time_stamp() - data->share->start_time, data->sit + 1);
}

void	print_fork(t_data *data)
{
	int	die;

	die = 0;
	pthread_mutex_lock(&(data->share->die_mutex));
	if (data->share->die == 1)
		die = 1;
	pthread_mutex_unlock(&(data->share->die_mutex));
	if (die == 1)
		return ;
	printf("\033[0;35m%lld %d has taken a fork\n",
		time_stamp() - data->share->start_time, data->sit + 1);
}
