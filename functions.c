#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "interfaces.h"

FileLine readLine(FILE * from) {
    FileLine line;
    char dummy;
    fread(&line.page_number, 1, 5, from);
    fread(&line.page_offset, 1, 3, from);
    fread(&dummy, 1, 1, from);
    fread(&line.readwrite, 1, 1, from);
    fread(&dummy, 1, 1, from);
    line.page_number[5] = '\0';
    line.page_offset[3] = '\0';
    return line;
}

void processLine(Table table, FileLine fileline, int no_of_k, int no_of_frames, Statistics * statistics, char * process_name) {
    int i;
    for (i = 0; i < no_of_frames; i++) {
        if (table.lines[i].status >= 0) {                //if not empty 
            if (strcmp(table.lines[i].page_number, fileline.page_number) == 0) {          
                if (strcmp(table.lines[i].process_name, process_name) == 0) {
                    if (fileline.readwrite == 'W' || fileline.readwrite == 'w') {
                        table.lines[i].status = 1;  //if W make this line dirty
                    }
                    statistics->hits++;
                    return;
                }
            }
        } 
    }

    //FWF 
    if (strcmp(process_name, "gcc") == 0) {   
        statistics->faults_gcc++;

        if (statistics->faults_gcc == no_of_k) {
            statistics->faults_gcc = 0;

            for (i = 0; i < no_of_frames; i++) {
                if (table.lines[i].status >= 0) {
                    if (strcmp(table.lines[i].process_name, process_name) == 0) {
                        if (table.lines[i].status == 1) { // dirty
                            statistics->writes++;
                        }
                        table.lines[i].status = -1;
                    }
                }
            }
        }
    } else if (strcmp(process_name, "bzip") == 0) {
        statistics->faults_bzip++;

        if (statistics->faults_bzip == no_of_k) {
            statistics->faults_bzip = 0;

            for (i = 0; i < no_of_frames; i++) {
                if (table.lines[i].status >= 0) {
                    if (strcmp(table.lines[i].process_name, process_name) == 0) {
                        if (table.lines[i].status == 1) { // dirty
                            statistics->writes++;
                        }
                        table.lines[i].status = -1;
                    }
                }
            }
        }
    }

    
    for (i = 0; i < no_of_frames; i++) {
        if (table.lines[i].status == -1) {    //if empty
            strcpy(table.lines[i].page_number, fileline.page_number);
            strcpy(table.lines[i].process_name, process_name);

            if (fileline.readwrite == 'R' || fileline.readwrite == 'r') {
                table.lines[i].status = 0;
            }

            if (fileline.readwrite == 'W' || fileline.readwrite == 'w') {
                table.lines[i].status = 1;
            }

            statistics->reads++;
            break;
        }
    }


    statistics->faults++;
}

Statistics mainloop(int no_of_q, int no_of_k, int no_of_max, int no_of_frames) {
    FILE * bzip = fopen("bzip.trace", "rt");
    FILE * gcc = fopen("gcc.trace", "rt");
    Table table;
    int i;
    int q = no_of_q;
    Statistics s;
    s.faults = 0;
    s.hits = 0;
    s.reads = 0;
    s.writes = 0;
    s.total = 0;
    s.faults_gcc = 0;
    s.faults_bzip = 0;

    if (bzip == NULL) {
        printf("Bzip trace file not found ! \n");
        exit(0);
    }

    if (gcc == NULL) {
        printf("Gcc trace file not found ! \n");
        exit(0);
    }

    table.lines = malloc(no_of_frames * sizeof (struct TableLine));
    for (i = 0; i < no_of_frames; i++) {
        table.lines[i].status = -1;   //-1  all lines empty
    }

    for (i = 0; i < no_of_max; i++) {
        FileLine line;

        if ((i / q) % 2 == 0) {
            line = readLine(bzip);
            processLine(table, line, no_of_k, no_of_frames, &s, "gcc");
        } else {
            line = readLine(gcc);
            processLine(table, line, no_of_k, no_of_frames, &s, "bzip");
        }
    }

    fclose(bzip);
    fclose(gcc);


    return s;
}
