/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 15:44:41 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/28 19:07:08 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

unsigned long	ft_strlcat(void *dest, const void *src, unsigned int l)
{
	unsigned int	i;
	unsigned int	destlen;
	unsigned int	srclen;
	char			*d;
	char			*s;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	if (l == 0)
		return (srclen);
	if (l - 1 < destlen)
		return (srclen + l);
	while (destlen + i < (l - 1) && s[i] != '\0')
	{
		d[destlen + i] = s[i];
		i++;
	}
	d[destlen + i] = '\0';
	return (destlen + srclen);
}
