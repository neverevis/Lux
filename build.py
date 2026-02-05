import subprocess
import glob

SOURCE_FOLDER   =   "Lux"
EXECUTABLE_NAME =   "sandbox.exe"
COMPILER        =   "clang++"
CPP_VERSION     =   "-std=c++23"
INCLUDES        =   "Lux/external"


SOURCES = " ".join(glob.glob(f"{SOURCE_FOLDER}/**/*.cpp",recursive=True))

subprocess.run(f"{COMPILER} {SOURCES} -o {EXECUTABLE_NAME} {CPP_VERSION} -I{SOURCE_FOLDER} -I{INCLUDES} -luser32 -lgdi32 -lopengl32", shell=True)