spirv_src = files([
  'spirv_code_buffer.cpp',
  'spirv_module.cpp',
])

if (get_option('wine-build') == false)
spirv_lib = static_library('spirv', spirv_src,
  include_directories : [ dxvk_include_path ],
  dependencies        : [ lib_spirvtools, lib_spirvtools_opt ])

else
spirv_lib = static_library('spirv', spirv_src,
  include_directories : [ dxvk_include_path ],
  dependencies        : [ lib_spirvtools ])
#spirv_dep = declare_dependency(
#  link_with           : [ spirv_lib ],
#  include_directories : [ dxvk_include_path, include_directories('.') ])
endif

