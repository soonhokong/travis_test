local env = environment()
env = env:begin_section_scope()
env = env:add_global_level("l")
local l = mk_global_univ("l")
env = env:add(check(env, mk_var_decl("A", mk_sort(l))), binder_info(true))
local A = Const("A")
local l2 = mk_param_univ("l")
check_error(function()
               env = add_decl(env, mk_var_decl("R", {l2}, mk_arrow(A, A, mk_sort(l2))))
            end
)
