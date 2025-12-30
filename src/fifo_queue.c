#include "fifo_queue.h"
#include <stdlib.h>

#include <assert.h>

FifoQueue fifo_q_new()
{
    return (FifoQueue){
        .first = NULL,
        .last = NULL
    };
}

void fifo_q_push(FifoQueue* q, void* cmd)
{
    Node* new_n = (Node*)malloc(sizeof(Node));
    new_n->cmd = cmd;
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
    if (q->first == NULL) {
        return NULL;
    }

    Node* n = q->first;
    void* cmd = n->cmd;

    q->first = n->next;
    if (q->first == NULL) {
        q->last = NULL;
    }

    free(n);

    return cmd;
}