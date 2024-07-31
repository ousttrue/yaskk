const std = @import("std");

const flags = [_][]const u8{
    "-std=c23",
    "-D_XOPEN_SOURCE=600",
    "-DPATH_TO_DICT=\"~/.skk\"",
};

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .target = target,
        .optimize = optimize,
        .name = "yaskk",
        // .root_source_file = b.path("src/main.zig"),
    });
    exe.addCSourceFiles(.{
        .files = &.{
            "dict.c",
            "line.c",
            "skk.c",
            "utf8.c",
            "util.c",
            "yaskk.c",
        },
        .flags = &flags,
    });
    exe.linkLibC();
    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }
    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);

    const exe_unit_tests = b.addTest(.{
        .root_source_file = b.path("src/main.zig"),
        .target = target,
        .optimize = optimize,
    });
    const run_exe_unit_tests = b.addRunArtifact(exe_unit_tests);
    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&run_exe_unit_tests.step);

    const sortdict = b.addExecutable(.{
        .target = target,
        .optimize = optimize,
        .name = "sortdict",
    });
    sortdict.addCSourceFiles(.{
        .files = &.{
            "tools/sortdict.c",
            "util.c",
        },
        .flags = &flags,
    });
    sortdict.linkLibC();
    b.installArtifact(sortdict);
}
