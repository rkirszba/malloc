#ifndef PROTOTYPES_MALLOC_H
# define PROTOTYPES_MALLOC_H

t_alloc_header	*alloc_access_next(t_alloc_header *alloc);
t_alloc_header	*alloc_access_th(t_zone *zone, size_t umpteenth);
void			alloc_header_init(t_alloc_header *header, size_t size,
				uint8_t available, uint8_t last);
int8_t			alloc_split(t_alloc_header *alloc, size_t first_size);
void			free_alloc(t_alloc_header *alloc_header);
size_t			ft_nb_len(intmax_t n, size_t base);
t_alloc_header	*get_alloc_header(void* alloc, t_zone *zone);
void			*get_spot(size_t size_to_find);
int				main(int ac, char **av);
int8_t			malloc_exit(void);
int8_t			malloc_init(void);
int8_t			mem_index_add(t_alloc_header *availble_alloc);
uint8_t			mem_index_del(t_alloc_header *unavailble_alloc);
t_alloc_header	*mem_index_get(size_t size);
void 			mem_put_color(t_alloc_header *alloc,
				int8_t alloc_nb,
				int8_t header);
void			our_free(void *alloc);
void			*our_malloc(size_t size);
void			padding_after(t_rbt *node);
void			padding_before(t_rbt *node, size_t space);
void			print_alloc_header(t_alloc_header *alloc, size_t *total_octet);
void			print_alloc_memory(t_alloc_header *alloc, size_t *total_octet,
				size_t alloc_nb);
void			print_malloc_mem(void);
void			print_zone(t_zone *zone, size_t zone_size);
void			print_zone_header(t_zone *zone, size_t *total_octet);
t_infos			*static_mem(void);
void			test_read(void *mem, size_t size);
void			test_write(void *mem, size_t size);
void			tree_delete_case_1(t_rbt *node);
void			tree_delete_case_2(t_rbt *node);
void			tree_delete_case_3(t_rbt *node);
void			tree_delete_case_4(t_rbt *node);
void			tree_delete_case_5(t_rbt *node);
void			tree_delete_case_6(t_rbt *node);
void			tree_delete_one_child(t_rbt *node, t_rbt_free_content *func);
void			tree_free(t_rbt *root, t_rbt_free_content *func);
t_rbt			*tree_grand_parent(t_rbt *node);
int				tree_inorder(t_rbt *root, t_rbt_inorder *func);
void			*tree_inorder_ptr(t_rbt *root, t_rbt_inorder_ptr *func);
int				tree_inrorder(t_rbt *root, t_rbt_inorder *func);
void			*tree_inrorder_ptr(t_rbt *root, t_rbt_inorder_ptr *func);
void			tree_insert_case_1(t_rbt *n);
void			tree_insert_case_2(t_rbt *n);
void			tree_insert_case_3(t_rbt *n);
void			tree_insert_case_4(t_rbt *n);
t_rbt			*tree_insert_func(t_rbt *root, t_rbt *new_node, void *content,
				t_rbt_compare *func);
void			tree_insert_recurse_func(t_rbt *root,
				t_rbt *n,
				t_rbt_compare *func);
void			tree_insert_repair(t_rbt *n);
t_rbt			*tree_new_node(void *content, t_rbt *new_node);
t_rbt			*tree_parent(t_rbt *node);
void			tree_print(t_rbt *node, size_t deep);
void			tree_print_elem(t_rbt *node);
void			tree_recoloring(t_rbt *node);
void			tree_replace_node(t_rbt *node, t_rbt *child);
t_rbt			*tree_root(t_rbt *node);
void			tree_rot_left(t_rbt *node);
void			tree_rot_right(t_rbt *node);
t_rbt			*tree_sibling(t_rbt *node);
t_rbt			*tree_uncle(t_rbt *node);
int8_t			zone_create(t_zone **zone, size_t zone_size);
void			zone_header_init(t_zone_header *header);
int8_t			zone_liberate_all(t_zone *zone, size_t zone_size);

#endif