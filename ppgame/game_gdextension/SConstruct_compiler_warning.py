import os
import subprocess
import re
import sys
from enum import Enum
from typing import Final

# =================================================================================
# copy from godot

IS_CI: Final[bool] = bool(os.environ.get("CI"))
NO_COLOR: Final[bool] = bool(os.environ.get("NO_COLOR"))
CLICOLOR_FORCE: Final[bool] = bool(os.environ.get("CLICOLOR_FORCE"))
STDERR_TTY: Final[bool] = bool(sys.stderr.isatty())

_STDERR_ORIGINAL: Final[bool] = False if NO_COLOR else CLICOLOR_FORCE or IS_CI or STDERR_TTY
_stderr_override: bool = _STDERR_ORIGINAL

class Ansi(Enum):
    """
    Enum class for adding ANSI codepoints directly into strings. Automatically converts values to
    strings representing their internal value.
    """

    RESET = "\x1b[0m"

    BOLD = "\x1b[1m"
    DIM = "\x1b[2m"
    ITALIC = "\x1b[3m"
    UNDERLINE = "\x1b[4m"
    STRIKETHROUGH = "\x1b[9m"
    REGULAR = "\x1b[22;23;24;29m"

    BLACK = "\x1b[30m"
    RED = "\x1b[31m"
    GREEN = "\x1b[32m"
    YELLOW = "\x1b[33m"
    BLUE = "\x1b[34m"
    MAGENTA = "\x1b[35m"
    CYAN = "\x1b[36m"
    WHITE = "\x1b[37m"
    GRAY = "\x1b[90m"

    def __str__(self) -> str:
        return self.value

RE_ANSI = re.compile(r"\x1b\[[=\?]?[;\d]+[a-zA-Z]")


def is_stderr_color() -> bool:
    return _stderr_override

def color_printerr(*values: object, sep: str | None = " ", end: str | None = "\n", flush: bool = False) -> None:
    """Prints a colored message to `stderr`. If disabled, ANSI codes are automatically stripped."""
    if is_stderr_color():
        print(*values, sep=sep, end=f"{Ansi.RESET}{end}", flush=flush, file=sys.stderr)
    else:
        print(RE_ANSI.sub("", (sep or " ").join(map(str, values))), sep="", end=end, flush=flush, file=sys.stderr)


def print_warning(*values: object) -> None:
    """Prints a warning message with formatting."""
    color_printerr(f"{Ansi.YELLOW}{Ansi.BOLD}WARNING:{Ansi.REGULAR}", *values)



def using_clang(env):
    return "clang" in os.path.basename(env["CC"])

def using_gcc(env):
    return "gcc" in os.path.basename(env["CC"])

def using_emcc(env):
    return "emcc" in os.path.basename(env["CC"])

compiler_version_cache = None

def update_compiler_version_cache(value):
    global compiler_version_cache
    compiler_version_cache = value
    return value

def get_compiler_version(env):
    """
    Returns a dictionary with various version information:

    - major, minor, patch: Version following semantic versioning system
    - metadata1, metadata2: Extra information
    - date: Date of the build
    """

    global compiler_version_cache
    if compiler_version_cache is not None:
        return compiler_version_cache

    import shlex

    ret = {
        "major": -1,
        "minor": -1,
        "patch": -1,
        "metadata1": "",
        "metadata2": "",
        "date": "",
        "apple_major": -1,
        "apple_minor": -1,
        "apple_patch1": -1,
        "apple_patch2": -1,
        "apple_patch3": -1,
    }

    if env.get("is_msvc", False) and not using_clang(env):
        try:
            # FIXME: `-latest` works for most cases, but there are edge-cases where this would
            # benefit from a more nuanced search.
            # https://github.com/godotengine/godot/pull/91069#issuecomment-2358956731
            # https://github.com/godotengine/godot/pull/91069#issuecomment-2380836341
            args = [
                env["VSWHERE"],
                "-latest",
                "-prerelease",
                "-products",
                "*",
                "-requires",
                "Microsoft.Component.MSBuild",
                "-utf8",
            ]
            version = subprocess.check_output(args, encoding="utf-8").strip()
            for line in version.splitlines():
                split = line.split(":", 1)
                if split[0] == "catalog_productDisplayVersion":
                    sem_ver = split[1].split(".")
                    ret["major"] = int(sem_ver[0])
                    ret["minor"] = int(sem_ver[1])
                    ret["patch"] = int(sem_ver[2].split()[0])
                # Could potentially add section for determining preview version, but
                # that can wait until metadata is actually used for something.
                if split[0] == "catalog_buildVersion":
                    ret["metadata1"] = split[1]
        except (subprocess.CalledProcessError, OSError):
            print_warning("Couldn't find vswhere to determine compiler version.")
        return update_compiler_version_cache(ret)

    # Not using -dumpversion as some GCC distros only return major, and
    # Clang used to return hardcoded 4.2.1: # https://reviews.llvm.org/D56803
    try:
        version = subprocess.check_output(
            shlex.split(env.subst(env["CXX"]), posix=False) + ["--version"], shell=(os.name == "nt"), encoding="utf-8"
        ).strip()
    except (subprocess.CalledProcessError, OSError):
        print_warning("Couldn't parse CXX environment variable to infer compiler version.")
        return update_compiler_version_cache(ret)

    match = re.search(
        r"(?:(?<=version )|(?<=\) )|(?<=^))"
        r"(?P<major>\d+)"
        r"(?:\.(?P<minor>\d*))?"
        r"(?:\.(?P<patch>\d*))?"
        r"(?:-(?P<metadata1>[0-9a-zA-Z-]*))?"
        r"(?:\+(?P<metadata2>[0-9a-zA-Z-]*))?"
        r"(?: (?P<date>[0-9]{8}|[0-9]{6})(?![0-9a-zA-Z]))?",
        version,
    )
    if match is not None:
        for key, value in match.groupdict().items():
            if value is not None:
                ret[key] = value

    match_apple = re.search(
        r"(?:(?<=clang-)|(?<=\) )|(?<=^))"
        r"(?P<apple_major>\d+)"
        r"(?:\.(?P<apple_minor>\d*))?"
        r"(?:\.(?P<apple_patch1>\d*))?"
        r"(?:\.(?P<apple_patch2>\d*))?"
        r"(?:\.(?P<apple_patch3>\d*))?",
        version,
    )
    if match_apple is not None:
        for key, value in match_apple.groupdict().items():
            if value is not None:
                ret[key] = value

    # Transform semantic versioning to integers
    for key in [
        "major",
        "minor",
        "patch",
        "apple_major",
        "apple_minor",
        "apple_patch1",
        "apple_patch2",
        "apple_patch3",
    ]:
        ret[key] = int(ret[key] or -1)
    return update_compiler_version_cache(ret)

def set_compiler_warnings(env):
    # Enforce our minimal compiler version requirements
    cc_version = get_compiler_version(env)
    cc_version_major = cc_version["major"]
    cc_version_minor = cc_version["minor"]
    cc_version_metadata1 = cc_version["metadata1"]
    
    # Configure compiler warnings
    env.AppendUnique(CCFLAGS=["$WARNLEVEL"])
    if env.get("is_msvc", False) and not using_clang(env):  # MSVC
        # Disable warnings which we don't plan to fix.
        disabled_warnings = [
            "/wd4100",  # C4100 (unreferenced formal parameter): Doesn't play nice with polymorphism.
            "/wd4127",  # C4127 (conditional expression is constant)
            "/wd4201",  # C4201 (non-standard nameless struct/union): Only relevant for C89.
            "/wd4244",  # C4244 C4245 C4267 (narrowing conversions): Unavoidable at this scale.
            "/wd4245",
            "/wd4267",
            "/wd4305",  # C4305 (truncation): double to float or real_t, too hard to avoid.
            "/wd4324",  # C4820 (structure was padded due to alignment specifier)
            "/wd4514",  # C4514 (unreferenced inline function has been removed)
            "/wd4714",  # C4714 (function marked as __forceinline not inlined)
            "/wd4820",  # C4820 (padding added after construct)
        ]
        
        if env["warnings"] == "extra":
            env["WARNLEVEL"] = "/W4"
            env.AppendUnique(CCFLAGS=disabled_warnings)
        elif env["warnings"] == "all":
            env["WARNLEVEL"] = "/W3"
            # C4458 is like -Wshadow. Part of /W4 but let's apply it for the default /W3 too.
            env.AppendUnique(CCFLAGS=["/w34458"] + disabled_warnings)
        elif env["warnings"] == "moderate":
            env["WARNLEVEL"] = "/W2"
            env.AppendUnique(CCFLAGS=disabled_warnings)
        else:  # 'no'
            env["WARNLEVEL"] = "/w"
            # C4267 is particularly finicky & needs to be explicitly disabled.
            env.AppendUnique(CCFLAGS=["/wd4267"])
            
        if env["werror"]:
            env.AppendUnique(CCFLAGS=["/WX"])
            env.AppendUnique(LINKFLAGS=["/WX"])
            
    else:  # GCC, Clang
        common_warnings = []
        if using_gcc(env):
            common_warnings += ["-Wshadow", "-Wno-misleading-indentation"]
            if cc_version_major < 11:
                # Regression in GCC 9/10, spams so much in our variadic templates
                # that we need to outright disable it.
                common_warnings += ["-Wno-type-limits"]
            if cc_version_major == 12:
                # Regression in GCC 12, false positives in our error macros, see GH-58747.
                common_warnings += ["-Wno-return-type"]
            if cc_version_major >= 11:
                common_warnings += ["-Wenum-conversion"]
        elif using_clang(env) or using_emcc(env):
            common_warnings += ["-Wshadow-field-in-constructor", "-Wshadow-uncaptured-local"]
            # We often implement `operator<` for structs of pointers as a requirement
            # for putting them in `Set` or `Map`. We don't mind about unreliable ordering.
            common_warnings += ["-Wno-ordered-compare-function-pointers"]
            common_warnings += ["-Wenum-conversion"]
            
        # clang-cl will interpret `-Wall` as `-Weverything`, workaround with compatibility cast.
        env["WARNLEVEL"] = "-Wall" if not env.get("is_msvc", False) else "-W3"
        
        if env["warnings"] == "extra":
            env.AppendUnique(CCFLAGS=["-Wextra", "-Wwrite-strings", "-Wno-unused-parameter"] + common_warnings)
            env.AppendUnique(CXXFLAGS=["-Wctor-dtor-privacy", "-Wnon-virtual-dtor"])
            if using_gcc(env):
                env.AppendUnique(
                    CCFLAGS=[
                        "-Walloc-zero",
                        "-Wduplicated-branches",
                        "-Wduplicated-cond",
                        "-Wstringop-overflow=4",
                    ]
                )
                env.AppendUnique(CXXFLAGS=["-Wplacement-new=1", "-Wvirtual-inheritance"])
                # Need to fix a warning with AudioServer lambdas before enabling.
                # if cc_version_major != 9:  # GCC 9 had a regression (GH-36325).
                #    env.Append(CXXFLAGS=["-Wnoexcept"])
                if cc_version_major >= 9:
                    env.AppendUnique(CCFLAGS=["-Wattribute-alias=2"])
                if cc_version_major >= 11:  # Broke on MethodBind templates before GCC 11.
                    env.AppendUnique(CCFLAGS=["-Wlogical-op"])
            elif using_clang(env) or using_emcc(env):
                env.AppendUnique(CCFLAGS=["-Wimplicit-fallthrough"])
        elif env["warnings"] == "all":
            env.AppendUnique(CCFLAGS=common_warnings)
        elif env["warnings"] == "moderate":
            env.AppendUnique(CCFLAGS=["-Wno-unused"] + common_warnings)
        else:  # 'no'
            env["WARNLEVEL"] = "-w"
            
        if env["werror"]:
            env.AppendUnique(CCFLAGS=["-Werror"])

