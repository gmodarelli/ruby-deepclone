#ifndef DEEP_CLONE_H
#define DEEP_CLONE_H

#include "ruby.h"
#include "ruby/st.h"

struct dump_call_arg {
  VALUE obj;
  VALUE tracker;
  VALUE src;
};

#ifdef SA_EMPTY
// Gotta do this because of 1.9.3's falcon patch
#define TABLE_FOREACH sa_foreach
#else
// Make it work with vanilla ruby (including 2.0)
#define TABLE_FOREACH st_foreach
#endif

VALUE DeepClone = Qnil;

void Init_deep_clone();

VALUE deep_clone(int argc,VALUE argv);
static VALUE clone_object(VALUE object, VALUE tracker);

#endif
