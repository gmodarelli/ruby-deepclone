#include "ruby.h"
#include "st.h"

struct dump_call_arg {
    VALUE obj;
    VALUE tracker;
};

VALUE DeepClone = Qnil;

void Init_deep_clone();

VALUE deep_clone(int argc,VALUE argv);
static VALUE clone_object(VALUE object, VALUE tracker);

void Init_deep_clone() {
	DeepClone = rb_define_module("DeepClone");
	rb_define_module_function(DeepClone, "clone", deep_clone, 1);
}

static int clone_variable(ID key, VALUE entry, struct dump_call_arg *arg)
{
  rb_ivar_set(arg->obj, key, clone_object(entry,arg->tracker));
  return ST_CONTINUE;
}

static int hash_each(VALUE key, VALUE value, struct dump_call_arg *arg)
{
  rb_hash_aset(arg->obj,clone_object(key,arg->tracker),clone_object(value,arg->tracker));
  return ST_CONTINUE;
}

static VALUE clone_object(VALUE object, VALUE tracker)
{
  VALUE new_obj;
  if(!rb_special_const_p(object)){
    int id = rb_obj_id(object);
    if(st_lookup(RHASH(tracker)->tbl, id, 0)){
      new_obj = rb_hash_aref(tracker,id);
    }
    else
    {
      switch (BUILTIN_TYPE(object)) {
        case T_ARRAY:
          new_obj = rb_ary_new2(RARRAY(object)->len);
          rb_hash_aset(tracker,id,new_obj);
          long len = RARRAY(object)->len;
          VALUE *ptr = RARRAY(object)->ptr;
          while (len--) {
            rb_ary_push(new_obj,clone_object(*ptr,tracker));
            ptr++;
          }
          break;
        case T_HASH:
          new_obj = rb_hash_new();
          rb_hash_aset(tracker,id,new_obj);
          struct dump_call_arg arg = {new_obj,tracker};
          rb_hash_foreach(object, hash_each, (st_data_t)&arg);
          break;
        case T_STRING:
          new_obj = rb_obj_clone(object);
          rb_hash_aset(tracker,id,new_obj);
          break;
        case T_CLASS: case T_MODULE: case T_REGEXP:
          new_obj = object;
          rb_hash_aset(tracker,id,new_obj);
          break;
        default:
          new_obj = rb_obj_clone(object);
          rb_hash_aset(tracker,id,new_obj);
          if (ROBJECT(object)->iv_tbl) {
            struct dump_call_arg arg = {new_obj,tracker};
            st_foreach(ROBJECT(object)->iv_tbl, clone_variable, (st_data_t)&arg);
          }
          break;
      }
    }
  }else{
     new_obj = object;
  }
  return new_obj;
}

VALUE deep_clone(int argc,VALUE argv)
{
  VALUE tracker = rb_hash_new();
  clone_object(argv,tracker);
}
