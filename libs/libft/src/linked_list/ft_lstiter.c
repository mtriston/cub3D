/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 00:32:37 by mtriston          #+#    #+#             */
/*   Updated: 2020/05/09 14:58:28 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *ptr;

	if (lst && f)
	{
		ptr = lst;
		while (ptr)
		{
			f(ptr->content);
			ptr = ptr->next;
		}
	}
}
