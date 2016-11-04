#include <ruby.h>
#include "mpg123.h"

VALUE mpg123 = Qnil;

void Init_mpg123() {
  mpg123 = rb_define_module("Mpg123");
  rb_define_singleton_method(mpg123, "mike_check", mike_check, 0);
}

static VALUE mike_check(VALUE self) {
  return rb_str_new2("moon river");
}
