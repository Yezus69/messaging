# distutils: language = c++
import sys
from libc cimport errno
from libcpp.string cimport string

from messaging cimport Context as cppContext
from messaging cimport PubSocket as cppPubSocket
from messaging cimport SubSocket as cppSubSocket
from messaging cimport Message as cppMessage

cdef class Message:
    cdef cppMessage *message
    def __cinit__(self):
        self.message = new cppMessage()
    def term(self):
        self.message = NULL
    def init(self,size_t size):
        self.message.init(size)
    def initData(self,char* data, size_t size):
        self.message.initData(data,size)
    def getSize(self):
        return self.message.getSize()
    def getData(self):
        return self.message.getData()
    def close(self):
        self.message.close()

cdef class Context:
    cdef cppContext *context
    def __cinit__(self):
        self.context = cppContext.create()
    def term(self):
        self.context = NULL

cdef class PubSocket:
    cdef cppPubSocket *pub
    def __cinit__(self, Context context):
        self.pub = cppPubSocket.create(context.context)
    def term(self):
        self.pub = NULL
    def connect(self,int port):
        return self.pub.connect(port)
    def sendMessage(self,Message message):
        return self.pub.sendMessage(message.message)
    def send(self, bytes data, size_t size):
        return self.pub.send(<char*>data, size)

cdef class SubSocket:
    cdef cppSubSocket *sub
    def __cinit__(self, Context context):
        self.sub = cppSubSocket.create(context.context)
    def term(self):
        self.sub = NULL
    def connect(self,int port,string address):
        self.sub.connect(port, address)
    def receive(self, char* filter):
        msg = self.sub.receive(filter)
        if msg == NULL:
            # If a blocking read returns no message check errno if SIGINT was caught in the C++ code
            if errno.errno == errno.EINTR:
                print("SIGINT received, exiting")
                sys.exit(1)
            return None
        else:
            sz = msg.getSize()
            m = msg.getData()[:sz]
            del msg

            return m


    