#include <ruby.h>
#include <mpg123.h>

/*
 * declaration
 */

// module
VALUE mpg123 = Qnil;

// module initialiser
void Init_mpg123();

// sanity check for testing purposes
static VALUE mike_check(VALUE module);


/*
 * implementation
 */

void Init_mpg123() {
  mpg123 = rb_define_module("Mpg123");
  rb_define_singleton_method(mpg123, "mike_check", mike_check, 0);
}

static VALUE mike_check(VALUE self) {
  return rb_str_new2("moon river");
}
