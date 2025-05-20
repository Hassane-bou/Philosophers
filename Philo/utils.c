/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 08:37:14 by haboucha          #+#    #+#             */
/*   Updated: 2025/05/20 16:48:14 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_code(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->dead_lock);
	free(data->forks);
	free(data->philos);
}

int	isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	else
		return (1);
}

int	check_parse(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (isdigit(str[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	res;
	int					s;

	i = ((res = 0), 0);
	s = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > LONG_MAX && s == 1)
			return (-1);
		if (res > LONG_MAX && s == -1)
			return (0);
		i++;
	}
	return (res * s);
}
