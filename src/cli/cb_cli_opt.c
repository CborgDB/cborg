
#include "cli/cb_cli_opt.h"
#include "cli/cb_cli_version.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void usage(const char *progname) {
  printf("Usage:\n");
  printf("    %s [options]\n\n", progname);
  printf("Options:\n");
  printf("    --version     Print the version of CborgDB\n");
  printf("    --help    Display this help\n");
  printf("    -h, --host    IP address of CborgDB\n");
  printf("    -p, --port    Port of CborgDB\n");
}

void print_version() {
  printf("CborgDB CLI v" CBORG_CLI_VERSION "\n\n");
  printf("Maintained by Adil Benhlal <a.benhlal@cborgdb.com>\n");
}

void cb_cli_getopt(int argc, char const *argv[], char* host, uint16_t *port) {
  int c;
  static int version_flag;
  static int help_flag;

  while (1) {
    static struct option long_options[] = {
        {"version", no_argument, &version_flag, 1},
        {"help", no_argument, &help_flag, 1},
        {"host", no_argument, 0, 'h'},
        {"port", required_argument, 0, 'p'},
        {0, 0, 0, 0}};
    int option_index = 0;
    c = getopt_long(argc, (char *const *)argv, "h:p:", long_options,
                    &option_index);
    if (c == -1)
      break;

    switch (c) {
    case 0:
        break;
    case 'h':
      memcpy(host, optarg, strlen(optarg) + 1);
      break;
    case 'p':
      *port = strtoul(optarg, NULL, 10);
      break;
    default:
      abort();
    }
  }

  if (version_flag) {
    print_version();
    exit(0);
  }

  if (help_flag) {
    usage(argv[0]);
    exit(0);
  }
}
