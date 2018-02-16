vulkan_src = [
  'vulkan_main.c',
  'vulkan_thunks.c',
]

vulkan_dll = shared_library('vulkan.dll', vulkan_src,
  name_prefix         : '',
  dependencies        : [ lib_user32, wineport_dep, lib_X11, lib_Xext ],
  include_directories : include_path,
  objects             : 'vulkan.spec',
  install             : true)



vulkan_dll_target = custom_target('vulkan.dll',
  output  : 'vulkan.dll',
  input   : 'vulkan.spec',
  command : [ winebuild, target_arch, '--dll', '--fake-module', '-E', '@INPUT@', '-o', '@OUTPUT@', '-F', '@BASENAME@.dll' ],
  install : true,
  install_dir : 'dlls')



vulkan_def_target = custom_target('vulkan.def',
  output  : 'vulkan.def',
  input   : 'vulkan.spec',
  command : [ winebuild, target_arch, '-w', '--def', '--export', '@INPUT@', '-o', '@OUTPUT@' ],
  install : true,
  install_dir : 'defs')

