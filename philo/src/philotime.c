/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philotime.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:43:34 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/21 00:43:34 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_time(t_philo_data *data)
{
	struct timeval	tv;
	long long		m_sec;
	long long		result;

	gettimeofday(&tv, NULL);
	m_sec = tv.tv_sec * 1000;
	pthread_mutex_lock(&data->time_lock);
	m_sec += (tv.tv_usec / 1000);
	if (!data->init_time)
		data->init_time = m_sec;
	result = m_sec - data->init_time;
	pthread_mutex_unlock(&data->time_lock);
	return (result);
}

bool	check_death(t_philo_data *data)
{
	pthread_mutex_lock(&(data->died_lock));
	if (data->died)
	{
		pthread_mutex_unlock(&(data->died_lock));
		return (true);
	}
	pthread_mutex_unlock(&(data->died_lock));
	return (false);
}

int	ft_usleep(long long milliseconds, t_philo_data *data)
{
	long long	start;

	start = get_time(data);
	while ((get_time(data) - start) < milliseconds)
	{
		if (check_death(data))
			return (0);
		usleep(500);
	}
	return (0);
}
