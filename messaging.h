#pragma once

#include <string>

class Message{
  private:
    char * data;
    size_t size;
  public:
    void init(size_t size);
    void initData(char *data, size_t size);
    size_t getSize(){return size;}
    char * getData(){return data;}
    void close();
    ~Message();
};

class Context{
  private:
    void* context;
  public:
    Context();
    static Context* create();
    void * getRawContext() {return context;}
    ~Context();
};

class PubSocket{
  private:
    void* publisher;
  public:
    PubSocket(Context* context);
    static PubSocket* create(Context* context);
    int connect(int port);
    int sendMessage(Message *message);
    int send(char *data, size_t size);
    ~PubSocket();
};

class SubSocket {
  private:
    void* subscriber;
  public:
    SubSocket(Context* context);
    static SubSocket* create(Context* context);
    int connect(int port, std::string address);
    Message* receive(char* filter);
    ~SubSocket();
};


    
