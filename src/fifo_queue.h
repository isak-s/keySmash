#ifndef FIFO_QUEUE_H
#define FIFO_QUEUE_H

#include "ui_commands.h"
//typedef struct DrawCommand DrawCommand;

typedef struct Node {
    void* cmd;
    struct Node* next;
} Node;

typedef struct {
    Node* first;
    Node* last;
} FifoQueue;

FifoQueue fifo_q_new();

void fifo_q_push(FifoQueue* q, void* cmd);

void* fifo_q_pop(FifoQueue* q);

#endif