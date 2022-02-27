#include "LazyPirateClient.h"
#include <iostream>
#include <chrono>

//  Helper function that returns a new configured socket
static std::unique_ptr<zmq::socket_t> createClientSocket(zmq::context_t& context, const std::string& serverAdress) {
    std::cout << "I: connecting to server..." << std::endl;
    auto socket = std::make_unique<zmq::socket_t>(context, zmq::socket_type::req);
    socket->connect("tcp://" + serverAdress);

    //  Configure socket to not wait at close time
    int linger = REQUEST_TIMEOUT;
    socket->setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
    
    return socket;
}

LazyPirateClient::LazyPirateClient(const std::string& serverAdress) :
    serverAdress_(serverAdress),
	context_(zmq::context_t(1)),
	socket_(createClientSocket(context_, serverAdress)) { }

// based on client-side reliability (Lazy Pirate Pattern) in https://zguide.zeromq.org/docs/chapter4/
bool LazyPirateClient::getReplyForRequest(const std::string& request, std::string& replyStr) {

    int retriesLeft = REQUEST_RETRIES;
    bool successfulReply = false;

    while (retriesLeft) {

        zmq::message_t requestMsg(request.size());
        memcpy(requestMsg.data(), request.data(), request.size());

        //  Send request to the server
        std::cout << "Sending request" << std::endl;
        socket_->send(requestMsg, zmq::send_flags::none);

        bool expectReply = true;
        while (expectReply) {
            //  Poll socket for a reply, with timeout
            zmq::pollitem_t items[] = {
                { *socket_, 0, ZMQ_POLLIN, 0 } };
            zmq::poll(&items[0], 1, REQUEST_TIMEOUT);

            //  If we got a reply, process it
            if (items[0].revents & ZMQ_POLLIN) {
                //  We got a reply from the server
                zmq::message_t reply;
                socket_->recv(reply, zmq::recv_flags::none);
                retriesLeft = 0;
                expectReply = false;
                successfulReply = true;
                replyStr = reply.to_string();
                std::cout << "I: server replied OK (" << replyStr << ")" << std::endl;
            }
            else if (--retriesLeft == 0) {
                replyStr = "Error: server seems to be offline, abandoning";
                std::cout << replyStr << std::endl;
                expectReply = false;
                break;
            }
            else {
                std::cout << "W: no response from server, retrying..." << std::endl;
                //  Old socket will be confused; close it and open a new one
                socket_ = createClientSocket(context_, serverAdress_);
                //  Send request again, on new socket
                socket_->send(requestMsg, zmq::send_flags::none);
            }
        }
    }
    return successfulReply;
}
