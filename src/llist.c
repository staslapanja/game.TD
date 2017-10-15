
#include "llist.h"

//ENEMY

struct enemy_t* append_ll_item(struct enemy_t *head,struct enemy_t *a)
{
    if (head == NULL) {
        //if no head exists, a is head
        return a;
    } else {
        struct enemy_t *cursor = head;
        //go to last node
        while(cursor->next != NULL)
            cursor = cursor->next;

        //add the node to the last node
        cursor->next = a;
        a->prev = cursor;
        return head;
    }
}

struct enemy_t* prepend_ll_item(struct enemy_t *head,struct enemy_t *a)
{
    if (head == NULL){
        return a;
    } else {
        a->next = head;
        head->prev = a;
        head = a;
        return head;
    }
}

struct enemy_t* remove_ll_item(struct enemy_t *head,struct enemy_t *a)
{
    if (head != NULL){
        struct enemy_t *cursor;
        //if head
        if (head == a){
            head = head->next;
            free(a);

        //if last and not only one because of previous condition
        } else if (a->next == NULL){
            cursor = a->prev;
            cursor->next = NULL;
            free(a);

        //if in the middle
        } else {
            //previous node
            cursor = a->prev;
            cursor->next = a->next;
            //next node
            cursor = a->next;
            cursor->prev = a->prev;
            free(a);
        }
    }
    return head;
}

struct enemy_t* create_enemy(int x, int y, int path_start, float speed, float health, int credits)
{
    struct enemy_t *a = (struct enemy_t*)malloc(sizeof(struct enemy_t));
    a->position.x = x;
    a->position.y = y;
    a->path_num = path_start;
    a->speed = speed;
    a->max_health = health;
    a->health = health;
    a->credits = credits;
    a->prev = NULL;
    a->next = NULL;

    return a;
}

//TOWERS

struct tower_t* t_append_ll_item(struct tower_t *head,struct tower_t *a)
{
    if (head == NULL) {
        //if no head exists, a is head
        return a;
    } else {
        struct tower_t *cursor = head;
        //go to last node
        while(cursor->next != NULL)
            cursor = cursor->next;

        //add the node to the last node
        cursor->next = a;
        a->prev = cursor;
        return head;
    }
}

struct tower_t* t_prepend_ll_item(struct tower_t *head,struct tower_t *a)
{
    if (head == NULL){
        return a;
    } else {
        a->next = head;
        head->prev = a;
        head = a;
        return head;
    }
}

struct tower_t* t_remove_ll_item(struct tower_t *head,struct tower_t *a)
{
    if (head != NULL){
        struct tower_t *cursor;
        //if head
        if (head == a){
            head = head->next;
            free(a);

        //if last and not only one because of previous condition
        } else if (a->next == NULL){
            cursor = a->prev;
            cursor->next = NULL;
            free(a);

        //if in the middle
        } else {
            //previous node
            cursor = a->prev;
            cursor->next = a->next;
            //next node
            cursor = a->next;
            cursor->prev = a->prev;
            free(a);
        }
    }
    return head;
}

struct tower_t* create_tower(int x, int y, float angle, float damage, int level, float range)
{
    struct tower_t *a = (struct tower_t*)malloc(sizeof(struct tower_t));
    a->position.x = x;
    a->position.y = y;
    a->angle = angle;
    a->damage = damage;
    a->fire_active = false;
    a->level = level;
    a->range = range;
    a->target = NULL;
    a->prev = NULL;
    a->next = NULL;

    return a;
}

//FLOATING TEXT

struct float_text_t* create_float_text(int x, int y, int move_per_tick, int timeout, char text[])
{
    struct float_text_t *a = (struct float_text_t*)malloc(sizeof(struct float_text_t));
    a->x = x;
    a->y = y;
    a->move_per_tick = move_per_tick;
    a->timeout = timeout;
    strcpy(a->text, text);
    a->prev = NULL;
    a->next = NULL;

    return a;
}

struct float_text_t* ft_append_ll_item(struct float_text_t *head,struct float_text_t *a)
{
    if (head == NULL) {
        //if no head exists, a is head
        return a;
    } else {
        struct float_text_t *cursor = head;
        //go to last node
        while(cursor->next != NULL)
            cursor = cursor->next;

        //add the node to the last node
        cursor->next = a;
        a->prev = cursor;
        return head;
    }
}

struct float_text_t* ft_remove_ll_item(struct float_text_t *head,struct float_text_t *a)
{
    if (head != NULL){
        struct float_text_t *cursor;
        //if head
        if (head == a){
            head = head->next;
            free(a);

        //if last and not only one because of previous condition
        } else if (a->next == NULL){
            cursor = a->prev;
            cursor->next = NULL;
            free(a);

        //if in the middle
        } else {
            //previous node
            cursor = a->prev;
            cursor->next = a->next;
            //next node
            cursor = a->next;
            cursor->prev = a->prev;
            free(a);
        }
    }
    return head;
}
