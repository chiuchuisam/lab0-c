#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

#ifndef strlcpy
#define strlcpy(dst,src,sz) snprintf((dst), (sz), "%s", (src))
#endif

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->len = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q) {
        list_ele_t *cur;
        while (q->head) {
            cur = q->head;
            free(cur->value);
            q->head = cur->next;
            free(cur);
        }
        free(q);
    }
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    char *val;

    if (!q)
        return false;

    newh = malloc(sizeof(list_ele_t));

    if (!newh)
        return false;

    val = malloc(strlen(s) + 1);
    if (!val) {
        free(newh);
        free(val);
        return false;
    }

    strlcpy(val, s, strlen(s) + 1);

    newh->value = val;
    newh->next = q->head;
    q->head = newh;
    if (q->len == 0)
        q->tail = newh;
    q->len++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newh;
    char *val;

    if (!q)
        return false;

    newh = malloc(sizeof(list_ele_t));

    val = malloc(strlen(s) + 1);
    if (!newh || !val) {
        free(newh);
        free(val);
        return false;
    }

    strlcpy(val, s, strlen(s) + 1);

    newh->value = val;
    newh->next = NULL;
    if (q->len == 0) {
        q->head = newh;
    } else {
        q->tail->next = newh;
    }
    q->tail = newh;
    q->len++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *cur;

    if (!q || !q->head)
        return false;
    if (sp) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    cur = q->head;

    q->head = q->head->next;
    q->len--;

    free(cur->value);
    free(cur);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q)
        return 0;
    return q->len;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q)
        return;
    list_ele_t *cur = q->head;
    list_ele_t *tmp, *pre = NULL;

    q->head = q->tail;
    q->tail = cur;
    while (cur) {
        tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
}


/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (!q)
        return;
    /* TODO: Write new sort function without malloc and free. */
}
