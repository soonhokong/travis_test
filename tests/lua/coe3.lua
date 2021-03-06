local env     = environment()
local l       = param_univ("l")
env = add_decl(env, mk_var_decl("group", {l}, mk_sort(l+1)))
env = add_decl(env, mk_var_decl("abelian_group", {l}, mk_sort(l+1)))
local group    = Const("group", {l})
local ab_group = Const("abelian_group", {l})
env = add_decl(env, mk_var_decl("carrier", {l}, mk_arrow(group, mk_sort(l))))
env = add_coercion(env, "carrier")
env = add_decl(env, mk_var_decl("abg2g", {l}, mk_arrow(ab_group, group)))
env = add_coercion(env, "abg2g")
for_each_coercion_sort(env, function(C, f) print(tostring(C) .. " >-> sort : " .. tostring(f)) end)
print(get_coercion_to_sort(env, Const("abelian_group", {1})))
assert(env:type_check(get_coercion_to_sort(env, Const("abelian_group", {1}))))
