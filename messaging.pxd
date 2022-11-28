# distutils: language = c++

from libcpp.string cimport string

cdef extern from "messaging.h":
    cdef cppclass Context:
        @staticmethod
        Context * create()
    cdef cppclass Message:
        void init(size_t)
        void initData(char *,size_t)
        size_t getSize()
        char* getData()
        void close()
    cdef cppclass PubSocket:
        @staticmethod
        PubSocket * create(Context*)
        int connect(int)
        int sendMessage(Message*)
        int send(char*, size_t)
    cdef cppclass SubSocket:
        @staticmethod
        SubSocket * create(Context*)
        int connect(int, string)
        Message* receive(char*)
