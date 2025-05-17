/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 08:37:16 by haboucha          #+#    #+#             */
/*   Updated: 2025/05/17 11:02:31 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_eat(t_data *data, int i)
{
	if (data->must_eat_count == -1)
		return (0);
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].time_eaten < data->must_eat_count)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (1);
}

int	check_deid_philo(t_data *data, int i)
{
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (gettime() - data->philos[i].last_time_meal >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->philos[i].meal_lock);
			pthread_mutex_lock(&data->dead_lock);
			data->is_dead = 1;
			print_dead(data, i);
			pthread_mutex_unlock(&data->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	if (data->nbr_philos == 1)
		return (NULL);
	while (1)
	{
		if (check_deid_philo(data, i) == 1)
			return (NULL);
		if (check_all_eat(data, i) == 1)
		{
			pthread_mutex_lock(&data->dead_lock);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_mutex(philo, 'f');
	pthread_mutex_lock(philo->right_fork);
	print_mutex(philo, 'f');
	print_mutex(philo, 'e');
	ft_usleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_time_meal = gettime();
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->time_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_mutex(philo, 's');
	ft_usleep(philo->data, philo->data->time_to_sleep);
	print_mutex(philo, 't');
}
