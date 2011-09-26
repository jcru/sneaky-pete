#include "nova/rpc/receiver.h"
#include "nova/rpc/amqp.h"
#include <sstream>


namespace nova { namespace rpc {


Receiver::Receiver(const char * host, int port,
                   const char * user_name, const char * password,
                   const char * queue_name)
:   connection(),
    last_delivery_tag(-1),
    log(),
    queue(),
    queue_name(queue_name)
{
    connection = AmqpConnection::create(host, port, user_name, password);
    queue = connection->new_channel();
}

Receiver::~Receiver() {
}

void Receiver::finish_message(json_object * arguments, json_object * output) {
    queue->ack_message(last_delivery_tag);
    json_object_put(arguments);
    json_object_put(output);
}

json_object * Receiver::next_message() {
    AmqpQueueMessagePtr msg;
    while(!msg) {
        msg = queue->get_message(queue_name.c_str());
        log.info("Received an empty message.");
    }
    std::stringstream log_msg;
    log_msg << "Received message "
        << ", key " << msg->routing_key
        << ", tag " << msg->delivery_tag
        << ", ex " << msg->exchange
        << ", content_type " << msg->content_type
        << ", message " << msg->message;
    log.info(log_msg.str());
    json_object *new_obj = json_tokener_parse(msg->message.c_str());

    last_delivery_tag = msg->delivery_tag;
    return new_obj;
}

} }  // end namespace