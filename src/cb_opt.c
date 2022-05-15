
#include "cb_opt.h"
#include "version.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void usage(const char *progname) {
  printf("Usage:\n");
  printf("    %s [options]\n\n", progname);
  printf("Options:\n");
  printf("    -h, --help    Display this help\n");
  printf("    --version     Print the version of CborgDB\n");
}

void print_version() {
  printf("CborgDB v" CBORGDB_VERSION "\n\n");
  printf("Maintained by Adil Benhlal <a.benhlal@cborgdb.com>\n");
}

void cb_getopt(int argc, char const *argv[]) {
  int c;
  static int version_flag;

  while (1) {
    static struct option long_options[] = {
        {"version", no_argument, &version_flag, 1},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}};
    int option_index = 0;
    c = getopt_long(argc, (char *const *)argv, "h", long_options,
                    &option_index);
    if (c == -1)
      break;

    switch (c) {
    case 0:
        break;
    case 'h':
      usage(argv[0]);
      exit(0);
      break;
    default:
      abort();
    }
  }

  if (version_flag) {
    print_version();
    exit(0);
  }
}
