local env    = environment()
local l      = param_univ("l")
local Ul     = mk_sort(l)
local lst_l  = Const("lst", {l})
local A      = Local("A", Ul)
env = add_decl(env, mk_var_decl("lst", {l}, mk_arrow(Ul, Ul)))
env = add_decl(env, mk_var_decl("lst2lst", {l}, Pi(A, mk_arrow(lst_l(A), lst_l(A)))))
env = add_decl(env, mk_var_decl("head", {l}, Pi(A, mk_arrow(lst_l(A), A))))
env = add_decl(env, mk_var_decl("id", {l}, Pi(A, mk_arrow(A, A))))
function add_bad_coercion(env, c)
   ok, msg = pcall(function() add_coercion(env, c) end)
   assert(not ok)
   print("Expected error: " .. tostring(msg:what()))
end
function add_bad_coercion2(env, c, cls)
   ok, msg = pcall(function() add_coercion(env, c, cls) end)
   assert(not ok)
   print("Expected error: " .. tostring(msg:what()))
end
add_bad_coercion(env, "lst2lst")
add_bad_coercion(env, "head")
add_bad_coercion(env, "id")
add_bad_coercion2(env, "head", "lst")
