/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:11:45 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/18 22:59:06 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *ptr;

	if (nmemb != 0 && size != 0 && size * nmemb / nmemb != size)
		return (NULL);
	if (!(ptr = (void *)malloc_gc(nmemb * size)))
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
