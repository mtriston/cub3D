/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 00:10:15 by mtriston          #+#    #+#             */
/*   Updated: 2020/05/06 18:51:44 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}
