
#ifndef LLIST_HEADER_H
#define LLIST_HEADER_H

#include "main_header.h"

struct llist_t *create_llist_member(void);

struct llist_t* append_ll_item(struct llist_t *head,void *a);
struct llist_t* prepend_ll_item(struct llist_t *head,void *a);
void free_llist_item(void *a);
struct llist_t* remove_ll_item(struct llist_t *head,struct llist_t *ll,void (*free_struct)(void *));

struct enemy_t* create_enemy(int x, int y, int path_start, float speed, float health, int credits);
void free_enemy_t (void *a);
struct train_t* create_train_unit(bool visible, int x, int y, int path_start, bool loco, float speed, float health, int credits);
void free_train_t (void *a);
struct tower_t* create_tower(int x, int y, float angle, float damage, int level, float range, int price);
void free_tower_t (void *a);
struct float_text_t* create_float_text(int x, int y, int move_per_tick, int timeout, char text[], ALLEGRO_COLOR colour);
void free_float_text_t (void *a);

#endif
