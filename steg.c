#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "steg.h"
#include "ppm.h"

struct args_t
{
    bool help;                  /* -h option */
    unsigned int verbosity;     /* -v option */
    const char *input_filename; /* -f option */
};

int main(int argc, char **argv)
{
    args_t args;
    bool args_valid = false;

    args_valid = parse_args(argc, argv, &args);

    if (!args_valid || args.help || !args.input_filename)
    {
        usage();
        return EXIT_FAILURE;
    }

    ppm_image_t *image;

    bool result = ppm_load_image(args.input_filename, image);

    if (!result)
    {
        fputs("Error loading image!", stdout);
        return EXIT_FAILURE;
    }

    result = ppm_free_image(image);

    if (!result)
    {
        fputs("Error freeing image!", stdout);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

bool parse_args(int argc, char **argv, args_t *args)
{
    int opt = 0;
    const char *opt_string = "cf:hstv?";

    args->input_filename = NULL;
    args->help = false;

    opt = getopt(argc, argv, opt_string);

    while (opt != -1)
    {
        switch (opt)
        {
        case 'f':
            args->input_filename = optarg;
            break;

        case 'v':
            args->verbosity++;
            break;

        case 'h': /* fall-through is intentional */
        case '?':
            args->help = true;
            break;

        default:
            return false;
            break;
        }

        opt = getopt(argc, argv, opt_string);
    }

    return true;
}

void usage()
{
    fputs("Usage: gpsanalyzer [options]\n", stdout);
    fputs("Options:\n", stdout);
    fputs("  -h			Print this message and exit.\n", stdout);
    fputs("  -f FILE		Read FILE as inputfile.\n", stdout);
}
