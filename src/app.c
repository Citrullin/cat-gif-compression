#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAVE_CONFIG_H
#include "webp/config.h"
#endif

#include "../examples/example_util.h"
#include "../imageio/image_dec.h"
#include "../imageio/imageio_util.h"
#include "./stopwatch.h"
#include "./unicode.h"
#include "webp/encode.h"
#include "webp/mux.h"

#if !defined(STDIN_FILENO)
#define STDIN_FILENO 0
#endif

static int ReadImage(const char filename[], WebPPicture* const pic) {
  const uint8_t* data = NULL;
  size_t data_size = 0;
  WebPImageReader reader;
  int ok;
#ifdef HAVE_WINCODEC_H
  // Try to decode the file using WIC falling back to the other readers for
  // e.g., WebP.
  ok = ReadPictureWithWIC(filename, pic, 1, NULL);
  if (ok) return 1;
#endif
  if (!ImgIoUtilReadFile(filename, &data, &data_size)) return 0;
  reader = WebPGuessImageReader(data, data_size);
  ok = reader(data, data_size, pic, 1, NULL);
  WebPFree((void*)data);
  return ok;
}

static int SetLoopCount(int loop_count, WebPData* const webp_data) {
  int ok = 1;
  WebPMuxError err;
  uint32_t features;
  WebPMuxAnimParams new_params;
  WebPMux* const mux = WebPMuxCreate(webp_data, 1);
  if (mux == NULL) return 0;

  err = WebPMuxGetFeatures(mux, &features);
  ok = (err == WEBP_MUX_OK);
  if (!ok || !(features & ANIMATION_FLAG)) goto End;

  err = WebPMuxGetAnimationParams(mux, &new_params);
  ok = (err == WEBP_MUX_OK);
  if (ok) {
    new_params.loop_count = loop_count;
    err = WebPMuxSetAnimationParams(mux, &new_params);
    ok = (err == WEBP_MUX_OK);
  }
  if (ok) {
    WebPDataClear(webp_data);
    err = WebPMuxAssemble(mux, webp_data);
    ok = (err == WEBP_MUX_OK);
  }

 End:
  WebPMuxDelete(mux);
  if (!ok) {
    fprintf(stderr, "Error during loop-count setting\n");
  }
  return ok;
}

int main(int argc, const char* argv[]) {
    puts("test");
    return 1;
}

