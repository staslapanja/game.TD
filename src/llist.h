
#ifndef LLIST_HEADER_H
#define LLIST_HEADER_H

#include "main_header.h"

struct enemy_t* append_ll_item(struct enemy_t *head,struct enemy_t *a);
struct enemy_t* prepend_ll_item(struct enemy_t *head,struct enemy_t *a);
struct enemy_t* remove_ll_item(struct enemy_t *head,struct enemy_t *a);
struct enemy_t* create_enemy(int x, int y, int path_start, float speed, float health, int credits);

struct tower_t* t_append_ll_item(struct tower_t *head,struct tower_t *a);
struct tower_t* t_prepend_ll_item(struct tower_t *head,struct tower_t *a);
struct tower_t* t_remove_ll_item(struct tower_t *head,struct tower_t *a);
struct tower_t* create_tower(int x, int y, float angle, float damage, int level, float range);

struct float_text_t* create_float_text(int x, int y, int move_per_tick, int timeout, char text[]);
struct float_text_t* ft_append_ll_item(struct float_text_t *head,struct float_text_t *a);
struct float_text_t* ft_remove_ll_item(struct float_text_t *head,struct float_text_t *a);

#endif
