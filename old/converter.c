#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <endian.h>
#include <stdbool.h>

#define BUFF_LEN 128

typedef struct {
    FILE *in;
    FILE *out;
} args_t;


void usage(const char *prog_name) {
    fprintf(stderr, "USAGE:\n");
    fprintf(stderr, "  %s [OPTIONS]\n", prog_name);
    fprintf(stderr, "  -i: *.qua\n");
    fprintf(stderr, "  -o: *.vsrg\n");
}

int parse_args(args_t *args, int argc, char *argv[]) {
    int opt;
    bool is_in = false;
    bool is_out = false;
    memset(args, 0, sizeof(args_t));
    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch (opt) {
            case 'i':
                args->in = fopen(optarg, "r");
                is_in = true;
                break;
            case 'o':
                args->out = fopen(optarg, "w+");
                is_out = true;
                break;
            default:
                usage(argv[0]);
        }
    } return !(is_in && is_out);
}

int main(int argc, char *argv[]) {
    args_t args;
    if (parse_args(&args, argc, argv)) return EXIT_FAILURE;
    printf("wallah \n");
    ssize_t n;
    char line[BUFF_LEN] = {0};
    while (fgets(line, BUFF_LEN, args.in)) {
        printf("%s", line);
    }

    fclose(args.out);
    return 0;
}
