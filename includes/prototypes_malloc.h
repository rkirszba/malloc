#ifndef PROTOTYPES_MALLOC_H
# define PROTOTYPES_MALLOC_H

size_t			align_size(uint8_t type_flag, size_t size);
t_alloc_header	*alloc_access_next(t_alloc_header *alloc);
t_alloc_header	*alloc_access_prev(t_alloc_header *alloc);
t_alloc_header	*alloc_access_th(t_zone *zone, size_t umpteenth);
t_zone			*alloc_access_zone(t_alloc_header *alloc);
t_alloc_header	*alloc_get(size_t size);
t_alloc_header	*alloc_get_available(size_t size);
void			alloc_header_init(t_alloc_header *header,
				size_t size,
				size_t size_prev,
				uint8_t flags);
t_alloc_header	*alloc_join(t_alloc_header *alloc, t_alloc_header *del_alloc);
t_alloc_header	*alloc_join_defrag(t_alloc_header *alloc);
t_alloc_header	*alloc_join_realloc(t_alloc_header *alloc, size_t size);
void			alloc_set_available(t_alloc_header *alloc);
void			alloc_set_unavailable(t_alloc_header *alloc);
int8_t			alloc_split(t_alloc_header *alloc, size_t first_size);
int8_t			alloc_split_malloc(t_alloc_header *alloc, size_t first_size);
void			alloc_update_size_next(t_alloc_header *alloc);
void			available_add(t_alloc_header *alloc);
t_rbt			**available_get_tree(t_alloc_header *alloc);
t_rbt			**available_get_tree_with_memory(size_t size_to_find);
int8_t			available_remove(t_alloc_header *alloc);
uint8_t			can_zone_liberate(t_alloc_header *alloc);
long long		compare_adresses(void *content1, void *content2);
t_alloc_header	*defrag_elem(t_alloc_header *alloc_header);
t_alloc_header	*defragment(t_alloc_header *alloc_header);
void			finish(char **tab);
size_t			first_biggest_than(t_zone *zone, size_t bound);
uint8_t			flag_set_availabilty(uint8_t flag, uint8_t option);
uint8_t			flag_set_pos(uint8_t flag, uint8_t option);
uint8_t			flag_set_type(uint8_t flag, uint8_t option);
size_t			ft_nb_len(intmax_t n, size_t base);
int				get_size_alloc();
size_t			hash_djb2(unsigned char *ptr);
char			**init(void);
uint8_t			is_large_zone(size_t size);
int				main(void);
int8_t			malloc_exit(void);
int8_t			malloc_init(void);
void 			mem_put_color(t_alloc_header *alloc,
				int32_t alloc_nb,
				int8_t header);
t_mem_type		*mem_type_get(uint8_t type);
t_mem_type		*mem_type_get_from_size(size_t size);
void			mem_type_init(t_mem_type *mem_type, int8_t zone_type);
t_zone			*next_smallest(size_t smallest);
void			our_free(void *ptr);
void			*our_malloc(size_t size);
void			padding_after(t_rbt *node);
void			padding_before(t_rbt *node, size_t space);
void			print_alloc(t_alloc_header *alloc);
void			print_alloc_header(t_alloc_header *alloc, size_t *total_octet);
void			print_alloc_memory(t_alloc_header *alloc, size_t *total_octet,
				size_t alloc_nb);
void			print_hex(size_t n);
void			print_hex_zeroes(size_t n);
void			print_malloc_mem(void);
void			print_zone(t_zone *zone, size_t zone_size);
void			print_zone_header(t_zone *zone, size_t *total_octet);
void			print_zone_type(t_zone *zone);
size_t			secure_align_size(size_t size);
void			show_alloc_alloc(void *ptr, size_t size);
void			show_alloc_mem(void);
void			show_alloc_zone(t_zone *z);
t_infos			*static_mem(void);
void			test_read(void *mem, size_t size);
void			test_write(void *mem, size_t size);
void			test_write2(void *mem, size_t size);
void			tree_delete_case_1(t_rbt *node);
void			tree_delete_case_2(t_rbt *node);
void			tree_delete_case_3(t_rbt *node);
void			tree_delete_case_4(t_rbt *node);
void			tree_delete_case_5(t_rbt *node);
void			tree_delete_case_6(t_rbt *node);
t_rbt			*tree_delete_node(t_rbt *node);
void			tree_delete_one_child(t_rbt *node);
void			tree_free(t_rbt *root, t_rbt_free_content *func);
t_rbt			*tree_get_node_th(t_rbt *root, int *umpteenth);
t_rbt			*tree_get_recurse_func(t_rbt *root,
				void *content,
				t_rbt_compare *func);
t_rbt			*tree_get_recurse_func_ll(t_rbt *root, void *content,
				t_rbt_compare_long_long *func);
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
t_rbt			*tree_insert_func_ll(t_rbt *root,
				t_rbt *new_node,
				void *content,
				t_rbt_compare_long_long *func);
void			tree_insert_recurse_func(t_rbt *root,
				t_rbt *n,
				t_rbt_compare *func);
void			tree_insert_recurse_func_ll(t_rbt *root,
				t_rbt *n,
				t_rbt_compare_long_long *func);
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
void			unavailable_add(t_alloc_header *alloc_header);
uint8_t			unavailable_exists(void *maybe_alloc_header);
t_rbt			**unavailable_get_tree(void *ptr);
int8_t			unavailable_remove(void *maybe_alloc_header);
int8_t			unit_test(char **tab);
int8_t			zone_create(t_mem_type *mem_type);
t_alloc_header	*zone_create_large(size_t size);
void			zone_header_init(t_zone_header *header,
				t_zone *next,
				size_t size);
int8_t			zone_liberate(t_zone *zone);
int8_t			zone_liberate_all(t_zone *zone);

#endif