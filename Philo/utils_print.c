/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:48:07 by haboucha          #+#    #+#             */
/*   Updated: 2025/05/17 10:29:22 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_data *data, size_t ms)
{
	size_t	time;

	time = gettime();
	while (1)
	{
		pthread_mutex_lock(&data->dead_lock);
		if (data->is_dead == 1)
		{
			pthread_mutex_unlock(&data->dead_lock);
			return ;
		}
		pthread_mutex_unlock(&data->dead_lock);
		if ((gettime() - time) > ms)
			break ;
		usleep(100);
	}
}

void	print_mutex(t_philo *philo, char flag)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->is_dead != 1)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		if (flag == 'f')
			printf("%zu %d has taken a fork\n", gettime()
				- philo->data->start_time, philo->id);
		else if (flag == 'e')
			printf("%zu %d is eating\n", gettime() - philo->data->start_time,
				philo->id);
		else if (flag == 's')
			printf("%zu %d is sleeping\n", gettime() - philo->data->start_time,
				philo->id);
		else if (flag == 't')
			printf("%zu %d is thinking\n", gettime() - philo->data->start_time,
				philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
}

void	print_dead(t_data *data, int i)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%zu %d died\n", gettime() - data->start_time, data->philos[i].id);
	pthread_mutex_unlock(&data->print_mutex);
}
