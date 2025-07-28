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

static t_philo_data	parse_args(char **argv)
{
	t_philo_data	d;

	d.philo_count = ft_atoi(argv[1]);
	if (d.philo_count < 0)
		philo_exit(NULL, argv[1], INV_PHILO_COUNT);
	if (d.philo_count > 800)
		philo_exit(NULL, argv[1], TOO_MANY_PHILO);
	d.die_time = ft_atoi(argv[2]);
	if (d.die_time < 0)
		philo_exit(NULL, argv[2], INV_DIE_TIME);
	d.eat_time = ft_atoi(argv[3]);
	if (d.eat_time < 0)
		philo_exit(NULL, argv[3], INV_EAT_TIME);
	d.sleep_time = ft_atoi(argv[4]);
	if (d.sleep_time < 0)
		philo_exit(NULL, argv[4], INV_SLEEP_TIME);
	d.repeat_count = -2;
	d.die_time += 10;
	if (argv[5])
	{
		d.repeat_count = ft_atoi(argv[5]);
		if (d.repeat_count == -1 || !d.repeat_count)
			philo_exit(NULL, argv[5], INV_REPEAT_COUNT);
	}
	return (d);
}

int	main(int argc, char **argv)
{
	t_philo_data	d;
	t_list			*philos;

	if (argc != 5 && argc != 6)
	{
		philo_exit(NULL, NULL, INV_ARGS);
		printf("\nusage: philo <philo_count> <die_time>");
		printf(" <eat_time> <sleep_time> [<repeat_times>]\n");
		return (1);
	}
	d = parse_args(argv);
	if (d.philo_count <= 0 || d.philo_count > 800 || d.die_time < -0
		|| d.eat_time < 0 || d.sleep_time < 0 || d.repeat_count < 0
		|| !d.repeat_count)
		return (1);
	d.init_time = philo_get_time();
	d.died = 0;
	d.eat_count = 0;
	pthread_mutex_init(&d.died_lock, NULL);
	pthread_mutex_init(&d.eat_count_lock, NULL);
	philos = philo_lst(&d);
	ft_lstlast(philos)->next = philos;
	philo_init(d.philo_count, philos);
	philo_exit(philos, NULL, END);
	return (0);
}
