/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 00:06:45 by mtriston          #+#    #+#             */
/*   Updated: 2020/05/11 18:47:32 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int		ft_lstsize(t_list *lst)
{
	t_list	*ptr;
	int		i;

	if (!lst)
		return (0);
	ptr = lst;
	i = 1;
	while (ptr->next)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
