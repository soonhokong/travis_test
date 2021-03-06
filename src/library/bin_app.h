/*
Copyright (c) 2014 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Leonardo de Moura
*/
#pragma once
#include "kernel/expr.h"

namespace lean {
/** \brief Return true iff \c t is of the form <tt>((f s1) s2)</tt> */
bool is_bin_app(expr const & t, expr const & f);
/** \brief Return true iff \c t is of the form <tt>((f s1) s2)</tt>, if the result is true, then store a1 -> lhs, a2 -> rhs */
bool is_bin_app(expr const & t, expr const & f, expr & lhs, expr & rhs);

/**
   \brief Return unit if <tt>num_args == 0</tt>, args[0] if <tt>num_args == 1</tt>, and
   <tt>(op args[0] (op args[1] (op ... )))</tt>
*/
expr mk_bin_rop(expr const & op, expr const & unit, unsigned num_args, expr const * args);
expr mk_bin_rop(expr const & op, expr const & unit, std::initializer_list<expr> const & l);

/**
   \brief Return unit if <tt>num_args == 0</tt>, args[0] if <tt>num_args == 1</tt>, and
   <tt>(op ... (op (op args[0] args[1]) args[2]) ...)</tt>
*/
expr mk_bin_lop(expr const & op, expr const & unit, unsigned num_args, expr const * args);
expr mk_bin_lop(expr const & op, expr const & unit, std::initializer_list<expr> const & l);
}
