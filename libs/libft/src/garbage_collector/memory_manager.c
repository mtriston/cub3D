/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 23:32:18 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/19 21:30:09 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static void		gc_lstclear(t_list **lst)
{
	t_list *ptr;
	t_list *temp;

	if (lst && *lst)
	{
		ptr = *lst;
		while (ptr)
		{
			temp = ptr;
			ptr = ptr->next;
			free(temp->content);
			free(temp);
			
		}
		*lst = NULL;
	}
}

static t_list	*gc_lstnew(void *content)
{
	t_list *elem;

	if (!(elem = malloc(sizeof(t_list))))
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

static void	gc_lstremove(t_list **root, void *data)
{
	t_list *node;
	t_list *temp;
	int		i;

	if (root == NULL || *root == NULL)
		return ;
	while (data == (*root)->content)
	{
		temp = (*root)->next;
		free((*root)->content);
		free(*root);
		(*root) = temp;
	}
	node = *root;
	temp = *root;
	i = 0;
	while (node != NULL)
	{
		if (data == node->content)
		{
			temp->next = node->next;
			free(node->content);
			free(node);
			node = temp;
			i = 0;
		}
		if (i > 0)
			temp = temp->next;
		if (node != NULL)
			node = node->next;
		i++;
	}
}
void			memory_manager(void *ptr, int action)
{
	static t_list *collector = NULL;

	if (ptr == NULL)
		gc_lstclear(&collector);
	else if (action == ADD)
		ft_lstadd_front(&collector, gc_lstnew(ptr));
	else if (action == REMOVE)
		gc_lstremove(&collector, ptr);
}
