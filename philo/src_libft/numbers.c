/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:44:01 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/21 00:44:01 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_fncts.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

long long	ft_atoi(const char *nptr)
{
	long unsigned	n;

	n = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (10 * n + (*nptr - '0') < n)
			return (-1);
		n = 10 * n + (*nptr - '0');
		nptr++;
	}
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr)
		return (-1);
	return (n);
}
