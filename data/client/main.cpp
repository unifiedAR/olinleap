//
//  Lazy Pirate client
//  Use zmq_poll to do a safe request-reply
//  To run, start piserver and then randomly kill/restart it
//
#include "../classes/zhelpers.hpp"
#include "../classes/pointCloudPack.h"

#include <sstream>

#define REQUEST_TIMEOUT     2500    //  msecs, (> 1000!)
#define REQUEST_RETRIES     3       //  Before we abandon

static zmq::socket_t *s_client_socket(zmq::context_t &context) {
    /* Helper function that returns a new configured socket connected to the Hello World server */
    std::cout << "I: connecting to server..." << std::endl;
    zmq::socket_t *client = new zmq::socket_t(context, ZMQ_REQ);
    client->connect("tcp://localhost:5555");

    //  Configure socket to not wait at close time
    int linger = 0;
    client->setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
    return client;
}

int main() {
    zmq::context_t context(1);

    int connect_sequence = '~';
    int retries_left = REQUEST_RETRIES;

    int counter = 0;

    // make some data
    pointCloudPack pcp;
    for (int i = 0; i < 1000; i++) {
        float x = (float) 3.0 * (float) i;
        float y = x + 1;
        float z = y + 1;

        float xyz[3] = {x, y, z};
        pcp.addXYZPoint(xyz);
    }
    std::string message_str = pcp.returnMessageStr();

    while (retries_left) {
        zmq::socket_t *client = s_client_socket(context);

        bool lastSent = false;

        std::stringstream request;
        request << connect_sequence;
        s_send(*client, request.str());

        // block program until connected to server
        bool expect_reply = true;
        while (expect_reply) {

            //  Poll socket for a reply, with timeout
            zmq::pollitem_t items[] = {
                    {static_cast<void *>(*client), 0, ZMQ_POLLIN, 0}};
            zmq::poll(&items[0], 1, REQUEST_TIMEOUT);

            //  If we got a reply, process it
            if (items[0].revents & ZMQ_POLLIN) {
                //  We got a reply from the server, must match connect_sequence
                std::string reply = s_recv(*client);
                if (atoi(reply.c_str()) == connect_sequence) {
                    std::cout << "I: server replied OK (" << reply << ")" << std::endl;
                    retries_left = REQUEST_RETRIES;
                    expect_reply = false;
                } else {
                    std::cout << "E: malformed reply from server: " << reply << std::endl;
                }
            } else {
                std::cout << "W: no response from server, retrying..." << std::endl;
                //  Old socket will be confused; close it and open a new one
                delete client;
                client = s_client_socket(context);
                //  Send request again, on new socket
                s_send(*client, request.str());
            }
        }

        int point_request_sequence = 1;
        bool working = true;
        while (1) {
            if (lastSent) {
                // wait for confirmation from server (emtpy message)
                zmq::pollitem_t items[] = {
                        {static_cast<void *>(*client), 0, ZMQ_POLLIN, 0}};
                zmq::poll(&items[0], 1, REQUEST_TIMEOUT);
                if (items[0].revents & ZMQ_POLLIN) {
                    std::cout << "Previous data was successfully sent" << std::endl;
                    s_recv(*client);  // receive empty confirmation message so a new message can be sent
                } else {
                    std::cout << "Previous data was not successfully sent" << std::endl;
                    //  Old socket will be confused; close it and open a new one
                    delete client;
                    break;
                }
            }
            // send data
            std::cout << "Sending data; time #" << counter << std::endl;

            s_send(*client, message_str);
            counter++;
            lastSent = true;
        }
    }
    std::cout << "Quitting program" << std::endl;
    return 0;
}

