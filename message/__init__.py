
import os
import capnp

MESSAGE_PATH = os.path.dirname(os.path.abspath(__file__))
capnp.remove_import_hook()

message = capnp.load(os.path.join(MESSAGE_PATH, "message.capnp"))
