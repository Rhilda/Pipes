/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhilda <rhilda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 12:37:44 by rhilda            #+#    #+#             */
/*   Updated: 2020/11/01 13:05:13 by rhilda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize < dest_len + 1)
		return (dstsize + src_len);
	if (dstsize > dest_len + 1)
	{
		while (src[i] != '\0' && dest_len + 1 + i < dstsize)
		{
			dest[dest_len + i] = src[i];
			i++;
		}
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
