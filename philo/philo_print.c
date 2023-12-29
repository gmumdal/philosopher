/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 20:18:03 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/29 15:01:29 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_eat(t_data *data)
{
	int	print;

	print = 0;
	pthread_mutex_lock(&(data->share->print_mutex));
	if (data->share->print == 1)
		print = 1;
	else
		printf("%lld %d is eating\n",
			time_stamp() - data->share->start_time, data->sit + 1);
	pthread_mutex_unlock(&(data->share->print_mutex));
	if (print == 1)
		return ;
	ft_usleep(data->share->t.eat, data);
}

void	print_sleep(t_data *data)
{
	int	print;

	print = 0;
	pthread_mutex_lock(&(data->share->print_mutex));
	if (data->share->print == 1)
		print = 1;
	else
		printf("%lld %d is sleeping\n",
			time_stamp() - data->share->start_time, data->sit + 1);
	pthread_mutex_unlock(&(data->share->print_mutex));
	if (print == 1)
		return ;
	ft_usleep(data->share->t.sleep, data);
}

void	print_think(t_data *data)
{
	pthread_mutex_lock(&(data->share->print_mutex));
	if (data->share->print == 0)
		printf("%lld %d is thinking\n",
			time_stamp() - data->share->start_time, data->sit + 1);
	pthread_mutex_unlock(&(data->share->print_mutex));
}

void	print_fork(t_data *data)
{
	pthread_mutex_lock(&(data->share->print_mutex));
	if (data->share->print == 0)
		printf("%lld %d has taken a fork\n",
			time_stamp() - data->share->start_time, data->sit + 1);
	pthread_mutex_unlock(&(data->share->print_mutex));
}
