import os
import subprocess
import re

# =================================================================================
# copy from godot

def using_clang(env):
    return "clang" in os.path.basename(env["CC"])

def using_gcc(env):
    return "gcc" in os.path.basename(env["CC"])

def using_emcc(env):
    return "emcc" in os.path.basename(env["CC"])

def get_compiler_version(env):
    """
    Returns a dictionary with various version information:

    - major, minor, patch: Version following semantic versioning system
    - metadata1, metadata2: Extra information
    - date: Date of the build
    """
    ret = {
        "major": -1,
        "minor": -1,
        "patch": -1,
        "metadata1": None,
        "metadata2": None,
        "date": None,
        "apple_major": -1,
        "apple_minor": -1,
        "apple_patch1": -1,
        "apple_patch2": -1,
        "apple_patch3": -1,
    }

    if not env.get("is_msvc", False):
        # Not using -dumpversion as some GCC distros only return major, and
        # Clang used to return hardcoded 4.2.1: # https://reviews.llvm.org/D56803
        try:
            version = (
                subprocess.check_output([env.subst(env["CXX"]), "--version"], shell=(os.name == "nt"))
                .strip()
                .decode("utf-8")
            )
        except (subprocess.CalledProcessError, OSError):
            print("warning: Couldn't parse CXX environment variable to infer compiler version.")
            return ret
    else:
        # TODO: Implement for MSVC
        return ret
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
    return ret

def set_compiler_warnings(env):
    if env.get("is_msvc", False):  # MSVC
        if env["warnings"] == "no":
            env.Append(CCFLAGS=["/w"])
        else:
            if env["warnings"] == "extra":
                env.Append(CCFLAGS=["/W4"])
            elif env["warnings"] == "all":
                # C4458 is like -Wshadow. Part of /W4 but let's apply it for the default /W3 too.
                env.Append(CCFLAGS=["/W3", "/w34458"])
            elif env["warnings"] == "moderate":
                env.Append(CCFLAGS=["/W2"])
            # Disable warnings which we don't plan to fix.

        env.Append(
            CCFLAGS=[
                "/wd4100",  # C4100 (unreferenced formal parameter): Doesn't play nice with polymorphism.
                "/wd4127",  # C4127 (conditional expression is constant)
                "/wd4201",  # C4201 (non-standard nameless struct/union): Only relevant for C89.
                "/wd4244",  # C4244 C4245 C4267 (narrowing conversions): Unavoidable at this scale.
                "/wd4245",
                "/wd4267",
                "/wd4305",  # C4305 (truncation): double to float or real_t, too hard to avoid.
                "/wd4514",  # C4514 (unreferenced inline function has been removed)
                "/wd4714",  # C4714 (function marked as __forceinline not inlined)
                "/wd4820",  # C4820 (padding added after construct)
            ]
        )

        if env["werror"]:
            env.Append(CCFLAGS=["/WX"])
            env.Append(LINKFLAGS=["/WX"])

    else:  # GCC, Clang
        cc_version = get_compiler_version(env) or {
            "major": None,
            "minor": None,
            "patch": None,
            "metadata1": None,
            "metadata2": None,
            "date": None
            }
        cc_version_major = int(cc_version["major"] or -1)
        cc_version_minor = int(cc_version["minor"] or -1)

        common_warnings = []

        if using_gcc(env):
            common_warnings += ["-Wshadow", "-Wno-misleading-indentation"]
            if cc_version_major == 7:  # Bogus warning fixed in 8+.
                common_warnings += ["-Wno-strict-overflow"]
            if cc_version_major < 11:
                # Regression in GCC 9/10, spams so much in our variadic templates
                # that we need to outright disable it.
                common_warnings += ["-Wno-type-limits"]
            if cc_version_major >= 12:  # False positives in our error macros, see GH-58747.
                common_warnings += ["-Wno-return-type"]
        elif using_clang(env) or using_emcc(env):
            common_warnings += ["-Wshadow-field-in-constructor", "-Wshadow-uncaptured-local"]
            # We often implement `operator<` for structs of pointers as a requirement
            # for putting them in `Set` or `Map`. We don't mind about unreliable ordering.
            common_warnings += ["-Wno-ordered-compare-function-pointers"]

        if env["warnings"] == "extra":
            env.Append(CCFLAGS=["-Wall", "-Wextra", "-Wwrite-strings", "-Wno-unused-parameter"] + common_warnings)
            env.Append(CXXFLAGS=["-Wctor-dtor-privacy", "-Wnon-virtual-dtor"])
            if using_gcc(env):
                env.Append(
                    CCFLAGS=[
                        "-Walloc-zero",
                        "-Wduplicated-branches",
                        "-Wduplicated-cond",
                        "-Wstringop-overflow=4",
                    ]
                )
                env.Append(CXXFLAGS=["-Wplacement-new=1"])
                # Need to fix a warning with AudioServer lambdas before enabling.
                # if cc_version_major != 9:  # GCC 9 had a regression (GH-36325).
                #    env.Append(CXXFLAGS=["-Wnoexcept"])
                if cc_version_major >= 9:
                    env.Append(CCFLAGS=["-Wattribute-alias=2"])
                if cc_version_major >= 11:  # Broke on MethodBind templates before GCC 11.
                    env.Append(CCFLAGS=["-Wlogical-op"])
            elif using_clang(env) or using_emcc(env):
                env.Append(CCFLAGS=["-Wimplicit-fallthrough"])
        elif env["warnings"] == "all":
            env.Append(CCFLAGS=["-Wall"] + common_warnings)
        elif env["warnings"] == "moderate":
            env.Append(CCFLAGS=["-Wall", "-Wno-unused"] + common_warnings)
        else:  # 'no'
            env.Append(CCFLAGS=["-w"])

        if env["werror"]:
            env.Append(CCFLAGS=["-Werror"])
