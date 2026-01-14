#ifndef FIFO_QUEUE_H
#define FIFO_QUEUE_H

#include <stddef.h>

typedef struct Node {
    void* cmd;
    struct Node* next;
} Node;

typedef struct {
    Node* first;
    Node* last;
} FifoQueue;

FifoQueue fifo_q_new();

void fifo_q_push(FifoQueue* q, void* cmd, size_t size);

void* fifo_q_pop(FifoQueue* q);

void fifo_q_destroy(FifoQueue* q);

#endif