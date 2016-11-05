#include "mpg123_handle.h"
#include <string.h>

static VALUE deallocate(void *handle) {
  mpg123_delete(handle);
  return Qnil;
}

static VALUE allocate(VALUE klass) {
  int outcome;
  mpg123_handle *handle = mpg123_new(NULL, &outcome);

  if (!handle) {
    rb_raise(
      rb_eRuntimeError,
      "Error creating mpg123 handle %s: ",
      mpg123_plain_strerror(outcome)
    );
  }

  return Data_Wrap_Struct(klass, NULL, deallocate, handle);
}

VALUE get_decoder(VALUE klass) {
  mpg123_handle *handle;
  Data_Get_Struct(klass, mpg123_handle, handle);

  const char* decoder = mpg123_current_decoder(handle); 
  return rb_str_new_cstr(decoder);
}

VALUE set_decoder(VALUE klass, VALUE value) {
  mpg123_handle *handle;
  Data_Get_Struct(klass, mpg123_handle, handle);

  const char *decoder_name = StringValuePtr(value);
  int outcome = mpg123_decoder(handle, decoder_name);

  if (outcome != MPG123_OK) {
    rb_raise(
      rb_eRuntimeError,
      "Error setting mpg123 decoder %s: ",
      mpg123_plain_strerror(outcome)
    );
  }

  return Qnil;
}

VALUE supported_decoders() {
  VALUE array = rb_ary_new();
  const char **decoders = mpg123_supported_decoders();

  for (int i = 0; 1; ++i) {
    if (decoders[i]) {
      VALUE str = rb_str_new_cstr(decoders[i]);
      rb_ary_push(array, str);
    }
    else {
      break;
    }
  }

  return array;
}

VALUE get_param(VALUE klass, VALUE type) {
  mpg123_handle *handle;
  Data_Get_Struct(klass, mpg123_handle, handle);

  long value;
  double float_value;
  enum mpg123_parms c_type = (enum mpg123_parms)FIX2LONG(type);
  int outcome = mpg123_getparam(handle, c_type, &value, &float_value);

  if (outcome != MPG123_OK) {
    rb_raise(
      rb_eRuntimeError,
      "Error getting parameter %s: ",
      mpg123_plain_strerror(outcome)
    );
  }

  if (value != 0) {
    return LONG2FIX(value);
  }
  else if (float_value != 0) {
    return DBL2NUM(float_value);
  }
  else {
    return LONG2FIX(0);
  }
}

VALUE set_param(VALUE klass, VALUE type, VALUE value) {  
  mpg123_handle *handle;
  Data_Get_Struct(klass, mpg123_handle, handle);

  enum mpg123_parms c_type = (enum mpg123_parms)FIX2LONG(type);
  long c_value = 0;
  double float_value = 0;

  if (FIXNUM_P(c_type)) {
    c_value = FIX2LONG(value);
  }
  else if (RB_FLOAT_TYPE_P(c_type)) {
    float_value = RFLOAT_VALUE(c_type);
  }

  int outcome = mpg123_getparam(handle, c_type, &c_value, &float_value);

  if (outcome != MPG123_OK) {
    rb_raise(
      rb_eRuntimeError,
      "Error setting parameter %s: ",
      mpg123_plain_strerror(outcome)
    );
  }

  return Qnil;
}

void Init_mpg123_handle() {
  VALUE klass = rb_define_class_under(Module, "Handle", rb_cObject);
  rb_define_alloc_func(klass, allocate);

  // rb_define_const(class, "CONST_NAME", value)

  rb_define_method(klass, "supported_decoders", supported_decoders, 0);
  rb_define_method(klass, "decoder", get_decoder, 0);
  rb_define_method(klass, "decoder=", set_decoder, 1);

  rb_define_method(klass, "get_param", get_param, 1);
  rb_define_method(klass, "set_param", set_param, 2);
}
