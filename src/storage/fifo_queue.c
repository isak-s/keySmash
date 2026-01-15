#include "fifo_queue.h"
#include <stdlib.h>
#include <memory.h>

#include <assert.h>

FifoQueue fifo_q_new()
{
    return (FifoQueue){
        .first = NULL,
        .last = NULL
    };
}

void fifo_q_destroy(FifoQueue* q)
{
    while (fifo_q_pop(q) != NULL) {}
}

void fifo_q_push(FifoQueue* q, void* cmd, size_t size)
{
    // copy and store by value
    Node* new_n = malloc(sizeof(Node));
    new_n->cmd = malloc(size);
    memcpy(new_n->cmd, cmd, size);

    new_n->next = NULL;

    if (q->first == NULL) {
        q->first = q->last = new_n;
    } else {
        q->last->next = new_n;
        q->last = new_n;
    }
}

void* fifo_q_pop(FifoQueue* q)
{
    if (!q->first) return NULL;

    Node* n = q->first;
    void* cmd = n->cmd;
    q->first = n->next;

    if (!q->first) q->last = NULL;

    free(n);
    return cmd;
}