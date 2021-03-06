local a = Const("a")
local f = Const("f")
local x = Var(0)
assert(not f(a):has_free_var(0))
assert(f(a, x):has_free_var(0))
assert(not f(a, x):has_free_var(1, 3))
assert(f(a, Var(1)):has_free_var(1, 3))
assert(f(a, Var(2)):has_free_var(1, 3))
assert(not f(a, Var(3)):has_free_var(1, 3))
assert(not f(a, Var(4)):has_free_var(1, 3))
assert(f(a, Var(2)):lower_free_vars(2) == f(a, Var(0)))
