local env = environment()
env = env:begin_section_scope()
env = env:begin_section_scope()
env = env:add_global_level("l")
local l = mk_global_univ("l")
env = env:add(check(env, mk_var_decl("A", mk_sort(l))), binder_info(true))
local A = Const("A")
env = add_decl(env, mk_var_decl("R", mk_arrow(A, A, Bool)))
local R = Const("R")
local a = Local("a", A)
env = add_decl(env, mk_definition("reflexive", Bool, Pi(a, R(a, a))))
env = add_decl(env, mk_definition("id", mk_arrow(A, A), Fun(a, a)))
env = env:end_scope()
local A1 = Local("A", mk_sort(mk_param_univ("l")))
local R1 = Local("R", mk_arrow(A1, A1, Bool))
local a1 = Local("a", A1)
print(env:find("reflexive"):type())
print(env:find("reflexive"):value())
assert(env:find("reflexive"):type() == Pi({A1, R1}, Bool))
assert(env:find("reflexive"):value() == Fun({A1, R1}, Pi(a1, R1(a1, a1))))
print(env:find("id"):type())
print(env:find("id"):value())
env = env:end_scope()
print(env:find("reflexive"):type())
print(env:find("reflexive"):value())
assert(env:find("reflexive"):type() == Pi({A1, R1}, Bool))
assert(env:find("reflexive"):value() == Fun({A1, R1}, Pi(a1, R1(a1, a1))))
