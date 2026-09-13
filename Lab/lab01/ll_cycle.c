#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    if (!head) return 0;
    node *hare = head->next;
    node *tortoise = head;
    while (hare && hare->next) {
        if (tortoise == hare) return 1;
        hare = hare->next->next;
        tortoise = tortoise->next;
    }
    return 0;
}