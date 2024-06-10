/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-khad <zel-khad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 13:42:49 by zel-khad          #+#    #+#             */
/*   Updated: 2023/11/15 12:53:39 by zel-khad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	cpy(char const *s1, char const *s2, char *ptr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[j] != '\0')
	{
		ptr[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	cpy(s1, s2, ptr);
	return (ptr);
}
