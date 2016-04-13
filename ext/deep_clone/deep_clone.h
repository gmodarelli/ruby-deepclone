#ifndef DEEP_CLONE_H
# define DEEP_CLONE_H

# include <ruby.h>
# include <ruby/st.h>
# include <ruby/version.h>

struct dump_call_arg
{
  VALUE obj;
  VALUE tracker;
  VALUE src;
};

# define DC_DEBUG 0

# define OBJ_UNFREEZE(x) FL_UNSET((x), FL_FREEZE)

# ifdef SA_EMPTY
// Gotta do this because of 1.9.3's falcon patch
struct rb_classext_struct
{
  sa_table m_tbl;
  sa_table iv_tbl;
  sa_table const_tbl;
  sa_table iv_index_tbl;
};

#   define TABLE_FOREACH sa_foreach

#   define DC_RCLASS_EXT(c)          (RCLASS(c)->ptr)
#   define DC_RCLASS_IV_INDEX_TBL(c) (&DC_RCLASS_EXT(c)->iv_index_tbl)
# else
// Make it work with vanilla ruby (including 2.0)
#   define TABLE_FOREACH st_foreach

#   if RUBY_API_VERSION_CODE >= 20100
#     if RUBY_API_VERSION_CODE >= 20300
// In Ruby 2.3, struct RClass was moved into internal.h and cannot be accessed
// directly.

// From ruby/ruby.h v2.2.4.
typedef struct rb_classext_struct rb_classext_t;

// RClass is defined as RClassDeprecated, which in turn only contains the 'basic' field.
#       undef RClass

// RClass as defined in Ruby 2.2.4.
struct RClass
{
  struct RBasic basic;
  VALUE super;
  rb_classext_t *ptr;
  struct method_table_wrapper *m_tbl_wrapper;
};
#     endif

// In Ruby 2.1, iv_index_tbl was moved into internal.h and cannot be accessed
// directly. We work around this by defining our own RCLASS helpers (since the
// rb_classext_struct returned by RCLASS_EXT is also effectively private).
typedef struct dc_iv_tbl_classext_struct
{
  struct st_table *iv_index_tbl;
} dc_iv_tbl_classext_t;

#     define DC_RCLASS_EXT(c)          ((dc_iv_tbl_classext_t*) RCLASS(c)->ptr)
#     define DC_RCLASS_IV_INDEX_TBL(c) (DC_RCLASS_EXT(c)->iv_index_tbl)
#   else
#     define DC_RCLASS_IV_INDEX_TBL(c) (RCLASS(c)->iv_index_tbl)
#   endif
# endif

# define DC_ROBJECT_IV_INDEX_TBL(o) ((RBASIC(o)->flags & ROBJECT_EMBED) ?\
                                    DC_RCLASS_IV_INDEX_TBL(rb_obj_class(o)) :\
                                    ROBJECT(o)->as.heap.iv_index_tbl)

VALUE DeepClone = Qnil;

void Init_deep_clone();
static int clone_variable(st_data_t key, st_data_t index, struct dump_call_arg *arg);
static int hash_each(VALUE key, VALUE value, struct dump_call_arg *arg);
static VALUE clone_object(VALUE object, VALUE tracker);
VALUE deep_clone(int argc,VALUE argv);
#endif
