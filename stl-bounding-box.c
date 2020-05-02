#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Structure to hold dimensions as x, y, z */
struct dims {
    float x;
    float y;
    float z;
};

typedef struct dims dim_t;

/* structure to carry minimum and maximum vertex positions across
 * fucntion calls */
struct dim_tuple {
    dim_t min;
    dim_t max;
};

typedef struct dim_tuple dim_tuple_t;

const char * trim(const char *s);
dim_t get_vertex(char *s);
dim_tuple_t vertex_compare(dim_t vertex, dim_tuple_t minmax);

/* remove spaces at beginning */
const char *trim(const char *s) {
    while (isspace(*s)) ++s;
    return s;
}

/* process a file
 * input - file name
 * opens the file and scans line by line
 * any line that starts with 'vertex' it takes in the x, y, z
 * compares them with known maxima and minima
 * and updates them
 * returns difference between maximum and mimimum
 * for x, y and z respectively
 * as dimensions of STL */
dim_t process_file(char * filename) {
    FILE *f;
    char buffer[1000];
    dim_t vertex;
    dim_tuple_t minmax;

    minmax.min.x = 0;
    minmax.min.y = 0;
    minmax.min.z = 0;
    minmax.max.x = 0;
    minmax.max.y = 0;
    minmax.max.z = 0;

    /* open file and check for errors */
    f = fopen(filename, "r");
    if (f == NULL) {
        sprintf(buffer, "Error opening %s\n", filename);
        perror(buffer);
        exit(1);
    }


    /* file open, process it */
    while (fgets(buffer, 999, f) != NULL) {
        char *trimmed;

        /* get line without spaces at beginning */
        trimmed = (char *) trim(buffer);

        /* if line starts with 'vertex' */
        if (strncmp(trimmed, "vertex", 6) == 0) {
            /* get x, y and z from that line */
            vertex = get_vertex(trimmed);

            /* update minimum and maximum */
            minmax = vertex_compare(vertex, minmax);
        }
    }

    /* file processed, close file */
    fclose(f);

    /* calculate dimensions from extrema */
    vertex.x = minmax.max.x - minmax.min.x;
    vertex.y = minmax.max.y - minmax.min.y;
    vertex.z = minmax.max.z - minmax.min.z;

    return vertex;
}

/* return x, y, z from vertex line */
dim_t get_vertex(char *s) {
    dim_t retval;
    char buffer[100];

    sscanf(s, "%s %f %f %f", buffer, &retval.x, &retval.y, &retval.z);

    return retval;
}

/* update extrema from vertex points */
dim_tuple_t vertex_compare(dim_t vertex, dim_tuple_t minmax) {
    if (vertex.x < minmax.min.x) minmax.min.x = vertex.x;
    if (vertex.x > minmax.max.x) minmax.max.x = vertex.x;
    if (vertex.y < minmax.min.y) minmax.min.y = vertex.y;
    if (vertex.y > minmax.max.y) minmax.max.y = vertex.y;
    if (vertex.z < minmax.min.z) minmax.min.z = vertex.z;
    if (vertex.z > minmax.max.z) minmax.max.z = vertex.z;

    return minmax;
}

/* print usage and exit */
void usage(const char * cmd) {
    printf("usage: %s file1 [,file2, ...]\n", cmd);
    exit(0);
}

/* now the main part */
int main(int argc, char* argv[]) {
    dim_t dimensions;

    /* if no files supplied print usage and exit */
    if (argc == 1) {
        usage(argv[0]);
    }

    /* process all files supplied *
     * if file is not STL dimensions get calculated as 0,0,0 */
    for(int i=1; i<argc; i++) {
        /* first calculate dimensions */
        dimensions = process_file(argv[i]);

        /* dimensions calculated now print */
        printf("dimensions of %s:", argv[i]);
        printf(" - length = %.2f, width = %.2f, height = %.2f\n",
                dimensions.x,
                dimensions.y,
                dimensions.z);
    }

    return 0;
}

