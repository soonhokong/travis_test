/*
Copyright (c) 2013 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Leonardo de Moura
*/
#include "util/script_state.h"
#include "util/numerics/register_module.h"
#include "util/sexpr/register_module.h"
#include "library/kernel_bindings.h"
#include "library/arith/register_module.h"
#include "library/tactic/register_module.h"
#include "frontends/lean/register_module.h"
#include "frontends/lua/lean.lua"

namespace lean {
void register_modules() {
    register_numerics_module();
    register_sexpr_module();
    register_kernel_module();
    register_arith_module();
    register_tactic_module();
    register_frontend_lean_module();
    script_state::register_code(g_extra_code);
}
}