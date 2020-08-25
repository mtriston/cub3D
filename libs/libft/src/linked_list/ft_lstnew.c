/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 23:59:07 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/18 22:59:06 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *elem;

	if (!(elem = malloc_gc(sizeof(t_list))))
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
