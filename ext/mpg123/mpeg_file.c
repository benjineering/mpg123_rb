#include "mpeg_file.h"

static void deallocate(void *handle) {
  if (handle) {
    mpg123_delete(handle);
  }
}

static VALUE allocate(VALUE klass) {
  const char *decoder = NULL; // TODO: read decoder from module, or maybe move to initialize and read options
  int outcome;
  mpg123_handle *handle = mpg123_new(decoder, &outcome);

  if (!handle) {
    rb_raise(
      rb_eRuntimeError, 
      "Error creating mpg123 handle: %s", 
      mpg123_plain_strerror(outcome)
    );
  }

  return Data_Wrap_Struct(klass, NULL, deallocate, handle);
}

static VALUE initialize(VALUE self) {
  mpg123_handle *handle;
  Data_Get_Struct(self, mpg123_handle, handle);

  int outcome = mpg123_param(handle, MPG123_VERBOSE, 2, 0); // TODO: set params via initialize(options) & check outcome

  if (outcome != MPG123_OK) {
    rb_raise(
      rb_eRuntimeError, 
      "Error setting mpg123 param: %s", 
      mpg123_plain_strerror(outcome)
    );
  }

  return self;
}

static void open(VALUE self, VALUE filePath) {
  rb_need_block();
  FILE *file = fopen(filePath, "r");

  if (!file) {
    
  }

  mpg123_handle *handle;
  Data_Get_Struct(self, mpg123_handle, handle);

  int outcome = mpg123_open_feed(handle);

  if (outcome != MPG123_OK) {
    rb_raise(
      rb_eRuntimeError, 
      "Error opening mpg123 feed: %s", 
      mpg123_plain_strerror(outcome)
    );
  }

  // TODO: pass these as options
  const int inBuffSize 16384;
  const int outBuffSize 32768;
  unsigned char inBuff[inBuffSize];
  unsigned char outBuff[outBuffSize];

  size_t length;
  size_t size;
  size_t outSize = 0;

  while(1) {
    length = read(0, inBuff, inBuffSize);

    if(length <= 0) {
      break;
    }

    // get first chunk
    inBuff += length;
    outcome = mpg123_decode(handle, inBuff, length, outBuff, outBuffSize, &size);
    
    if(outcome == MPG123_NEW_FORMAT) {
      long rate;
      int channels, enc;
      mpg123_getformat(handle, &rate, &channels, &enc);
    }

    write(1, out, size);
    // TODO: yield

    outSize += size;

    // get remainder
    while(outcome != MPG123_ERR && outcome != MPG123_NEED_MORE) {
      outcome = mpg123_decode(handle, NULL, 0, outBuff, outBuffSize, &size);

      write(1, out, size);
      // TODO: yield

      outSize += size;
    }

    if (outcome == MPG123_ERR) {

    }
  }
}

void Init_mpg123_mpegFile() {
  VALUE klass = rb_define_class_under(module, "MpegFile", rb_cObject);
  rb_define_alloc_func(klass, allocate);
  rb_define_method(klass, "initialize", initialize, 0);
  rb_define_method(klass, "open", open, 1);

  int outcome = mpg123_init();

  if (outcome != MPG123_OK) {
    rb_raise(
      rb_eRuntimeError, 
      "Error initializing mpg123: %s", 
      mpg123_plain_strerror(outcome)
    );
  }
}
