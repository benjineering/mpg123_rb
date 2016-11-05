#include "mpg123_rb.h"

VALUE Module;

static VALUE module_init(VALUE module) {
  return LONG2FIX(mpg123_init());
}

static VALUE module_exit(VALUE module) {
  mpg123_exit();
  return Qnil;
}

void Init_mpg123() {
  Module = rb_define_module("Mpg123");
  rb_define_singleton_method(Module, "init", module_init, 0);
  rb_define_singleton_method(Module, "exit", module_exit, 0);
  Init_mpg123_handle();
}
