/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:35:07 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:35:07 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void				tree_free(t_rbt *root, t_rbt_free_content *func)
{
	if (root != NULL)
	{
		tree_free(root->left, func);
		func(&root->content);
		tree_free(root->right, func);
	}
}
