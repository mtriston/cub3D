/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 00:27:24 by mtriston          #+#    #+#             */
/*   Updated: 2020/05/09 14:56:00 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *ptr;
	t_list *temp;

	if (lst && *lst && del)
	{
		ptr = *lst;
		while (ptr)
		{
			temp = ptr;
			ptr = ptr->next;
			ft_lstdelone(temp, del);
		}
		*lst = NULL;
	}
}
