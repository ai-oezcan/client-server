#ifndef LAZYPIRATECLIENT_H
#define LAZYPIRATECLIENT_H

#define REQUEST_TIMEOUT     2500    //  msecs, (> 1000!)
#define REQUEST_RETRIES     3       //  Before we abandon

#include <zmq.hpp>
#include <string>
#include <memory>

class LazyPirateClient {
public:
    LazyPirateClient(const std::string& serverAdress);

    bool getReplyForRequest(const std::string& request, std::string& replyStr);
private:
    std::string serverAdress_;
    zmq::context_t context_;
    std::unique_ptr<zmq::socket_t> socket_;
};

#endif