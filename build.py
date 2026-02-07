import subprocess
import platform
from pathlib import Path

def main():
    OS = platform.system()
    if OS == "Windows":
        subprocess.run("cls",shell=True)
    else:
        subprocess.run("clear",shell=True)

    # config
    COMPILER        =   "clang++"
    SOURCE_DIR      =   "src"
    BUILD_DIR       =   "build"
    EXECUTABLE_NAME =   "sandbox.exe"
    CPP_VERSION     =   "-std=c++23"
    INCLUDES        =   ["src/external"]

    INCLUDES        =   " ".join(["-I" + include for include in INCLUDES])

    print(f"{text_magenta}=-=-=-=-= ✦ {text_bright_yellow}Lux builder{text_magenta} ✦ =-=-=-=-=\n")
    print(f"{text_yellow}Platform: {text_bright_cyan}{platform.system()}")
    print(f"{text_yellow}Compiler: {text_bright_cyan}{COMPILER}\n")

    Path(f"{BUILD_DIR}/obj").mkdir(parents = True, exist_ok = True)
    Path(f"{BUILD_DIR}/bin").mkdir(parents = True, exist_ok = True)

    modified = False
    success = True

    for s in Path(SOURCE_DIR).rglob("*.cpp"):
        should_compile = False

        source = Path(s)
        object = Path(f"{BUILD_DIR}/obj/" + source.stem + ".o")
        object.as_posix

        if not object.exists():
            should_compile = True
            print(f"{text_bright_blue}Compiling {text_bright_yellow}-> {text_bright_cyan}{source.name}",  end = "")

        if object.exists() and object.stat().st_mtime < source.stat().st_mtime:
            should_compile = True
            print(f"{text_bright_blue}Re-Compiling {text_bright_yellow}-> {text_bright_cyan}{source.name}", end = "")

        if should_compile:
            compilation = subprocess.run(F"{COMPILER} -c {source} -o {object} {CPP_VERSION} -I{SOURCE_DIR} {INCLUDES}",shell = True, capture_output = True, text = True)
            modified = True

            if compilation.returncode != 0:
                print(f"{text_red} -> Error!{text_reset}")
                print(f"{compilation.stderr}",end="")
                success = False
                break
            else:
                print(f"{text_bright_green} -> Success!{text_reset}")

    if not modified:
        print(f"{text_bright_green}everything up-to-date!{text_reset}")

    elif success:
        print(f"\n{text_bright_blue}Linking",end="")
        objects = " ".join([str(p) for p in Path(f"{BUILD_DIR}/obj").glob("*.o")])
        linking = subprocess.run(f"{COMPILER} {objects} -o {BUILD_DIR}/bin/{EXECUTABLE_NAME} -luser32 -lgdi32 -lopengl32", shell = True, capture_output = True, text = True)

        if linking.returncode != 0:
            print(f"{text_red} -> Error!{text_reset}")
            print(linking.stderr,end="")
            success = False
        else:
            print(f"{text_bright_green} -> Success!{text_reset}")
    
    if success:
        print(f"\n{text_magenta}=-=-=-=-= ✦ {text_bright_green}Build Done{text_magenta} ✦ =-=-=-=-=\n{text_reset}")
    else:
        print(f"\n{text_magenta}=-=-=-=-= ✦ {text_bright_red}Build Failed{text_magenta} ✦ =-=-=-=-=\n{text_reset}")

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