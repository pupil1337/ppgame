def can_build(env, platform):
    return True


def configure(env):
    # 额外的宏定义
    env.Append(CPPDEFINES=["DEBUG_LOAD_THREADED"])
    pass
