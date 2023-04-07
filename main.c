#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sort_bus_lines.h"
#include "test_bus_lines.h"

#define MAX_DISTANCE 1000
#define MIN_DURATION 10
#define MAX_DURATION 100
#define ONE_ARGUMENT_INPUT 2
#define FULL_SCAN 3
#define DECIMAL 10
#define FIRST_ARGUMENT argv[1]
#define MAX_LINE_LENGTH 60
#define NAME_LEN 21
#define BY_DURATION_OPTION "by_duration"
#define BY_DISTANCE_OPTION "by_distance"
#define BY_NAME_OPTION "by_name"
#define TEST_OPTION "test"

/*
 * DELETE THIS. WAS FOR EXPIRIMENTING
 */
void print_all_buslines(BusLine *start, BusLine *end);
void print_busline(BusLine b);

typedef enum InputType {
    INVALID, BY_DISTANCE, BY_DURATION, BY_NAME, TEST
} InputType;

/*
 * checks the arguments and concludes what type of input was received
 * @return: enum type of the input
 */
InputType get_input_type(int argc, char *argv[]);

/*
 * Asks for number of lines from user and returns the number once received
 * @return: positive integer representing number of lines
 */
int get_number_of_lines(void);

/*
 * Requests from the user input in the 'name,distance,duration' format.
 * Once input in the correct format gets accepted, the function stores it
 * in the args referenced.
 * @return: no return but the argument's references get modified.
 */
void get_valid_input(char *name, int *distance, int *duration);

/*
 * Checks if the name follows the bus line name guidelines
 * @return: true if it does, false otherwise
 */
bool valid_busline_name(char *name);

/*
 * Checks if the string of distance follows the bus line distance guidelines
 * @return: true if it does, false otherwise
 */
bool valid_busline_distance(char *distance);

/*
 * Checks if the string of duration follows the bus line duration guidelines
 * @return: true if it does, false otherwise
 */
bool valid_busline_duration(char *duration);

/*
 * CRITICAL - WRITE A DESCRIPTION
 */
void test(BusLine *start_original, BusLine *end_original);

/**
 * TODO add documentation
 */
int main (int argc, char *argv[])
{
    const InputType input_type = get_input_type(argc, argv);
    int line_count, distance, duration;
    char line_name[NAME_LEN];
    BusLine *buslines, *next_busline_ptr;

    if (input_type == INVALID) {
        printf("USAGE: " "Acceptable arguments are 'by_name',"
               "'by_duration or 'by_distance'. "
               "Please enter one argument\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of lines. Then enter\n");

    line_count = get_number_of_lines();

    buslines = (BusLine *) malloc(sizeof(BusLine) * line_count);

    if (buslines == NULL) {
        printf("ERROR: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (next_busline_ptr = buslines;
         next_busline_ptr < buslines + line_count;next_busline_ptr++) {
        get_valid_input(line_name,&distance, &duration);

        BusLine next_busline;
        strcpy(next_busline.name, line_name);
        next_busline.distance = distance;
        next_busline.duration = duration;
        *next_busline_ptr = next_busline;
    }

    if (input_type == TEST) {
        test(buslines, buslines + line_count);
    } else if (input_type == BY_NAME) {
        bubble_sort(buslines, buslines + line_count);
    }
    else if (input_type == BY_DISTANCE) {
        quick_sort(buslines, buslines + line_count, DISTANCE);
    }
    else if (input_type == BY_DURATION) {
        quick_sort(buslines, buslines + line_count, DURATION);
    }

    print_all_buslines(buslines, buslines + line_count);

    free(buslines);

    return EXIT_SUCCESS;
}

int get_number_of_lines(void)
{
    char buffer[MAX_LINE_LENGTH];
    int line_count = 0;

    fgets(buffer, MAX_LINE_LENGTH, stdin);
    line_count = (int) strtol(buffer, NULL , DECIMAL);

    while (line_count < 1) {
        printf("ERROR: number of lines should be a positive integer\n");
        fgets(buffer, MAX_LINE_LENGTH, stdin);
        line_count = (int) strtol(buffer, NULL , DECIMAL);
    }

    return line_count;
}

InputType get_input_type(int argc, char *argv[]) {
    if (argc != ONE_ARGUMENT_INPUT) {
        return INVALID;
    }

    if (strcmp(FIRST_ARGUMENT, BY_DURATION_OPTION) == 0) {
        return BY_DURATION;
    }
    if (strcmp(FIRST_ARGUMENT, BY_DISTANCE_OPTION) == 0) {
        return BY_DISTANCE;
    }
    if (strcmp(FIRST_ARGUMENT, BY_NAME_OPTION) == 0) {
        return BY_NAME;
    }
    if (strcmp(FIRST_ARGUMENT, TEST_OPTION) == 0) {
        return TEST;
    }

    return INVALID;
}

void get_valid_input(char *name, int *distance, int *duration)
{
    char buffer[MAX_LINE_LENGTH];
    char line_distance[NAME_LEN], line_duration[NAME_LEN];

    while(true) {
        printf("Enter line info. Then enter\n");
        fgets(buffer, MAX_LINE_LENGTH, stdin);
        if(sscanf(buffer, "%[^,],%[^,],%[^\n]]",  name,
                  line_distance, line_duration) == FULL_SCAN) {
            if (valid_busline_name(name) &&
                valid_busline_distance(line_distance) &&
                valid_busline_duration(line_duration)) {
                *distance = (int) strtol(line_distance, NULL, DECIMAL);
                *duration = (int) strtol(line_duration, NULL, DECIMAL);
                break;
            }
        }
        else {
            printf("ERROR: format for line input is "
                   "[line name],[distance],[duration]\n");
        }
    }
}

bool valid_busline_name(char *name)
{
    char c;

    while ((c = *name) != '\0') {
        if (!(('0' <= c && c <= '9') || ('a' <= c && c <= 'z'))) {
            printf( "ERROR: bus name should contain only "
                    "digits and small chars\n");
            return false;
        }
        name++;
    }

    return true;
}

bool valid_busline_distance(char *distance)
{
    char c;

    if (MAX_DISTANCE < strtol(distance, NULL, DECIMAL)) {
        printf("ERROR: distance should be an integer"
               " between 0 and %d\n", MAX_DISTANCE);
        return false;
    }

    while ((c = *distance) != '\0') {
        if (c < '0' || '9' < c) {
            printf("ERROR: distance should be an integer"
                   " between 0 and %d\n", MAX_DISTANCE);
            return false;
        }
        distance++;
    }

    return true;
}

bool valid_busline_duration(char *duration)
{
    char c;
    long tmp_duration = strtol(duration, NULL, DECIMAL);

    if (tmp_duration < MIN_DURATION || MAX_DURATION < tmp_duration) {
        printf("ERROR: duration should be an integer "
               "between %d and %d\n", MIN_DURATION, MAX_DURATION);
        return false;
    }

    while ((c = *duration) != '\0') {
        if (c < '0' || '9' < c) {
            printf("ERROR: duration should be an integer "
                   "between %d and %d\n", MIN_DURATION, MAX_DURATION);
            return false;
        }
        duration++;
    }

    return true;
}

void test(BusLine *start_original, BusLine *end_original)
{
    int n = (int) (end_original - start_original);
    BusLine *start_sorted = (BusLine *) malloc(sizeof(BusLine) * n);
    BusLine *end_sorted = start_sorted + n;
    memcpy(start_sorted, start_original, n);

    quick_sort(start_sorted, end_sorted, DISTANCE);
    if (is_sorted_by_distance(start_sorted, end_sorted)) {
        printf("TEST 1 PASSED: ");
    } else {
        printf("TEST 1 FAILED: ");
    }
    if (is_equal(start_sorted, end_sorted, start_original, end_original)) {
        printf("TEST 2 PASSED: ");
    } else {
        printf("TEST 2 FAILED: ");
    }
    quick_sort(start_sorted, end_sorted, DURATION);
    if (is_sorted_by_duration(start_sorted, end_sorted))  {
        printf("TEST 3 PASSED: ");
    } else {
        printf("TEST 3 FAILED: ");
    }
    if (is_equal(start_sorted, end_sorted, start_original, end_original))  {
        printf("TEST 4 PASSED: ");
    } else {
        printf("TEST 4 FAILED: ");
    }
    bubble_sort(start_sorted, end_sorted);
    if (is_sorted_by_name(start_sorted, end_sorted))  {
        printf("TEST 5 PASSED: ");
    } else {
        printf("TEST 5 FAILED: ");
    }
    if (is_equal(start_sorted, end_sorted, start_original, end_original))  {
        printf("TEST 6 PASSED: ");
    } else {
        printf("TEST 6 FAILED: ");
    }
}

void print_busline(BusLine b)
{
    printf("%s,%d,%d\n", b.name, b.distance, b.duration);
}

void print_all_buslines(BusLine *start, BusLine *end)
{
    while (start != end) {
        print_busline(*(start)++);
    }
}

