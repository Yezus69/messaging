#include "messaging.h"
#include <zmq.h>
#include <cassert>

Context::Context()
{
	context = zmq_ctx_new();
}

Context* Context::create(){
  Context* c= new Context();
  return c;
} 

Context::~Context()
{
	zmq_ctx_destroy(context);
}

void Message::init(size_t sz) {
  size = sz;
  data = new char[size];
}

void Message::initData(char * d, size_t sz) {
  size = sz;
  data = new char[size];
  memcpy(data, d, size);
}

void Message::close() {
  if (size > 0){
    delete[] data;
  }
  size = 0;
}

Message::~Message() {
  this->close();
}

PubSocket::PubSocket(Context* context)
{
	publisher = zmq_socket(context->getRawContext(), ZMQ_PUB);
}

PubSocket* PubSocket::create(Context* context){
  PubSocket* p = new PubSocket(context);
  return p;
} 
int PubSocket::connect(int port)
{
	std::string full= "tcp://*:" + std::to_string(port);
	return zmq_bind(publisher,full.c_str());
}

int PubSocket::sendMessage(Message* message)
{
	return zmq_send(publisher, message->getData(), message->getSize(), ZMQ_DONTWAIT);
}

int PubSocket::send(char* data, size_t size)
{
	return zmq_send(publisher, data, size, ZMQ_DONTWAIT);;
}

PubSocket::~PubSocket()
{
	zmq_close(publisher);
}

SubSocket::SubSocket(Context* context)
{
  subscriber = zmq_socket(context->getRawContext(), ZMQ_SUB);
}

SubSocket* SubSocket::create(Context* context)
{
  SubSocket* s = new SubSocket(context);
  return s;  
}

int SubSocket::connect(int port, std::string address)
{
	std::string full = "tcp://" + address + ":" + std::to_string(port);
	return zmq_connect(subscriber, full.c_str());
}

Message* SubSocket::receive(char* filter)
{
	zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, filter, strlen(filter));
    zmq_msg_t msg;
    assert(zmq_msg_init(&msg) == 0);
    int rc = zmq_msg_recv(&msg, subscriber, 0);
	Message *r = new Message;
    if (rc >= 0) {
		r->initData((char*)zmq_msg_data(&msg), zmq_msg_size(&msg));
    }
    zmq_msg_close(&msg);
	return r;
}

SubSocket::~SubSocket()
{
	zmq_close(subscriber);
}