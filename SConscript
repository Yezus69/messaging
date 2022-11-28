Import('env', 'arch', 'envCython')
import os


schema_files = ['message/message.capnp']

env.Command([f'{s}.c++' for s in schema_files] + [f'{s}.h' for s in schema_files],
    schema_files,
    ['capnp compile -oc++ $SOURCES'])

message_objects = env.SharedObject([f'{s}.c++' for s in schema_files])

env.Library('message', message_objects)
env.SharedLibrary('message_shared', message_objects)

messaging_objects = env.SharedObject([
  'messaging.cc',
])

messaging_lib = env.Library('messaging', messaging_objects, LIBS=['zmq'])
env.CompilationDatabase()

envCython.Program('messaging_pyx.so', 'messaging_pyx.pyx', LIBS=envCython["LIBS"]+[messaging_lib, "zmq"])
