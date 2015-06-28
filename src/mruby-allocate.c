#include <mruby.h>
#include <stdio.h>
#include <mruby/class.h>

mrb_value
mrb_instance_allocate(mrb_state *mrb, mrb_value cv)
{
  struct RClass *c = mrb_class_ptr(cv);
  struct RObject *o;
  enum mrb_vtype ttype = MRB_INSTANCE_TT(c);
  mrb_value obj;

  if (ttype == 0) ttype = MRB_TT_OBJECT;
  o = (struct RObject*)mrb_obj_alloc(mrb, ttype, c);
  obj = mrb_obj_value(o);
  return obj;
}


void
mrb_mruby_allocate_gem_init(mrb_state* mrb) {
  int ai = mrb_gc_arena_save(mrb);
  struct RClass *cls = mrb_class_get(mrb,"Class");
  mrb_define_method(mrb, cls, "allocate", mrb_instance_allocate, MRB_ARGS_ANY()); 
  mrb_gc_arena_restore(mrb,ai); 
}

void
mrb_mruby_allocate_gem_final(mrb_state* mrb) {
  // finalize
}
