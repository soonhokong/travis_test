local a   = Const("a")
local A   = Const("A")
local vec = Const("vec")
local T   = Const("T")
print(Pi({{A, Type}, {a, A}, {A, vec(A)}, {a, A}}, a))
local t = mk_pi("A", Type, mk_pi("a", Var(0), mk_pi("A", vec(Var(1)), mk_pi("a", Var(0), T(Var(0), Var(2))))))
print(t)
print(Let(A, Type, Bool, Pi(a, A, Let(A, Type, A, Pi(a, A, a)))))
print(mk_let("A", Type, Bool, mk_pi("a", Var(0), mk_let("A", Type, Var(1), mk_pi("a", Var(0), T(Var(0), Var(1), Var(2)))))))
print(mk_let("A", Type, Bool, mk_pi("a", Var(0), mk_let("A", Type, Var(1), mk_pi("a", Var(0), T(Var(0), Var(1), Var(2), Var(3)))))))
