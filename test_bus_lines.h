#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H
// and #endif //EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"

/*
 * Function checks if a given array of BusLines is sorted by distance
 * @return: 1 if it is sorted by distance, 0 otherwise.
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);

/*
 * Function checks if a given array of BusLines is sorted by duration
 * @return: 1 if it is sorted by duration, 0 otherwise.
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);

/*
 * Function checks if a given array of BusLines is sorted by name
 * (as in dictionary order).
 * @return: 1 if it is sorted by name, 0 otherwise.
 */
int is_sorted_by_name (BusLine *start, BusLine *end);

/*
 * Checks if two arrays have exactly the same BusLines.
 * Taking into consideration no two different buses can share the same name.
 * @return: 1 if the two arrays are equal. 0 otherwise.
 */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif //EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
