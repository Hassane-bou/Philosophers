/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 08:37:11 by haboucha          #+#    #+#             */
/*   Updated: 2025/05/17 17:42:51 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				time_eaten;
	long			last_time_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nbr_philos;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_mutex;
	int				is_dead;
	int				all_eat;
	t_philo			*philos;
}					t_data;

int					main(int argc, char *argv[]);
int					check_arguments(int argc, char **argv);
size_t				gettime(void);
int					initialiser(int ac, char *av[], t_data *data);
int					initialisation(int ac, char *av[], t_data *data);
int					check_all_eat(t_data *data, int i);
int					check_deid_philo(t_data *data, int i);
void				*monitoring(void *arg);
void				eating(t_philo *philo);
int					check_is_one_philo(t_philo *philo);
void				*routine_philo(void *arg);
void				create_thread(t_data *data);
void				ft_usleep(t_data *data, size_t ms);
void				print_mutex(t_philo *philo, char flag);
void				print_dead(t_data *data, int i);
int					isdigit(int c);
int					check_parse(char *str);
int					ft_atoi(const char *str);
void				clean_code(t_data *data);

#endif