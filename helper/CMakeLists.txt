set(helper_source console_printer.h randomizer.h workspace.h nnhelper.hpp console_printer.cpp randomizer.cpp workspace.cpp)

add_library(libhelper ${helper_source})
target_link_libraries(libhelper ncurses)
