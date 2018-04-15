
#include "llist.h"


//LINKED LIST OPERATIONS
struct llist_t *create_llist_member(void)
{
    struct llist_t *a = (struct llist_t*)malloc(sizeof(struct llist_t));
    return a;
};

struct llist_t* append_ll_item(struct llist_t *head,void *a)
{
    struct llist_t *ll = create_llist_member();
    if (head == NULL) {
        //if no head exists, a is head
        ll->ptr = a;
        ll->next = NULL;
        ll->prev = NULL;
        return ll;
    } else {
        struct llist_t *cursor = head;
        //go to last node
        while(cursor->next != NULL)
            cursor = cursor->next;

        //add the node to the last node
        ll->ptr = a;
        ll->next = NULL;
        cursor->next = ll;
        ll->prev = cursor;
        return head;
    }
}

struct llist_t* prepend_ll_item(struct llist_t *head,void *a)
{
    struct llist_t *ll = create_llist_member();
    if (head == NULL){
        //if no head exists, a is head
        ll->ptr = a;
        ll->next = NULL;
        ll->prev = NULL;
        return ll;
    } else {
        ll->ptr = a;
        ll->next = head;
        ll->prev = NULL;
        head->prev = ll;
        return ll;
    }
}

void free_llist_item(void *a)
{
    struct enemy_t *enemy;
    struct tower_t *tower;
    struct float_text_t *float_text;
    //first item in any llist struct is int id!
    int *id_ptr,id;
    //void pointer to integer pointer
    id_ptr = a;
    //get integer value
    id = *id_ptr;
    //determine struct from this id
    switch(id){
        case(LLIST_ENEMY):
            enemy = a;
            free(enemy);
            break;
        case(LLIST_TOWER):
            tower = a;
            free(tower);
            break;
        case(LLIST_FLOAT_TEXT):
            float_text = a;
            free(float_text);
            break;
        default:
            break;
    }

}

struct llist_t* remove_ll_item(struct llist_t *head,struct llist_t *ll,void (*free_struct)(void *))
{
    if (head != NULL){
        struct llist_t *cursor;
        //if head
        if (head == ll){
            cursor = head;
            head = head->next;
            free_struct(ll->ptr);
            free(ll);

        //if last and not only one because of previous condition
        } else if (ll->next == NULL){
            cursor = ll->prev;
            cursor->next = NULL;
            free_struct(ll->ptr);
            free(ll);

        //if in the middle
        } else {
            //previous node
            cursor = ll->prev;
            cursor->next = ll->next;
            //next node
            cursor = ll->next;
            cursor->prev = ll->prev;
            free_struct(ll->ptr);
            free(ll);
        }
    }
    return head;
}

//ENEMY
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

    return a;
}

void free_enemy_t (void *a)
{
    struct enemy_t *b = a;
    free(b);
}

//TRAINS
struct train_t* create_train_unit(bool visible, int x, int y, int path_start, bool loco, float speed, float health, int credits)
{
    struct train_t *a = (struct train_t*)malloc(sizeof(struct train_t));
    a->visible = visible;
    a->position.x = x;
    a->position.y = y;
    a->angle = 0;
    a->path_num = path_start;
    a->locomotive = loco;
    a->speed = speed;
    a->max_health = health;
    a->health = health;
    a->credits = credits;
    a->prew_train = NULL;
    a->next_train = NULL;

    return a;
}

void free_train_t (void *a)
{
    struct train_t *b = a;
    free(b);
}

//TOWERS
struct tower_t* create_tower(int x, int y, float angle, float damage, int level, float range, int price)
{
    struct tower_t *a = (struct tower_t*)malloc(sizeof(struct tower_t));
    a->position.x = x;
    a->position.y = y;
    a->angle = angle;
    a->damage = damage;
    a->fire_active = false;
    a->level = level;
    a->range = range;
    a->price = price;
    a->e_target = NULL;
    a->t_target = NULL;

    return a;
}

void free_tower_t (void *a)
{
    struct tower_t *b = a;
    free(b);
}

//FLOATING TEXT
struct float_text_t* create_float_text(int x, int y, int move_per_tick, int timeout, char text[], ALLEGRO_COLOR colour)
{
    struct float_text_t *a = (struct float_text_t*)malloc(sizeof(struct float_text_t));
    a->x = x;
    a->y = y;
    a->move_per_tick = move_per_tick;
    a->timeout = timeout;
    strcpy(a->text, text);
    a->colour = colour;

    return a;
}

void free_float_text_t (void *a)
{
    struct float_text_t *b = a;
    free(b);
}
