/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 08:37:19 by haboucha          #+#    #+#             */
/*   Updated: 2025/05/20 16:53:25 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arguments(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf("Invalid Arguments !!\n"), 1);
	else
	{
		if (check_parse(argv[1]) != 0 || check_parse(argv[2]) != 0
			|| check_parse(argv[3]) != 0 || check_parse(argv[4]) != 0)
			return (printf("Arguments must be  a number"), 1);
		else if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0
			|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		{
			printf("Arguments must be positive\n");
			return (1);
		}
		else if (ft_atoi(argv[1]) > 200)
			return (printf("You can't use more than 200 philo!!\n"), 1);
	}
	if (argc == 6 && (check_parse(argv[5]) != 0 || ft_atoi(argv[5]) == 0
			|| ft_atoi(argv[1]) <= 0))
	{
		printf("fixe this last argument\n");
		return (1);
	}
	return (0);
}

size_t	gettime(void)
{
	size_t			timems;
	struct timeval	sa;

	if (gettimeofday(&sa, NULL) == -1)
	{
		printf("erreur!!\n");
		return (0);
	}
	timems = (sa.tv_sec * 1000) + (sa.tv_usec / 1000);
	return (timems);
}

int	initialiser(int ac, char *av[], t_data *data)
{
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	else
		data->must_eat_count = -1;
	data->nbr_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->start_time = gettime();
	data->is_dead = 0;
	data->all_eat = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philos);
	if (!data->forks)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!data->philos)
	{
		free(data->forks);
		return (1);
	}
	return (0);
}

int	initialisation(int ac, char *av[], t_data *data)
{
	int	i;

	if (initialiser(ac, av, data) != 0)
		return (printf("Erreur \n"), 1);
	i = -1;
	while (++i < data->nbr_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nbr_philos];
		data->philos[i].time_eaten = 0;
		data->philos[i].data = data;
		data->philos[i].last_time_meal = gettime();
	}
	i = -1;
	while (++i < data->nbr_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].meal_lock, NULL);
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	return (0);
}
