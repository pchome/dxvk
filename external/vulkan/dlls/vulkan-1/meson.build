vulkan1_dll = shared_library('vulkan-1.dll',
  name_prefix         : '',
  dependencies        : [ wineport_dep ],
  include_directories : include_path,
  objects             : 'vulkan-1.spec',
  install             : true)


vulkan1_dll_target = custom_target('vulkan-1.dll',
  output  : 'vulkan-1.dll',
  input   : 'vulkan-1.spec',
  command : [ winebuild, target_arch, '--dll', '--fake-module', '-E', '@INPUT@', '-o', '@OUTPUT@', '-F', '@BASENAME@.dll' ],
  install : true,
  install_dir : 'dlls')



vulkan1_def_target = custom_target('vulkan-1.def',
  output  : 'vulkan-1.def',
  input   : 'vulkan-1.spec',
  command : [ winebuild, target_arch, '-w', '--def', '--export', '@INPUT@', '-o', '@OUTPUT@' ],
  install : true,
  install_dir : 'defs')
