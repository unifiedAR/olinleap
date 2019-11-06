//
// Lazy Pirate server
// Binds REQ socket to tcp://*:5555
// Like hwserver except:
// - echoes request as-is
// - randomly runs slowly, or exits to simulate a crash.
//
#include "../classes/zhelpers.hpp"

int main() {
    std::string connect_sequence = "126"; // '~'
    zmq::context_t context(1);

    srandom((unsigned) time(NULL));

    int counter = 0;

    // --------- Log point cloud data -------- //
    while (1) {
        auto *server = new zmq::socket_t(context, ZMQ_REP);
        server->bind("tcp://*:5555");

        while (1) {
            std::string points = s_recv(*server);
            if (points == connect_sequence) {
                std::cout << "Establish a connection with the client" << std::endl;
                s_send(*server, points);
                continue;
            }

            std::cout << "Points: (time #" << counter << ")" << std::endl << points << std::endl;

            sleep(1);
            s_send(*server, "");  // send confirmation as an empty message
            counter++;
        }
    }
    return 0;
}