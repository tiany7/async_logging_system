
cc_library(
    name = "wwfastlog",
    hdrs = ["async_logger.h",
            "fastlog.h",
            "util.h",
            "environment.h",],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "log_test",
    srcs = ["main.cpp",],
    deps = [":wwfastlog"],
    copts = ["-std=c++17"],
)