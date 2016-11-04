#include "mpeg_file.h"

static VALUE initialize(VALUE self) {
  return Qnil;
}

void Init_mpg123_mpegFile() {
  VALUE klass = rb_define_class_under(module, "MpegFile", rb_cObject);
  rb_define_method(klass, "initialize", initialize, 0);
}
