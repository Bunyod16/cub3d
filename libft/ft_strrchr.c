/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 18:32:41 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/28 19:07:31 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(char *str, int c)
{
	int		i;
	char	*p;
	char	chr;

	i = 0;
	p = 0;
	chr = c;
	if (chr == '\0')
		return (&str[ft_strlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == chr)
			p = &str[i];
		if (str[i + 1] == '\0' && chr == '\0')
			p = &str[i + 1];
		i++;
	}
	return (p);
}
