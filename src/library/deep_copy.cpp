/*
Copyright (c) 2013 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Leonardo de Moura
*/
#include "util/buffer.h"
#include "kernel/expr.h"
#include "kernel/expr_maps.h"

namespace lean {
expr copy(expr const & a) {
    switch (a.kind()) {
    case expr_kind::Var:      return mk_var(var_idx(a));
    case expr_kind::Constant: return mk_constant(const_name(a), const_levels(a));
    case expr_kind::Sort:     return mk_sort(sort_level(a));
    case expr_kind::Macro:    return mk_macro(to_macro(a)->m_definition, macro_num_args(a), macro_args(a));
    case expr_kind::App:      return mk_app(app_fn(a), app_arg(a));
    case expr_kind::Lambda:   return mk_lambda(binding_name(a), binding_domain(a), binding_body(a), binding_info(a));
    case expr_kind::Pi:       return mk_pi(binding_name(a), binding_domain(a), binding_body(a), binding_info(a));
    case expr_kind::Let:      return mk_let(let_name(a), let_type(a), let_value(a), let_body(a));
    case expr_kind::Meta:     return mk_metavar(mlocal_name(a), mlocal_type(a));
    case expr_kind::Local:    return mk_local(mlocal_name(a), local_pp_name(a), mlocal_type(a));
    }
    lean_unreachable(); // LCOV_EXCL_LINE
}

/** \brief Implements deep copy of kernel expressions. */
class deep_copy_fn {
    expr_cell_map<expr> m_cache;

    expr apply(expr const & a) {
        bool sh = false;
        if (is_shared(a)) {
            auto r = m_cache.find(a.raw());
            if (r != m_cache.end())
                return r->second;
            sh = true;
        }
        expr r;
        switch (a.kind()) {
        case expr_kind::Var:
        case expr_kind::Constant:
        case expr_kind::Sort:
        case expr_kind::Macro:   r = copy(a); break;
        case expr_kind::App:     r = mk_app(apply(app_fn(a)), apply(app_arg(a))); break;
        case expr_kind::Lambda:  r = mk_lambda(binding_name(a), apply(binding_domain(a)), apply(binding_body(a))); break;
        case expr_kind::Pi:      r = mk_pi(binding_name(a), apply(binding_domain(a)), apply(binding_body(a))); break;
        case expr_kind::Let:     r = mk_let(let_name(a), apply(let_type(a)), apply(let_value(a)), apply(let_body(a))); break;
        case expr_kind::Meta:    r = mk_metavar(mlocal_name(a), apply(mlocal_type(a))); break;
        case expr_kind::Local:   r = mk_local(mlocal_name(a), local_pp_name(a), apply(mlocal_type(a))); break;
        }
        if (sh)
            m_cache.insert(std::make_pair(a.raw(), r));
        return r;
    }
public:
    /**
        \brief Return a new expression that is equal to the given
        argument, but does not share any memory cell with it.
    */
    expr operator()(expr const & a) {
        scoped_expr_caching set(false);
        return apply(a);
    }
};
expr deep_copy(expr const & e) { return deep_copy_fn()(e); }
}
