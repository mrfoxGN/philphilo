#ifndef LIBFT_TOOLS_H

# define LIBFT_TOOLS_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/* Returns length of string */
size_t		ft_strlen(const char *s);

/* Prints string with write */
int			ft_putstr_fd(char *s, int fd);

/* Returns 1 if a char is of a space form: space, tab, etc */
int			ft_isspace(char c);

/* Returns equivalent int from a string, or -1 */
long long	ft_atoi(const char *nptr);

/* Adds a node at the end of a list */
void		ft_lstadd_back(t_list **lst, t_list *newnode);

/* Creates new node */
t_list		*ft_lstnew(void *content);

/* Returns last node of linked list */
t_list		*ft_lstlast(t_list *lst);

/* Deletes every node of linked list */
void		ft_lstclear(t_list **lst, void (*del)(void*));

#endif
