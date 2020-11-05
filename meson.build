project(
  'stb',
  'c',
  'cpp',
  version : '0.0.1',
  license : 'Mit'
)

incdir = include_directories('.')

stb_dep = declare_dependency(
    include_directories : incdir,
    version: meson.project_version()
)

if meson.version().version_compare('>=0.54.0')
    meson.override_dependency('stb', stb_dep)
endif
