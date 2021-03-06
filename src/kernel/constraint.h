/*
Copyright (c) 2014 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Leonardo de Moura
*/
#pragma once
#include <algorithm>
#include "kernel/expr.h"
#include "kernel/justification.h"
namespace lean {
/**
   \brief The lean kernel type checker produces two kinds of constraints:

   - Equality constraint:          t ≈ s
        The terms t and s must be definitionally equal.
   - Universe level constaint:     l = m
        The universe level l must be less than or equal to m.

   \remark The constraints are only generated if the input term contains
   metavariables or level metavariables.

   Each constraint is associated with a justification object.
*/
enum class constraint_kind { Eq, Level };
struct constraint_cell;
class constraint {
    constraint_cell * m_ptr;
    constraint(constraint_cell * ptr);
public:
    constraint(constraint const & c);
    constraint(constraint && s);
    ~constraint();

    constraint_kind kind() const;
    unsigned hash() const;
    justification const & get_justification() const;

    constraint & operator=(constraint const & c);
    constraint & operator=(constraint && c);

    friend bool is_eqp(constraint const & c1, constraint const & c2) { return c1.m_ptr == c2.m_ptr; }
    friend void swap(constraint & l1, constraint & l2) { std::swap(l1, l2); }

    friend constraint mk_eq_cnstr(expr const & lhs, expr const & rhs, justification const & j);
    friend constraint mk_level_cnstr(level const & lhs, level const & rhs, justification const & j);

    constraint_cell * raw() const { return m_ptr; }
};

bool operator==(constraint const & c1, constraint const & c2);
inline bool operator!=(constraint const & c1, constraint const & c2) { return !(c1 == c2); }

constraint mk_eq_cnstr(expr const & lhs, expr const & rhs, justification const & j);
constraint mk_level_cnstr(level const & lhs, level const & rhs, justification const & j);

inline bool is_eq_cnstr(constraint const & c) { return c.kind() == constraint_kind::Eq; }
inline bool is_level_cnstr(constraint const & c) { return c.kind() == constraint_kind::Level; }

/** \brief Return the lhs of an equality constraint. */
expr const & cnstr_lhs_expr(constraint const & c);
/** \brief Return the rhs of an equality constraint. */
expr const & cnstr_rhs_expr(constraint const & c);
/** \brief Return the lhs of an level constraint. */
level const & cnstr_lhs_level(constraint const & c);
/** \brief Return the rhs of an level constraint. */
level const & cnstr_rhs_level(constraint const & c);

/** \brief Update equality constraint c with new_lhs, new_rhs and justification. */
constraint updt_eq_cnstr(constraint const & c, expr const & new_lhs, expr const & new_rhs, justification const & new_jst);
/** \brief Update equality constraint c with new_lhs and new_rhs, but keeping the same justification. */
constraint updt_eq_cnstr(constraint const & c, expr const & new_lhs, expr const & new_rhs);
/** \brief Update level constraint c with new_lhs, new_rhs and justification. */
constraint updt_level_cnstr(constraint const & c, level const & new_lhs, level const & new_rhs, justification const & new_jst);
/** \brief Update level constraint c with new_lhs and new_rhs, but keeping the same justification. */
constraint updt_level_cnstr(constraint const & c, level const & new_lhs, level const & new_rhs);

/** \brief Printer for debugging purposes */
std::ostream & operator<<(std::ostream & out, constraint const & c);

typedef list<constraint> constraints;
inline constraints add(constraints const & cs, constraint const & c) { return cons(c, cs); }
}
