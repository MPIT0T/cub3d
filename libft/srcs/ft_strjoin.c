/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:35:07 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/24 16:05:12 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*nstr;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	nstr = malloc(sizeof(char) * (size + 1));
	if (!nstr)
		return (NULL);
	i = -1;
	while (s1[++i])
		nstr[i] = s1[i];
	j = 0;
	while (s2[j])
		nstr[i++] = s2[j++];
	nstr[i] = '\0';
	return (nstr);
}

char	*ft_strjoin_free(char *s1, char *s2, int f)
{
	char	*nstr;

	nstr = ft_strjoin(s1, s2);
	if (f == 1)
		return (free(s1), nstr);
	else if (f == 2)
		return (free(s2), nstr);
	return (free(s1), free(s2), nstr);
}
