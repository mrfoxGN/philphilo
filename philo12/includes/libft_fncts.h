/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fncts.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:52:30 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/21 13:52:30 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FNCTS_H

# define LIBFT_FNCTS_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

size_t		ft_strlen(const char *s);

int			ft_putstr_fd(char *s, int fd);

int			ft_isspace(char c);

long long	ft_atoi(const char *nptr);

void		ft_lstadd_back(t_list **lst, t_list *newnode);

t_list		*ft_lstnew(void *content);

t_list		*ft_lstlast(t_list *lst);

void		ft_lstclear(t_list **lst, void (*del)(void*));

#endif
