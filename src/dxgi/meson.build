dxgi_src = [
  'dxgi_adapter.cpp',
  'dxgi_device.cpp',
  'dxgi_enums.cpp',
  'dxgi_factory.cpp',
  'dxgi_main.cpp',
  'dxgi_output.cpp',
  'dxgi_presenter.cpp',
  'dxgi_swapchain.cpp',
]

if (get_option('wine-build'))
dxgi_dll = shared_library('dxgi'+redirect_suffix+'.dll', dxgi_src,
  name_prefix         : '',
  link_with           : [ util_lib ],
  dependencies        : [ dxvk_dep ],
  include_directories : dxvk_include_path,
  objects             : 'dxgi.spec',
  install             : true,
  install_dir         : get_option('libdir') + '/wine')

dxgi_dll_target = custom_target('dxgi.fake',
  output  : 'dxgi'+redirect_suffix+'.dll',
  input   : 'dxgi.spec',
  command : [ winebuild, target_arch, '--dll', '--fake-module', '-E', '@INPUT@', '-o', '@OUTPUT@', '-F', '@BASENAME@'+redirect_suffix+'.dll' ],
  install : true,
  install_dir : get_option('libdir') + '/wine/fakedlls')
else
dxgi_dll = shared_library('dxgi', dxgi_src,
  name_prefix         : '',
  link_with           : [ util_lib ],
  dependencies        : [ dxvk_dep ],
  include_directories : dxvk_include_path,
  install             : true)
endif

dxgi_dep = declare_dependency(
  link_with           : [ dxgi_dll ],
  include_directories : [ dxvk_include_path, include_directories('.') ])
