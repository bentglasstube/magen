package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "magen",
    data = ["//content"],
    linkopts = [
        "-lSDL2",
        "-lSDL2_mixer",
    ],
    srcs = ["main.cc"],
    deps = [
        ":music_screen",
        "@libgam//:game",
    ],
)

cc_library(
    name = "music_generator",
    srcs = ["music_generator.cc"],
    hdrs = ["music_generator.h"],
)

cc_library(
    name = "music_screen",
    srcs = ["music_screen.cc"],
    hdrs = ["music_screen.h"],
    deps = [
        ":music_generator",
        "@libgam//:screen",
        "@libgam//:text",
    ],
)
