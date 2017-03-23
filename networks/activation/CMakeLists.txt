set(activation_source activation.h fixedinput.hpp logistic.hpp powern.hpp rectify.hpp step.hpp tanh.hpp)

add_library(libactivation ${activation_source})
