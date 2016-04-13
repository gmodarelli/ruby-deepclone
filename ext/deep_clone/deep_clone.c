#include "deep_clone.h"

int ident = 0;

void inspect(VALUE val)
{
#if DC_DEBUG
  for(int i = 0; i <= ident - 1; ++i)
  {
    printf("\t");
  }
  
  printf("BEFORE %d ", BUILTIN_TYPE(val));
  printf("INSPECT: %s\n", RSTRING_PTR(rb_any_to_s(val)));
#endif
}

void inspect_kvp(ID key, VALUE val)
{
#if DC_DEBUG
  for(int i = 0; i <= ident - 1; ++i)
  {
    printf("\t");
  }
  
  printf("BEFORE %s %d %d", RSTRING_PTR(rb_inspect(ID2SYM(key))), val);
  printf("VALUE: %s => %s\n", RSTRING_PTR(rb_inspect(ID2SYM(key))), RSTRING_PTR(rb_any_to_s(val)));
#endif
}

void Init_deep_clone()
{
  DeepClone = rb_define_module("DeepClone");
  rb_define_module_function(DeepClone, "clone", deep_clone, 1);
}

static int clone_variable(st_data_t key, st_data_t index, struct dump_call_arg *arg)
{
  VALUE val = rb_ivar_get(arg->obj, (ID) key);
  inspect_kvp((ID) key, val);
  
  // Check if value is nil. For some reason, if you "force" an instance value
  // to nil, the ||= operator won't work.
  if(!NIL_P(val))
  {
    rb_ivar_set(arg->obj, (ID) key, clone_object(val, arg->tracker));
  }
  
  return ST_CONTINUE;
}

static int hash_each(VALUE key, VALUE value, struct dump_call_arg *arg)
{
  rb_hash_aset(arg->obj, clone_object(key, arg->tracker), clone_object(value, arg->tracker));
  
  return ST_CONTINUE;
}

static VALUE clone_object(VALUE object, VALUE tracker)
{
  if(rb_special_const_p(object))
  {
    return object;
  }

  inspect(object);

  VALUE new_obj;
  VALUE id = rb_obj_id(object);

  if(st_lookup(RHASH_TBL(tracker), id, 0))
  {
    new_obj = rb_hash_aref(tracker, id);
  }
  else
  {
    ++ident;
    
    switch(BUILTIN_TYPE(object))
    {
      case T_ARRAY:
        new_obj = rb_ary_new2(RARRAY_LEN(object));
        long len = RARRAY_LEN(object);
        if(len == 0)
        {
          break;
        }
        
        rb_hash_aset(tracker, id, new_obj);
        
        VALUE *ptr = RARRAY_PTR(object);
        while(len--)
        {
          rb_ary_push(new_obj, clone_object(*ptr, tracker));
          
          ++ptr;
        }
        
        break;
      case T_HASH:
        new_obj = rb_hash_new();
        rb_hash_aset(tracker, id, new_obj);
        
        struct dump_call_arg arg = { new_obj, tracker, object };
        rb_hash_foreach(object, hash_each, (st_data_t) &arg);
        
        break;
      case T_STRING:
      case T_DATA:
        if(rb_obj_is_kind_of(object, rb_cNumeric))
        {
          new_obj = object;
        }
        else
        {
          new_obj = rb_obj_clone(object);
        }
        
        rb_hash_aset(tracker, id, new_obj);
        
        break;
      case T_CLASS:
      case T_MODULE:
      case T_FLOAT:
      case T_REGEXP:
      case T_BIGNUM:
      case T_NIL:
      case T_TRUE:
      case T_FALSE:
      case T_FIXNUM:
      case T_STRUCT:
      case T_FILE:
        new_obj = object;
        
        rb_hash_aset(tracker, id, new_obj);
        
        break;
      default:
        if(rb_obj_is_kind_of(object, rb_cNumeric))
        {
          new_obj = object;
          rb_hash_aset(tracker, id, new_obj);
        }
        else
        {
          new_obj = rb_obj_clone(object);

          // Unfreeze the new object
          OBJ_UNFREEZE(new_obj);

          rb_hash_aset(tracker, id, new_obj);
          
          st_table *tbl = DC_ROBJECT_IV_INDEX_TBL(object);

          if(tbl)
          {
            struct dump_call_arg arg = { new_obj, tracker, object };
            TABLE_FOREACH(tbl, clone_variable, (st_data_t) &arg);
          }

          if(OBJ_FROZEN(object))
          {
            OBJ_FREEZE(new_obj);
          }
        }
        
        break;
    }
    
    --ident;
  }
  
  return new_obj;
}

VALUE deep_clone(int argc, VALUE argv)
{
  VALUE tracker = rb_hash_new();
  
  return clone_object(argv, tracker);
}
