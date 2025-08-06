/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:43:14 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/21 00:43:14 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	philo_take_forks(t_list *node, t_philo *philo, t_philo *next)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->fork_lock);
		philo_timestamp(node, PHILO_TAKE_FORK);
		pthread_mutex_lock(&next->fork_lock);
		philo_timestamp(node, PHILO_TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(&next->fork_lock);
		philo_timestamp(node, PHILO_TAKE_FORK);
		pthread_mutex_lock(&philo->fork_lock);
		philo_timestamp(node, PHILO_TAKE_FORK);
	}
}

void	philo_actions(t_list *node, t_philo *philo, t_philo *next)
{
	long	stagger;

	philo_take_forks(node, philo, next);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_time(philo->data);
	pthread_mutex_unlock(&philo->last_meal_lock);
	philo_timestamp(node, PHILO_EAT);
	pthread_mutex_lock(&philo->data->eat_count_lock);
	philo->data->eat_count++;
	pthread_mutex_unlock(&philo->data->eat_count_lock);
	ft_usleep(philo->data->eat_time, philo->data);
	pthread_mutex_unlock(&philo->fork_lock);
	pthread_mutex_unlock(&next->fork_lock);
	philo_timestamp(node, PHILO_SLEEP);
	ft_usleep(philo->data->sleep_time, philo->data);
	philo_timestamp(node, PHILO_THINK);
	if (philo->data->eat_time > philo->data->sleep_time)
		ft_usleep(philo->data->eat_time - philo->data->sleep_time, philo->data);
	if (philo->data->philo_count % 2 == 1)
	{
		stagger = (long) philo->data->eat_time / 2;
		ft_usleep((int)stagger, philo->data);
	}
}

void	*start_thread(void *node)
{
	t_philo		*philo;
	t_philo		*next;
	int			i;

	i = -1;
	philo = ((struct s_list *)node)->content;
	next = ((struct s_list *)node)->next->content;
	ft_usleep(!(philo->id % 2) * 2, philo->data);
	pthread_mutex_lock(&philo->data->died_lock);
	while (!philo->data->died
		&& (philo->data->repeat_count == -2 || ++i < philo->data->repeat_count))
	{
		pthread_mutex_unlock(&philo->data->died_lock);
		philo_actions(node, philo, next);
		pthread_mutex_lock(&philo->data->died_lock);
	}
	pthread_mutex_unlock(&philo->data->died_lock);
	return (NULL);
}
