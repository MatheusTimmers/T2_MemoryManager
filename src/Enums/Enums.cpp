#include "./Enums.hpp"

std::string to_string(Policy policy) {
    switch (policy) {
        case WORST_FIT:
            return "WORST_FIT";
        case CIRCULAR_FIT:
            return "CIRCULAR_FIT";
        default:
            return "UNKNOWN_POLICY";
    }
}
