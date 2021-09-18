/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhilda <rhilda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:19:30 by rhilda            #+#    #+#             */
/*   Updated: 2020/10/30 17:43:36 by rhilda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isupper(int c)
{
	return ((65 <= c) && (90 >= c));
}

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c + 32);
	return (c);
}