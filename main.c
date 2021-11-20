#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "interfaces.h"

// ./main q k
// ./main q k max

int main(int argc, char** argv) {
    int no_of_q;
    int no_of_k = 0;
    int no_of_max = 2000000;
    int no_of_frames;

    if (argc == 1) {
        printf("Invalid parameters \n");
        return 1;
    } else if (argc == 3) {
        no_of_q = atoi(argv[1]);
        no_of_k = atoi(argv[2]);
        no_of_frames = 2 * no_of_k;

	printf("-------------------------DATA----------------------------\n\n");
        printf("number of q is %d \n", no_of_q);
        printf("number of k is %d \n", no_of_k);
        printf("number of frames is %d \n", no_of_frames);
	printf("number of max is %d \n\n\n", no_of_max);       
    } else if (argc == 4) {
        no_of_q = atoi(argv[1]);
        no_of_k = atoi(argv[2]);
        no_of_frames = 2 * no_of_k;
        no_of_max = atoi(argv[3]);

	printf("----------------------DATA-------------------------------\n\n");
        printf("number of q is %d \n", no_of_q);
        printf("number of k is %d \n", no_of_k);
        printf("number of frames is %d \n", no_of_frames);
        printf("number of max is %d \n\n\n", no_of_max);
    } else {
        printf("Invalid parameters \n");
        return 1;
    }

    Statistics s = mainloop(no_of_q, no_of_k, no_of_max, no_of_frames);

    printf("----------------------STATISTICS---------------------------\n\n");
    printf("number of hits is %d \n", s.hits);
    printf("number of faults is %d \n", s.faults);
    printf("number of reads is %d \n", s.reads);
    printf("number of writes is %d \n\n", s.writes);
    return 0;
}
