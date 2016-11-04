#include "mpg123_rb.h"

VALUE module;

void Init_mpg123() {
  module = rb_define_module("Mpg123");
  Init_mpg123_mpegFile();
}
