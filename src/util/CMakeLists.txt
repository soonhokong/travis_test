set(SOURCES trace.cpp debug.cpp name.cpp name_set.cpp
  name_generator.cpp exception.cpp interrupt.cpp hash.cpp escaped.cpp
  bit_tricks.cpp safe_arith.cpp ascii.cpp memory.cpp realpath.cpp
  script_state.cpp script_exception.cpp rb_map.cpp lua.cpp luaref.cpp
  lua_named_param.cpp stackinfo.cpp lean_path.cpp serializer.cpp
  lbool.cpp thread_script_state.cpp)

if ("${MULTI_THREAD}" MATCHES "ON")
  # Add "shared_mutex.cpp" only if MULTI_THREAD option is on.
  # Otherwise, clang++ complains that it has no symbols.
  #   /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib:
  #   file: util/libutil.a(shared_mutex.cpp.o) has no symbols
  LIST(APPEND SOURCES "shared_mutex.cpp")
  if ("${BOOST}" MATCHES "ON")
    LIST(APPEND SOURCES "thread.cpp")
  endif()
endif()

add_library(util ${SOURCES})