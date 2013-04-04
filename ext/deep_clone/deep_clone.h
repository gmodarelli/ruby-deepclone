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
 struct rb_classext_struct {
    sa_table m_tbl;
    sa_table iv_tbl;
    sa_table const_tbl;
    sa_table iv_index_tbl;
};

#define TABLE_FOREACH sa_foreach
#define RCLASS_EXT(c) (RCLASS(c)->ptr)
#define RCLASS_IV_INDEX_TBL(c) (&RCLASS_EXT(c)->iv_index_tbl)

#else
// Make it work with vanilla ruby (including 2.0)
#define RCLASS_IV_INDEX_TBL(c) (RCLASS(c)->iv_index_tbl)
#define TABLE_FOREACH st_foreach

#endif

VALUE DeepClone = Qnil;

void Init_deep_clone();
static int clone_variable(st_data_t key, st_data_t index, struct dump_call_arg *arg);
static int hash_each(VALUE key, VALUE value, struct dump_call_arg *arg);
static VALUE clone_object(VALUE object, VALUE tracker);

VALUE deep_clone(int argc,VALUE argv);

#endif
