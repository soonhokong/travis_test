/*
Copyright (c) 2014 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Leonardo de Moura
*/
#pragma once
#include <utility>
#include "util/rb_map.h"
#include "util/optional.h"
#include "kernel/expr.h"
#include "kernel/justification.h"

namespace lean {
class substitution {
    typedef rb_map<name, std::pair<expr, justification>, name_quick_cmp> expr_map;
    typedef rb_map<name, std::pair<level, justification>, name_quick_cmp> level_map;
    expr_map  m_expr_subst;
    level_map m_level_subst;

    substitution(expr_map const & em, level_map const & lm);
    void d_assign(name const & m, expr const & t, justification const & j);
    void d_assign(name const & m, expr const & t);
    void d_assign(name const & m, level const & t, justification const & j);
    void d_assign(name const & m, level const & t);
    std::pair<expr, justification> d_instantiate_metavars(expr const & e);
    expr d_instantiate_metavars_wo_jst(expr const & e);
    std::pair<level, justification> d_instantiate_metavars(level const & l, bool use_jst, bool updt);
    friend class instantiate_metavars_fn;
public:
    substitution();
    typedef optional<std::pair<expr,  justification>> opt_expr_jst;
    typedef optional<std::pair<level, justification>> opt_level_jst;

    bool is_expr_assigned(name const & m) const;
    opt_expr_jst get_expr_assignment(name const & m) const;

    bool is_level_assigned(name const & m) const;
    opt_level_jst get_level_assignment(name const & m) const;

    optional<expr> get_expr(name const & m) const;
    optional<level> get_level(name const & m) const;

    substitution assign(name const & m, expr const & t, justification const & j) const;
    substitution assign(name const & m, expr const & t) const;

    substitution assign(name const & m, level const & t, justification const & j) const;
    substitution assign(name const & m, level const & t) const;

    template<typename F>
    void for_each_expr(F && fn) const {
        for_each(m_expr_subst, [=](name const & n, std::pair<expr, justification> const & a) { fn(n, a.first, a.second); });
    }

    template<typename F>
    void for_each_level(F && fn) const {
        for_each(m_level_subst, [=](name const & n, std::pair<level, justification> const & a) { fn(n, a.first, a.second); });
    }

    bool is_assigned(expr const & m) const { lean_assert(is_metavar(m)); return is_expr_assigned(mlocal_name(m)); }
    opt_expr_jst get_assignment(expr const & m) const { lean_assert(is_metavar(m)); return get_expr_assignment(mlocal_name(m)); }
    optional<expr> get_expr(expr const & m) const { lean_assert(is_metavar(m)); return get_expr(mlocal_name(m)); }
    substitution assign(expr const & m, expr const & t, justification const & j) { lean_assert(is_metavar(m)); return assign(mlocal_name(m), t, j); }
    substitution assign(expr const & m, expr const & t) const { lean_assert(is_metavar(m)); return assign(mlocal_name(m), t); }

    bool is_assigned(level const & m) const { lean_assert(is_meta(m)); return is_level_assigned(meta_id(m)); }
    opt_level_jst get_assignment(level const & m) const { lean_assert(is_meta(m)); return get_level_assignment(meta_id(m)); }
    optional<level> get_level(level const & m) const { lean_assert(is_meta(m)); return get_level(meta_id(m)); }
    substitution assign(level const & m, level const & l, justification const & j) const { lean_assert(is_meta(m)); return assign(meta_id(m), l, j); }
    substitution assign(level const & m, level const & l) { lean_assert(is_meta(m)); return assign(meta_id(m), l); }

    /** \brief Instantiate metavariables in \c e assigned in this substitution. */
    std::pair<expr, justification> instantiate_metavars(expr const & e) const;

    /**
       \brief Similar to the previous function, but it compress the substitution.
       By compress, we mean, for any metavariable \c m reachable from \c e,
       if s[m] = t, and t has asssigned metavariables, then s[m] <- instantiate_metavars(t, s).
       The updated substitution is returned.
    */
    std::tuple<expr, justification, substitution> updt_instantiate_metavars(expr const & e) const;

    /** \brief Instantiate level metavariables in \c l. */
    std::pair<level, justification> instantiate_metavars(level const & l) const;

    /**
       \brief Instantiate metavariables in \c e assigned in the substitution \c s,
       but does not return a justification object for the new expression.
    */
    expr instantiate_metavars_wo_jst(expr const & e) const;

    std::pair<expr, substitution> updt_instantiate_metavars_wo_jst(expr const & e) const;

    /** \brief Instantiate level metavariables in \c l, but does not return justification object. */
    level instantiate_metavars_wo_jst(level const & l) const;

    /** \brief Return true iff the metavariable \c m occurrs (directly or indirectly) in \c e. */
    bool occurs_expr(name const & m, expr const & e) const;
    bool occurs(expr const & m, expr const & e) const { lean_assert(is_metavar(m)); return occurs_expr(mlocal_name(m), e); }
};
}
