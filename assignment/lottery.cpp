/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			lottery.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lottery.h"

#define UUID_LEN 36
#define MAX_TIP_LEN 17
#define MAX_LINE_LEN (UUID_LEN + 1 + MAX_TIP_LEN + 1)

char _csv_separator;
int drawing[TIP_SIZE];
FILE* stream;

bool contains_tip(int* tip, int tipDigit);
int get_count_of_lines(FILE* stream);

bool init_lottery (const char *csv_file, char csv_separator) {
    stream = fopen(csv_file, "r");
    _csv_separator = csv_separator;
    if(stream == 0) return false;
    return true;
}

bool get_tip(int tip_number, int tip[TIP_SIZE])
{
    if (tip_number >= 0 && tip_number < 1000000) {
        fseek(stream, 0, SEEK_SET);
        int currentLine = 0;
        while (currentLine < tip_number) {
            while (!feof(stream) && fgetc(stream) == '\n') {
                currentLine++;
                break;
            }
        }

        fseek(stream, (UUID_LEN + 1) * sizeof(char), SEEK_CUR);

        char tip[MAX_TIP_LEN];
        fgets(tip, MAX_TIP_LEN, stream);

        char delimiter[2] = { _csv_separator, '\0' };
        char *pointer = strtok(tip, delimiter);

        int position = 0;
        while(pointer != NULL) {
            int tipNumber = atoi(pointer);
            tip[position] = tipNumber;
            pointer = strtok(NULL, delimiter);
            position++;
        }
        return true;
    }

    return false;
}
bool set_drawing (int drawing_numbers[TIP_SIZE]) {
    for (int i = 0; i < TIP_SIZE; i++) {
        if (drawing_numbers[i] > 45 || drawing_numbers[i] <= 0) {
            return false;
        }
    }

    for (int i = 0; i < TIP_SIZE; i++) {
        drawing[i] = drawing_numbers[i];
    }
    return true;
}

bool is_invalid_tip(int tip_number)
{
    int previous = ftell(stream);
    fseek(stream, 0, SEEK_END);
    int last = ftell(stream);
    fseek(stream, previous, SEEK_SET);
    return tip_number * MAX_LINE_LEN > last;
}

bool is_drawing_set()
{
    for (int i = 0; i < TIP_SIZE; i++) {
        if (drawing[i] == 0) {
            return false;
        }
    }
    return true;
}

int get_tip_result (int tip_number) {
    if (tip_number < 0 || tip_number >= get_count_of_lines(stream)) {
        return -2;
    }

    if (!is_drawing_set()) {
        return -1;
    }

    int csv_tip[TIP_SIZE];
    get_tip(tip_number, csv_tip);

    int right_guessed = 0;
    for (int i = 0; i < TIP_SIZE; i++) {
        if (contains_tip(drawing, csv_tip[i])) {
            right_guessed++;
        }
    }
    return right_guessed;
}

int get_count_of_lines (FILE* stream) {
    int previous = ftell(stream);
    fseek(stream, 0, SEEK_SET);
    int lines = 1;
    while (!feof(stream)) {
        if (fgetc(stream) == '\n') {
            lines++;
        }
    }
    fseek(stream, previous, SEEK_SET);
    return lines;
}

int get_right_tips_count (int right_digits_count) {
    if (!is_drawing_set() || right_digits_count < 0 || right_digits_count > TIP_SIZE) {
        return -1;
    }

    int count = 0;
    int result;
    int numOfLines = get_count_of_lines(stream);
    for (int i = 0; i < numOfLines; i++) {
        result = get_tip_result(i);
        if (result == right_digits_count) {
            count++;
        }
    }
    return count;
}

bool contains_tip (int* tip, int tipDigit) {
    for (unsigned int i = 0; i < TIP_SIZE; i++) {
        if (tip[i] == tipDigit) {
            return true;
        }
    }
    return false;
}
