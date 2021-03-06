/*
Copyright (c) 2013 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Leonardo de Moura
*/
#include <utility>
#include "kernel/for_each_fn.h"

namespace lean {
void for_each_fn::apply(expr const & e, unsigned offset) {
    buffer<std::pair<expr const &, unsigned>> todo;
    todo.emplace_back(e, offset);
    while (true) {
      begin_loop:
        if (todo.empty())
            break;
        auto p = todo.back();
        todo.pop_back();
        expr const & e  = p.first;
        unsigned offset = p.second;

        switch (e.kind()) {
        case expr_kind::Constant: case expr_kind::Var:
        case expr_kind::Sort:
            m_f(e, offset);
            goto begin_loop;
        default:
            break;
        }

        if (is_shared(e)) {
            expr_cell_offset p(e.raw(), offset);
            if (!m_visited)
                m_visited.reset(new expr_cell_offset_set());
            if (m_visited->find(p) != m_visited->end())
                goto begin_loop;
            m_visited->insert(p);
        }

        if (!m_f(e, offset))
            goto begin_loop;

        switch (e.kind()) {
        case expr_kind::Constant: case expr_kind::Var:
        case expr_kind::Sort:
            goto begin_loop;
        case expr_kind::Meta: case expr_kind::Local:
            todo.emplace_back(mlocal_type(e), offset);
            goto begin_loop;
        case expr_kind::Macro: {
            unsigned i = macro_num_args(e);
            while (i > 0) {
                --i;
                todo.emplace_back(macro_arg(e, i), offset);
            }
            goto begin_loop;
        }
        case expr_kind::App:
            todo.emplace_back(app_arg(e), offset);
            todo.emplace_back(app_fn(e), offset);
            goto begin_loop;
        case expr_kind::Lambda: case expr_kind::Pi:
            todo.emplace_back(binding_body(e), offset + 1);
            todo.emplace_back(binding_domain(e), offset);
            goto begin_loop;
        case expr_kind::Let:
            todo.emplace_back(let_body(e), offset + 1);
            todo.emplace_back(let_value(e), offset);
            todo.emplace_back(let_type(e), offset);
            goto begin_loop;
        }
    }
}
}
