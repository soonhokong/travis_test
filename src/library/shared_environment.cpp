/*
Copyright (c) 2014 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Author: Leonardo de Moura
*/
#include "library/shared_environment.h"

namespace lean {
shared_environment::shared_environment() {}
shared_environment::shared_environment(environment const & env):m_env(env) {}

environment shared_environment::get_environment() const {
    unique_lock<mutex> l(m_mutex);
    return m_env;
}

void shared_environment::add(certified_declaration const & d) {
    unique_lock<mutex> l(m_mutex);
    m_env = m_env.add(d);
}

void shared_environment::add(declaration const & d) {
    unique_lock<mutex> l(m_mutex);
    m_env = m_env.add(d);
}

void shared_environment::replace(certified_declaration const & t) {
    unique_lock<mutex> l(m_mutex);
    m_env = m_env.replace(t);
}

void shared_environment::update(std::function<environment(environment const &)> const & f) {
    unique_lock<mutex> l(m_mutex);
    m_env = f(m_env);
}
}
