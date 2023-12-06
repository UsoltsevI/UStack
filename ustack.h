#ifndef USTACK_H_INCLUDED
#define USTACK_H_INCLUDED

struct ustack {
    void *data;
    size_t size_elem;
    size_t top;
    size_t capacity;
};

//wc = without checks and reallocations

struct ustack * new_ustack(size_t capacity, const size_t size_elem);
size_t ucapacity(const struct ustack *stk);
size_t usize(const struct ustack *stk);
int uis_empty(const struct ustack *stk);
int uis_full(const struct ustack *stk);
void upush(struct ustack *stk, const void *new_elem);
void upush_wc(struct ustack *stk, const void *new_elem);
void upop(struct ustack *stk, void *ret);
void upop_wc(struct ustack *stk, void *ret);
void upeek(const struct ustack *stk, void *ret);
void upeek_wc(const struct ustack *stk, void *ret);
void delete_top(struct ustack *stk);
void delete_top_wc(struct ustack *stk);
void print_ustack(FILE *fout, const struct ustack *stk, const char *name);
void delete_ustack(struct ustack * *stk);
size_t set_min_capacity_to_decrease(const size_t new_val);
size_t set_min_ustack_capacity(const size_t new_val);
size_t set_num_elem_to_output(const size_t new_val);

#define PRINT_USTACK(file, stk) print_ustack(file, stk, #stk);

#endif //USTACK_H_INCLUDED