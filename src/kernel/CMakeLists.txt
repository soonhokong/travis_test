add_library(kernel level.cpp expr.cpp expr_eq_fn.cpp for_each_fn.cpp
replace_fn.cpp free_vars.cpp abstract.cpp instantiate.cpp
formatter.cpp declaration.cpp replace_visitor.cpp environment.cpp
justification.cpp pos_info_provider.cpp metavar.cpp converter.cpp
constraint.cpp type_checker.cpp error_msgs.cpp kernel_exception.cpp )

target_link_libraries(kernel ${LEAN_LIBS})
