/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:19:07 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/28 11:19:09 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

static int		count(t_rbt *rbt)
{
	(void)rbt;
	return (1);
}

int			tree_len(t_rbt *tree)
{
	return (tree_inorder(tree, count));
}
