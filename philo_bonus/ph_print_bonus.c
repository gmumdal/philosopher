/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongsh <hyeongsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 13:41:23 by hyeongsh          #+#    #+#             */
/*   Updated: 2023/12/29 20:16:25 by hyeongsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_bonus.h"

void	print_eat(t_data *data)
{
	sem_wait(data->print_sem);
	printf("%lld %d is eating\n", time_stamp() - data->start_time,
		data->sit + 1);
	sem_post(data->print_sem);
	ph_usleep(data->t.eat);
}

void	print_sleep(t_data *data)
{
	sem_wait(data->print_sem);
	printf("%lld %d is sleeping\n", time_stamp() - data->start_time,
		data->sit + 1);
	sem_post(data->print_sem);
	ph_usleep(data->t.sleep);
}

void	print_think(t_data *data)
{
	sem_wait(data->print_sem);
	printf("%lld %d is thinking\n", time_stamp() - data->start_time,
		data->sit + 1);
	sem_post(data->print_sem);
}

void	print_fork(t_data *data)
{
	sem_wait(data->print_sem);
	printf("%lld %d has taken a fork\n", time_stamp() - data->start_time,
		data->sit + 1);
	sem_post(data->print_sem);
}
