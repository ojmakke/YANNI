set(interpreter_source commands.h parser.h parser.cpp classic_network.cpp eval_network.cpp reset_network.cpp retrain_network.cpp scale_network.cpp set_io.cpp train_network.cpp use_network.cpp validate_network.cpp)

add_library(libinterpreter ${interpreter_source})
target_link_libraries(libinterpreter libcommon libfileio)
