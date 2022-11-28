import os
import numpy as np
import sysconfig
import platform
import subprocess

messaging_dir = Dir('.')
libpath = [
  '/opt/homebrew/lib',
]

cpppath = [
  messaging_dir,
  '/opt/homebrew/include',
  sysconfig.get_paths()['include'],
]


env = Environment(
    ENV=os.environ,
    CXXFLAGS="-std=c++1z",
    CPPPATH=cpppath,
    LIBPATH=libpath,
    CYTHONCFILESUFFIX=".cpp",
    tools=["default", "cython"]
)
env.Tool('compilation_db')



arch = subprocess.check_output(["uname", "-m"], encoding='utf8').rstrip()
if platform.system() == "Darwin":
  arch = "Darwin"

envCython = env.Clone(LIBS=[])
envCython["CPPPATH"] += [np.get_include()]
envCython["CCFLAGS"] += ["-Wno-#warnings", "-Wno-shadow", "-Wno-deprecated-declarations"]
if arch == "Darwin":
  envCython["LINKFLAGS"] = ["-bundle", "-undefined", "dynamic_lookup"]
elif arch == "aarch64":
  envCython["LINKFLAGS"] = ["-shared"]
  envCython["LIBS"] = [os.path.basename(sysconfig.get_paths()['include'])]
else:
  envCython["LINKFLAGS"] = ["-pthread", "-shared"]
envCython["CPPPATH"] += [np.get_include()]


Export('env', 'arch', 'envCython')
SConscript(['SConscript'])

