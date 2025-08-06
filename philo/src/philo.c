/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:43:00 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/21 00:43:00 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_death_2(t_philo *philo, long long start_time, long last_meal)
{
	long long	now;

	now = get_time(philo->data);
	if ((last_meal > 0 && now - last_meal >= philo->data->die_time)
		|| (last_meal == 0 && now - start_time >= philo->data->die_time))
	{
		pthread_mutex_lock(&philo->data->died_lock);
		philo->data->died = 1;
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%lld %d %s\n", now, philo->id, PHILO_DIE);
		pthread_mutex_unlock(&philo->data->print_lock);
		pthread_mutex_unlock(&philo->data->died_lock);
		return (1);
	}
	return (0);
}

static int	check_eat_count(t_philo *philo, long eat_c)
{
	if (philo->data->repeat_count != -2
		&& eat_c >= philo->data->philo_count * philo->data->repeat_count)
	{
		pthread_mutex_lock(&philo->data->died_lock);
		philo->data->died = 1;
		pthread_mutex_unlock(&philo->data->died_lock);
		return (1);
	}
	return (0);
}

static int	philo_check_status(t_philo *philo, long long start_time)
{
	long		eat_c;
	long		last_meal;

	pthread_mutex_lock(&philo->data->eat_count_lock);
	eat_c = philo->data->eat_count;
	pthread_mutex_unlock(&philo->data->eat_count_lock);
	pthread_mutex_lock(&philo->last_meal_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock);
	if (check_death_2(philo, start_time, last_meal)
		|| check_eat_count(philo, eat_c))
		return (1);
	return (0);
}

void	*philo_monitor(t_list *start, t_philo *philo)
{
	t_list		*current;
	long long	start_time;
	int			i;

	current = start;
	start_time = get_time(((t_philo *)start->content)->data);
	while (1)
	{
		i = 0;
		while (i < ((t_philo *)start->content)->data->philo_count)
		{
			philo = current->content;
			if (philo_check_status(philo, start_time))
				return (NULL);
			current = current->next;
			i++;
		}
		ft_usleep(1, philo->data);
	}
}

void	*philo_init(int philo_count, t_list *philos)
{
	int		i;
	t_list	*start;
	t_philo	*philo;

	i = -1;
	start = philos;
	while (++i < philo_count)
	{
		philo = start->content;
		if (pthread_create(&philo->thread_id, NULL, start_thread, start))
			return (philo_exit(philos, NULL, THREAD_FAILED));
		start = start->next;
	}
	philo_monitor(start, NULL);
	i = -1;
	while (++i < philo_count)
	{
		philo = start->content;
		pthread_join(philo->thread_id, NULL);
		start = start->next;
	}
	return (NULL);
}
