local env = bare_environment()
assert(is_environment(env))
assert(not env:is_global_level("U"))
local env2 = env:add_global_level("U")
assert(not env:is_global_level("U"))
assert(env2:is_global_level("U"))
assert(env:eta())
assert(env:prop_proof_irrel())
assert(env:impredicative())
