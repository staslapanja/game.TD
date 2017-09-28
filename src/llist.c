
#include "llist.h"

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

struct enemy_t* create_enemy(int x, int y, float speed, float health)
{
    struct enemy_t *a = (struct enemy_t*)malloc(sizeof(struct enemy_t));
    a->position.x = x;
    a->position.y = y;
    a->speed = speed;
    a->max_health = health;
    a->health = health;
    a->prev = NULL;
    a->next = NULL;

    return a;
}
