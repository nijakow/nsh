#ifndef NSH_DEFS_H
#define NSH_DEFS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

#ifndef NSH_UTIL_STDLIB_H
# include "util/stdlib.h"
#endif

#ifndef NSH_UTIL_LIST_H
# include "util/list.h"
#endif

#ifndef NSH_UTIL_STRINGBUILDER_H
# include "util/stringbuilder.h"
#endif

#endif
