#include "sort_bus_lines.h"


void bubble_sort (BusLine *start, BusLine *end)
{
    BusLine *current;

    for (;start < end - 1; --end) {
        for (current = start; current < end - 1; ++current) {
            if (0 < strcmp(current->name, (current+1)->name)) {
                swap(current, current + 1);
            }
        }
    }
}


void quick_sort (BusLine *start, BusLine *end, SortType sort_type)
{
    if (start < end) {
        BusLine *pivot = partition(start, end, sort_type);
        quick_sort(start, pivot, sort_type);
        quick_sort(pivot + 1, end, sort_type);
    }
}


BusLine *partition (BusLine *start, BusLine *end, SortType sort_type)
{
    BusLine *pivot;
    BusLine *first_bigger_then_pivot;
    pivot = start++;
    first_bigger_then_pivot = pivot + 1;

    while (start < end) {
        if (sort_type == DISTANCE) {
            if (start->distance < pivot->distance) {
                swap(first_bigger_then_pivot, start);
                first_bigger_then_pivot++;
            }
        } else if (sort_type == DURATION){
            if (start->duration < pivot->duration) {
                swap(first_bigger_then_pivot, start);
                first_bigger_then_pivot++;
            }
        }

        ++start;
    }

    swap(pivot, first_bigger_then_pivot-1);

    return first_bigger_then_pivot - 1;
}

void swap(BusLine *first, BusLine *second)
{
    BusLine tmp;

    tmp = *first;
    *first = *second;
    *second = tmp;
}