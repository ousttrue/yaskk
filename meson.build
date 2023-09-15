project(
    'yaskk',
    'c',
    'cpp',
    default_options: ['c_std=c99'],
)

executable(
    'yaskk',
    [
        'main.cpp',
        'yaskk.cpp',
        'skk.cpp',
        'util.cpp',
        'line.cpp',
        'dict.cpp',
        'utf8.cpp',
    ],
    install: true,
    c_args: [
        ['-Werror-implicit-function-declaration'],
    ],
)
