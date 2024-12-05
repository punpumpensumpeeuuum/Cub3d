/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:44:31 by jomendes          #+#    #+#             */
/*   Updated: 2023/10/11 17:10:35 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*s;
	t_list	*hel;

	s = NULL;
	while (lst)
	{
		hel = ft_lstnew(f(lst->content));
		if (!hel)
		{
			ft_lstclear(&s, del);
			return (NULL);
		}
		ft_lstadd_back(&s, hel);
		lst = lst->next;
	}
	return (s);
}
