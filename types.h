typedef struct FileLine {
    char page_number[6];
    char page_offset[4];
    char readwrite;
} FileLine;

typedef struct TableLine {
    int status; // 0: clean page 1:dirty page -1: empty page
    char page_number[6];
    char process_name[6];
} TableLine;

typedef struct Table {
    TableLine * lines;
} Table;

typedef struct Statistics {
    int reads;
    int writes;
    int hits;
    int faults;
    int total;
    int faults_gcc;
    int faults_bzip;
} Statistics;

