/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:37:28 by iel-amra          #+#    #+#             */
/*   Updated: 2022/08/15 10:28:53 by iel-amra         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{	
	t_list	*new;
	t_list	*elem;
	void	*new_content;

	new = (void *) 0;
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
		{
			del(new_content);
			ft_lstclear(&new, del);
			return ((void *) 0);
		}
		elem = ft_lstnew(new_content);
		if (!elem)
		{	
			ft_lstclear(&new, del);
			return ((void *) 0);
		}
		ft_lstadd_back(&new, elem);
		lst = lst->next;
	}
	return (new);
}
