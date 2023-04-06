#include <stdbool.h>
#include "test_bus_lines.h"

int is_sorted_by_distance (BusLine *start, BusLine *end)
{
    while (++start < end) {
        if (start->distance < (start-1)->distance) {
            return 0;
        }
    }

    return 1;
}

int is_sorted_by_duration (BusLine *start, BusLine *end)
{
    while (++start < end) {
        if (start->duration < (start-1)->duration) {
            return 0;
        }
    }

    return 1;
}

int is_sorted_by_name (BusLine *start, BusLine *end)
{
    while (++start < end) {
        if (strcmp(start->name, (start-1)->name) > 0) {
            return 0;
        }
    }

    return 1;
}

int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original)
{
    bool found;
    for(;start_original < end_original; start_original++) {
        found = false;
        BusLine *tmp_sorted = start_sorted;

        for (;tmp_sorted < end_sorted; tmp_sorted++) {
            if (strcmp(tmp_sorted->name, start_original->name) == 0 &&
                    tmp_sorted->distance == start_original->distance &&
                    tmp_sorted->duration == start_original->duration) {
                found = true;
                break;
            }
        }

        if (!found) {
            return 0;
        }
    }

    return 1;
}