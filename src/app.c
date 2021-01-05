#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAVE_CONFIG_H
#include "webp/config.h"
#endif


#if defined(HAVE_UNISTD_H) && HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <gif_lib.h>
#include "webp/encode.h"
#include "webp/mux.h"
#include "../examples/example_util.h"
#include "../imageio/imageio_util.h"
#include "./gifdec.h"
#include "./unicode.h"
#include "./unicode_gif.h"

#if !defined(STDIN_FILENO)
#define STDIN_FILENO 0
#endif

int main(int argc, const char* argv[]) {

    return 1;
}

