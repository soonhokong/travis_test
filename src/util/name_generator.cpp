/*
Copyright (c) 2013 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Leonardo de Moura
*/
#include <limits>
#include <algorithm>
#include "util/name_generator.h"

namespace lean {
name name_generator::next() {
    if (m_next_idx == std::numeric_limits<unsigned>::max()) {
        // avoid overflow
        m_prefix   = name(m_prefix, m_next_idx);
        m_next_idx = 0;
    }
    name r(m_prefix, m_next_idx);
    m_next_idx++;
    return r;
}

void swap(name_generator & a, name_generator & b) {
    swap(a.m_prefix, b.m_prefix);
    std::swap(a.m_next_idx, b.m_next_idx);
}

DECL_UDATA(name_generator)
static int mk_name_generator(lua_State * L) { return push_name_generator(L, name_generator(to_name_ext(L, 1))); }
static int name_generator_next(lua_State * L) { return push_name(L, to_name_generator(L, 1).next()); }
static int name_generator_prefix(lua_State * L) { return push_name(L, to_name_generator(L, 1).prefix()); }
static int name_generator_mk_child(lua_State * L) { return push_name_generator(L, to_name_generator(L, 1).mk_child()); }
static const struct luaL_Reg name_generator_m[] = {
    {"__gc",     name_generator_gc}, // never throws
    {"next",     safe_function<name_generator_next>},
    {"prefix",   safe_function<name_generator_prefix>},
    {"mk_child", safe_function<name_generator_mk_child>},
    {0, 0}
};
static void name_generator_migrate(lua_State * src, int i, lua_State * tgt) { push_name_generator(tgt, to_name_generator(src, i)); }

void open_name_generator(lua_State * L) {
    luaL_newmetatable(L, name_generator_mt);
    set_migrate_fn_field(L, -1, name_generator_migrate);
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    setfuncs(L, name_generator_m, 0);

    SET_GLOBAL_FUN(mk_name_generator,   "name_generator");
    SET_GLOBAL_FUN(name_generator_pred, "is_name_generator");
}
}
