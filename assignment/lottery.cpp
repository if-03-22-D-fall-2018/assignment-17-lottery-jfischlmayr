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
FILE* stream;

bool init_lottery (const char *csv_file, char csv_separator) {
    stream = fopen(csv_file, "r");
    _csv_separator = csv_separator;
    if(stream == 0) return false;
    return true;
}
/*bool get_tip (int tip_number, int tip[TIP_SIZE]) {
    if (tip_number < 0 || tip_number > ) return false;
    fseek(stream, tip_number * 4, SEEK_SET);
    char line[MAX_LINE_LEN];
    fgets(line, MAX_LINE_LEN, stream);

    return true;
}*/
bool get_tip(int tip_number, int tip[TIP_SIZE])
{
    //Validate tip number
    if (tip_number < 0 || tip_number >= 1000000)
        return false;

    //Jump to tip
    //Iterate to target line start (can't use fseek() because each line is differently long)
    rewind(stream);
    int currentLine = 0; //Representing the current line in file
    while (currentLine < tip_number)
        for (;;) {
            if (fgetc(stream) == '\n') {
                currentLine++;
                break;
            }
        }

    //Skip UUID (+first separator)
    fseek(stream, UUID_LEN + 1, SEEK_CUR);

    //Read tip string
    char tipString[MAX_TIP_LEN];
    fgets(tipString, MAX_TIP_LEN, stream);

    //Split tip string
    char delimiter[2] = { _csv_separator, '\0' };
    char *ptr = strtok(tipString, delimiter);

    int pos = 0;
    while(ptr != NULL) {
        int tipNumber = atoi(ptr);
        tip[pos] = tipNumber;
        ptr = strtok(NULL, delimiter);
        pos++;
    }
    return true;
}
bool set_drawing (int drawing_numbers[TIP_SIZE]) {
    return false;
}
int get_tip_result (int tip_number) {
    return 0;
}
int get_right_tips_count (int right_digits_count) {
    return 0;
}
