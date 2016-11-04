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

  return Qnil;
}

void Init_mpg123_mpegFile() {
  VALUE klass = rb_define_class_under(module, "MpegFile", rb_cObject);
  rb_define_alloc_func(klass, allocate);
  rb_define_method(klass, "initialize", initialize, 0);
  rb_define_method(klass, "initialize", initialize, 0);

  int outcome = mpg123_init();

  if (outcome != MPG123_OK) {
    rb_raise(
      rb_eRuntimeError, 
      "Error initializing mpg123: %s", 
      mpg123_plain_strerror(outcome)
    );
  }
}
