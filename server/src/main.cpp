#include <iostream>
#define BUFFSIZE 1024

#include "threads/iThread.hpp"
#include "sockets/iSocket.hpp"
#include "library/iLibrary.hpp"
#include "level.hpp"
#include "monster.hpp"
#include "math/vertex.hpp"
#include "game.hpp"
#include "server.hpp"
#include <stdlib.h>
#include <vector>


using namespace std;

int	main() {
    srand(43);

    try {
		Server	s;
		s.run();
    } catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
        delete e;
    }
    return 0;
}
