#include "Hexagon.h"

std::ostream& operator<<(std::ostream &os , const Hexagon& hex){
    os << "Hexagon(" << hex.getQ() << ", " << hex.getR() << ")";
    return os;
}
