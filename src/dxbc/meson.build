dxbc_src = files([
  'dxbc_chunk_isgn.cpp',
  'dxbc_chunk_shex.cpp',
  'dxbc_common.cpp',
  'dxbc_compiler.cpp',
  'dxbc_defs.cpp',
  'dxbc_decoder.cpp',
  'dxbc_header.cpp',
  'dxbc_module.cpp',
  'dxbc_names.cpp',
  'dxbc_options.cpp',
  'dxbc_reader.cpp',
  'dxbc_util.cpp',
])

if (get_option('wine-build'))
dxbc_lib = static_library('dxbc', dxbc_src,
  dependencies : [ spirv_dep ],
  include_directories : [ dxvk_include_path ])
else
dxbc_lib = static_library('dxbc', dxbc_src,
  include_directories : [ dxvk_include_path ])
endif

dxbc_dep = declare_dependency(
  link_with           : [ dxbc_lib ],
  include_directories : [ dxvk_include_path, include_directories('.') ])
