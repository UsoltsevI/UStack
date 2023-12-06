#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ustack.h"

static size_t MIN_CAPACITY_TO_DECREASE = 256;
static size_t MIN_USTACK_CAPACITY = 32;
static size_t NUM_ELEM_TO_OUTPUT = 8;

struct ustack * new_ustack(size_t capacity, const size_t size_elem) {
    assert(size_elem > 0);

    struct ustack *stk = (struct ustack *) calloc(1, sizeof(struct ustack));

    if (stk == NULL) {
        fprintf(stderr, "Failed callocation for stk in func <%s>\n", __func__);
        return NULL;
    }

    if (capacity < MIN_USTACK_CAPACITY)
        capacity = MIN_USTACK_CAPACITY;

    stk->data = calloc(capacity, size_elem);

    if (stk == NULL) {
        fprintf(stderr, "Failed callocation for stk->data in func <%s>\n", __func__);
        return NULL;
    }

    stk->size_elem = size_elem;
    stk->capacity = capacity;
    stk->top = -1;

    return stk;
}

size_t ucapacity(const struct ustack *stk) {
    assert(stk);
    return stk->capacity;
}

size_t usize(const struct ustack *stk) {
    assert(stk);
    return stk->top + 1;
}

int uis_empty(const struct ustack *stk) {
    assert(stk);
    return stk->top == -1;
}

int uis_full(const struct ustack *stk) {
    assert(stk);
    return (stk->top != -1) && (stk->top >= stk->capacity - 1);
}

void upush(struct ustack *stk, const void *new_elem) {
    assert(stk);
    assert(new_elem);

    if (uis_full(stk)) {
        stk->capacity = stk->capacity * 2;
        stk->data = realloc(stk->data, stk->capacity * stk->size_elem);

        if (!stk->data) {
            fprintf(stderr, "failed reallocation for stk->data in func <%s>\n", __func__);
            return;
        }
    }

    stk->top++;
    memcpy(stk->data + stk->top * stk->size_elem, new_elem, stk->size_elem);
}

void upush_wc(struct ustack *stk, const void *new_elem) {
    assert(stk);
    assert(new_elem);

    stk->top++;
    memcpy(stk->data + stk->top * stk->size_elem, new_elem, stk->size_elem);
}

void upop(struct ustack *stk, void *ret) {
    assert(ret);
    assert(stk);

    if (uis_empty(stk)) {
        fprintf(stderr, "stk is empty in func <%s>\n", __func__);
        return;
    }

    memcpy(ret, stk->data + stk->top * stk->size_elem, stk->size_elem);

    delete_top(stk);
}

void upop_wc(struct ustack *stk, void *ret) {
    assert(ret);
    assert(stk);

    memcpy(ret, stk->data + stk->top * stk->size_elem, stk->size_elem);

    delete_top_wc(stk);
}

void upeek(const struct ustack *stk, void *ret) {
    assert(ret);
    assert(stk);

    if (uis_empty(stk)) {
        fprintf(stderr, "stk is empty in func <%s>\n", __func__);
        return;
    }

    memcpy(ret, stk->data + stk->top * stk->size_elem, stk->size_elem);    
}

void upeek_wc(const struct ustack *stk, void *ret) {
    assert(ret);
    assert(stk);

    memcpy(ret, stk->data + stk->top * stk->size_elem, stk->size_elem);    
}

void delete_top(struct ustack *stk) {
    assert(stk);

    if (uis_empty(stk)) {
        fprintf(stderr, "stk is empty in func <%s>\n", __func__);
        return;
    }
    
    stk->top--;

    if ((stk->capacity > MIN_CAPACITY_TO_DECREASE) && (stk->top < stk->capacity / 2)) {
        stk->capacity = stk->capacity / 2;
        stk->data = realloc(stk->data, stk->capacity * stk->size_elem);

        if (!stk->data) {
            fprintf(stderr, "failed reallocation for stk->data in func <%s>\n", __func__);
            return;
        }
    }
}

void delete_top_wc(struct ustack *stk) {
    assert(stk);

    if (stk->top != -1)
        stk->top--;
}

void print_ustack(FILE *fout, const struct ustack *stk, const char *name) {
    assert(stk);
    assert(fout);

    fprintf(fout, "ustack <%s>:\n", name);
    fprintf(fout, "size_elem = %lu, top = %lu, capacity = %lu\n{", stk->size_elem, stk->top, stk->capacity);

    for (size_t i = (10 < stk->top ? stk->top - NUM_ELEM_TO_OUTPUT : 0); i <= stk->top; i++) {
        char *out = (char *) stk->data + i * stk->size_elem;

        for (int j = 0; j < stk->size_elem; j++)
            fprintf(fout, "|%x", *(out + j));

        fprintf(fout, "|, ");
    }

    fprintf(fout, "END}\n");
}

void delete_ustack(struct ustack * *stk) {
    assert(stk);
    assert(*stk);

    free((*stk)->data);
    free(*stk);
}

size_t set_min_capacity_to_decrease(const size_t new_val) {
    assert(new_val > 0);
    size_t prev = MIN_CAPACITY_TO_DECREASE;
    MIN_CAPACITY_TO_DECREASE = new_val;
    return prev;
}

size_t set_min_ustack_capacity(const size_t new_val) {
    assert(new_val > 0);
    size_t prev = MIN_USTACK_CAPACITY;
    MIN_USTACK_CAPACITY = new_val;
    return prev;
}

size_t set_num_elem_to_output(const size_t new_val) {
    size_t prev = NUM_ELEM_TO_OUTPUT;
    NUM_ELEM_TO_OUTPUT = new_val;
    return prev;
}
