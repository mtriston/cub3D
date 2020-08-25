/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtriston <mtriston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:05:47 by mtriston          #+#    #+#             */
/*   Updated: 2020/08/18 22:59:06 by mtriston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char			*ft_strdup(char const *s)
{
	char	*dest;

	if (!(dest = (char *)malloc_gc((ft_strlen(s) + 1) * sizeof(char))))
		return (NULL);
	dest = ft_strcpy(dest, s);
	return (dest);
}
