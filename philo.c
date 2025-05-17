/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 08:37:08 by haboucha          #+#    #+#             */
/*   Updated: 2025/05/17 11:37:24 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_is_one_philo(t_philo *philo)
{
	if (philo->data->nbr_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_mutex(philo, 'f');
		pthread_mutex_unlock(philo->left_fork);
		ft_usleep(philo->data, philo->data->time_to_die);
		print_dead(philo->data, 1);
		return (1);
	}
	return (0);
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (check_is_one_philo(philo) == 1)
		return (NULL);
	print_mutex(philo, 't');
	if (philo->id % 2 == 0)
		ft_usleep(philo->data, philo->data->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
		eating(philo);
	}
	return (NULL);
}

void	create_thread(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, routine_philo,
			&data->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitoring, data);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (check_arguments(argc, argv) != 0)
		return (1);
	else
	{
		if (initialisation(argc, argv, &data) != 0)
			return (1);
		create_thread(&data);
		clean_code(&data);
	}
	return (0);
}
