import subprocess
import platform
import shutil
import json
from pathlib import Path

# config
build_config = Path("build_config.json")
if not build_config.exists():
    print(f"Required a build_config.json")
    exit()
with open("build_config.json", "r") as f:
    config = json.load(f)


PLATFORM        =   platform.system()
COMPILER        =   config["compiler"].lower()

if COMPILER == "clang":
    COMPILER = "clang++"
elif COMPILER == "gcc":
    COMPILER = "g++"

SOURCE_DIR      =   config["source directory"]
BUILD_DIR       =   config["build directory"]

DEBUG_MODE = config["compilation mode"]
if DEBUG_MODE == "debug":
    DEBUG_MODE = True
else:
    DEBUG_MODE = False
    
EXECUTABLE_NAME =   config["executable name"]

if PLATFORM == "Windows":
    EXECUTABLE_NAME += ".exe"

CPP_VERSION     =   f"-std=c++{config['c++ version']}"
INCLUDES        =   " ".join(["-I" + include for include in config["includes"]])

COMPILE_FLAGS = ""
LINK_FLAGS = ""
PLATFORM_FLAGS = ""

if PLATFORM == "Windows":
    PLATFORM_FLAGS = "-luser32 -lopengl32 -lgdi32"
elif PLATFORM == "Linux":
    PLATFORM_FLAGS = "-lEGL -lGL -lX11"

if DEBUG_MODE:
        COMPILE_FLAGS = "-g -O0 -DLUX_DEBUG" #-g keeps symbols in binary and -O0 does not optimize (also to keep symbols)
        LINK_FLAGS = "-g"
else:
    COMPILE_FLAGS = "-O3"
    LINK_FLAGS = "-O3 -s"


def main():
    #script

    OS = platform.system()
    if OS == "Windows":
        subprocess.run("cls",shell=True)
    else:
        subprocess.run("clear",shell=True)

    print(f"{text_magenta}=-=-=-=-= ✦ {text_bright_yellow}Lux builder{text_magenta} ✦ =-=-=-=-=\n")
    print(f"{text_yellow}Platform: {text_bright_cyan}{platform.system()}")
    print(f"{text_yellow}Compiler: {text_bright_cyan}{COMPILER}\n")

    Path(f"{BUILD_DIR}/obj").mkdir(parents = True, exist_ok = True)
    Path(f"{BUILD_DIR}/bin").mkdir(parents = True, exist_ok = True)

    compilation_queue = []

    for h in Path(SOURCE_DIR).rglob("*.h"):
        for o in Path(f"{BUILD_DIR}/obj").rglob("*.o"):
            if h.stat().st_mtime > o.stat().st_mtime or build_config.stat().st_mtime > o.stat().st_mtime:
                clear_folder(Path(f"{BUILD_DIR}/obj"))
                break

    for h in Path(SOURCE_DIR).rglob("*.hpp"):
        for o in Path(f"{BUILD_DIR}/obj").rglob("*.o"):
            if h.stat().st_mtime > o.stat().st_mtime or build_config.stat().st_mtime > o.stat().st_mtime:
                clear_folder(Path(f"{BUILD_DIR}/obj"))
                break

    i = 0
    for s in Path(SOURCE_DIR).rglob("*.cpp"):
        source = Path(s)
        object = Path(f"{BUILD_DIR}/obj/" + source.stem + ".o")

        compilation_queue.append({
            "path": source.as_posix(),
            "source_name": source.name,
            "object_name": object.name,
            "command": get_compile_command(source, object),
            "status": "updated"
        })

        if not object.exists():
            compilation_queue[i]["status"] = "new"

        if object.exists() and object.stat().st_mtime < source.stat().st_mtime:
            compilation_queue[i]["status"] = "outdated"

        i += 1
    
    save_compile_commands(compilation_queue)

    success = True
    modified = False

    for o in Path(f"{BUILD_DIR}/obj/").rglob("*.o"):
        object = Path(o)
        should_delete = True
        for item in compilation_queue:
            if item["object_name"] == object.name:
                should_delete = False
        if should_delete:
            print(f"{text_bright_red}Removing {text_yellow}-> {text_cyan}{object.name}")
            object.unlink()
            modified = True

    print()

    for item in compilation_queue:
        if item["status"] == "new" or item["status"] == "outdated":
            modified = True
            if item["status"] == "new":
                print(f"{text_bright_blue}Compiling {text_bright_yellow}-> {text_bright_cyan}{item['source_name']}",end="")
            else:
                print(f"{text_bright_blue}Re-Compiling {text_bright_yellow}-> {text_bright_cyan}{item['source_name']}",end="");
    
            compilation = subprocess.run(item["command"],shell=True,capture_output=True,text=True)

            if compilation.returncode != 0:
                print(f"{text_red} -> Error!")
                print(compilation.stderr,end="")
                success = False
                break
            else:
                print(f"{text_bright_green} -> Success!{text_reset}")

    if success and modified:
        print(f"\n{text_bright_blue}Linking",end="")
        objects = " ".join([str(p) for p in Path(f"{BUILD_DIR}/obj").glob("*.o")])
        linking = subprocess.run(f"{COMPILER} {LINK_FLAGS} {objects} -o {BUILD_DIR}/bin/{EXECUTABLE_NAME} {PLATFORM_FLAGS} > build_output.txt", shell = True, capture_output = True, text = True)

        if linking.returncode != 0:
            print(f"{text_red} -> Error!{text_reset}")
            print(linking.stderr,end="")
            success = False
        else:
            print(f"{text_bright_green} -> Success!{text_reset}")

    if not modified:
        print(f"{text_bright_green}everything up-to-date!{text_reset}")
    
    if success:
        print(f"\n{text_magenta}=-=-=-=-= ✦ {text_bright_green}Build Done{text_magenta} ✦ =-=-=-=-=\n{text_reset}")
    else:
        print(f"\n{text_magenta}=-=-=-=-= ✦ {text_bright_red}Build Failed{text_magenta} ✦ =-=-=-=-=\n{text_reset}")

def clear_folder(folder_path):
    if folder_path.exists():
        shutil.rmtree(folder_path)
        folder_path.mkdir(parents=True, exist_ok=True)

def get_compile_command(source, object):
    return F"{COMPILER} -c {COMPILE_FLAGS} {source.as_posix()} -MMD -o {object.as_posix()} {CPP_VERSION} -I{SOURCE_DIR} {INCLUDES}"

def save_compile_commands(queue):
    json_data = []
    root_dir = Path.cwd().as_posix()

    for item in queue:
        json_data.append({
            "directory": root_dir,
            "file": item["path"],
            "command": item["command"]
        })

    with open("compile_commands.json","w",encoding="utf-8") as f:
        json.dump(json_data, f, indent=4)
        print(f"{text_green}IntelliSense {text_bright_green}updated!")

#log colors
text_reset      = "\033[0m"
text_black      = "\033[30m"
text_red        = "\033[31m"
text_green      = "\033[32m"
text_yellow     = "\033[33m"
text_blue       = "\033[34m"
text_magenta    = "\033[35m"
text_cyan       = "\033[36m"
text_white      = "\033[37m"

text_bright_gray        = "\033[90m"
text_bright_red         = "\033[91m"
text_bright_green       = "\033[92m"
text_bright_yellow      = "\033[93m"
text_bright_blue        = "\033[94m"
text_bright_magenta     = "\033[95m"
text_bright_cyan        = "\033[96m"
text_bright_white       = "\033[97m"

main()