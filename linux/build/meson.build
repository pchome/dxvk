# -----------------------------------------------------------
# d3d11 part
# -----------------------------------------------------------

d3d11_source_dir = meson.source_root() + '/src/d3d11/'
d3d11_install_dir = get_option('libdir') + '/wine'
d3d11_build_dir = 'linux/build/d3d11'+ redirect_suffix +'.dll@sha/'

# add full path to sources
d3d11_src_path = []
d3d11_obj_path = []
foreach src : d3d11_src
  d3d11_src_path += d3d11_source_dir + src
  d3d11_obj_path += d3d11_build_dir + src + '.o'
endforeach

d3d11_wine_link = declare_dependency(link_args : [
  '-Wl,-Bsymbolic',
  '-Wl,-z,defs',
  '-Wl,-init,__wine_spec_init,-fini,__wine_spec_fini',
  '-L' + wine_library_path,
  '-L' + winecrt0_library_path,
  '-lwinecrt0', '-lwine', '-lm', '-lc', '-lpthread' ])

#d3d11_dxgi_link = declare_dependency(link_args : ['-L'+dxvk_library_path, '-ldxgi'+redirect_suffix])

# create d3d11 dependency object for WINE
d3d11_wine_dep_target = custom_target('d3d11.wine',
  output  : 'd3d11'+redirect_suffix+'.spec.o',
  input   : 'd3d11.spec',
  command : [ winebuild,
    target_arch, '-fno-asynchronous-unwind-tables', '--dll', '-D_REENTRANT', '-fPIC',
    '-E', '@INPUT@', '-o', '@OUTPUT@',
    '--',
    d3d11_obj_path,

    util_lib.full_path(),
    dxvk_lib.full_path(),
    spirv_lib.full_path(),

    dxvk_library_path + '/libvulkan-1.def',
    dxvk_library_path + '/libdxgi'+ redirect_suffix +'.def',

    wine_library_path + '/wine/libwinecrt0.a',

    wine_library_path + '/wine/libadvapi32.def',
    wine_library_path + '/wine/libuser32.def',
    wine_library_path + '/wine/libkernel32.def',
    wine_library_path + '/wine/libntdll.def' ],

  depend_files : d3d11_src_path,
  depends      : [ util_lib, dxvk_lib, spirv_lib, dxbc_lib ], # build all before link
  install : false)


# create d3d11.dll.so for WINE
d3d11_dll = shared_library('d3d11'+redirect_suffix+'.dll', d3d11_src_path, d3d11_wine_dep_target,
  name_prefix         : '',
  link_with           : [ util_lib ],
  dependencies        : [ d3d11_wine_link, dxbc_dep, dxvk_dep ],
  include_directories : dxvk_include_path,
#  objects             : 'd3d11.spec',
  install             : true,
  install_dir         : d3d11_install_dir)


# create fake d3d11.dll for WINE
d3d11_dll_target = custom_target('d3d11.fake',
  output  : 'd3d11'+redirect_suffix+'.dll',
  input   : 'd3d11.spec',
  command : [ winebuild, target_arch, '--dll', '--fake-module', '-E', '@INPUT@', '-o', '@OUTPUT@', '-F', '@BASENAME@'+redirect_suffix+'.dll' ],
  install : true,
  install_dir : d3d11_install_dir + '/fakedlls')


#d3d11_dep = declare_dependency(
#  link_with           : [ d3d11_dll ],
#  include_directories : [ dxvk_include_path, include_directories('.') ])


# -----------------------------------------------------------
# dxgi part
# -----------------------------------------------------------

dxgi_source_dir = meson.source_root() + '/src/dxgi/'
dxgi_install_dir = get_option('libdir') + '/wine'
dxgi_build_dir = 'linux/build/dxgi'+ redirect_suffix +'.dll@sha/'

# add full path to sources
dxgi_src_path = []
dxgi_obj_path = []
foreach src : dxgi_src
  dxgi_src_path += dxgi_source_dir + src
  dxgi_obj_path += dxgi_build_dir + src + '.o'
endforeach

dxgi_wine_link = declare_dependency(link_args : [
  '-Wl,-Bsymbolic',
  '-Wl,-z,defs',
  '-Wl,-init,__wine_spec_init,-fini,__wine_spec_fini',
  '-L' + wine_library_path,
  '-L' + winecrt0_library_path,
  '-lwinecrt0', '-lwine', '-lm', '-lc', '-lpthread' ])

# create dxgi dependency object for WINE
dxgi_wine_dep_target = custom_target('dxgi.wine',
  output  : 'dxgi'+redirect_suffix+'.spec.o',
  input   : 'dxgi.spec',
  command : [ winebuild,
    target_arch, '-fno-asynchronous-unwind-tables', '--dll', '-D_REENTRANT', '-fPIC',
    '-E', '@INPUT@', '-o', '@OUTPUT@',
    '--',
    dxgi_obj_path,

    util_lib.full_path(),
    dxvk_lib.full_path(),
    spirv_lib.full_path(),

    dxvk_library_path + '/libvulkan-1.def',

    wine_library_path + '/wine/libwinecrt0.a',

    wine_library_path + '/wine/libadvapi32.def',
    wine_library_path + '/wine/libuser32.def',
    wine_library_path + '/wine/libkernel32.def',
    wine_library_path + '/wine/libntdll.def' ],

  depend_files : dxgi_src_path,
  depends      : [ util_lib, dxvk_lib, spirv_lib, dxbc_lib ], # build all before link
  install : false)


# create dxgi.dll.so for WINE
dxgi_dll = shared_library('dxgi'+redirect_suffix+'.dll', dxgi_src_path, dxgi_wine_dep_target,
  name_prefix         : '',
  link_with           : [ util_lib ],
  dependencies        : [ dxgi_wine_link, dxvk_dep ],
  include_directories : dxvk_include_path,
#  objects             : 'dxgi.spec',
  install             : true,
  install_dir         : dxgi_install_dir)


# create fake dxgi.dll for WINE
dxgi_dll_target = custom_target('dxgi.fake',
  output  : 'dxgi'+redirect_suffix+'.dll',
  input   : 'dxgi.spec',
  command : [ winebuild, target_arch, '--dll', '--fake-module', '-E', '@INPUT@', '-o', '@OUTPUT@', '-F', '@BASENAME@'+redirect_suffix+'.dll' ],
  install : true,
  install_dir : dxgi_install_dir + '/fakedlls')

#dxgi_dep = declare_dependency(
#  link_with           : [ dxgi_dll ],
#  include_directories : [ dxvk_include_path, include_directories('.') ])

# -----------------------------------------------------------
# tests part
# -----------------------------------------------------------
# name.exe and name.exe.so pairs are to be generated for WINE

if get_option('enable_tests')

# tests/dxbc
test_dxbc_src_dir = meson.source_root() + '/tests/dxbc/'
test_dxbc_deps = [ dxbc_dep, dxvk_dep, declare_dependency(link_args : ['-mwindows']) ]
test_hlsl_deps = [ test_dxbc_deps, declare_dependency(link_args : ['-L'+dxvk_library_path, '-ld3dcompiler_47']) ]

executable('dxbc-compiler', files(test_dxbc_src_dir + 'test_dxbc_compiler.cpp'),
  dependencies : test_dxbc_deps,
  name_suffix: 'exe', install : get_option('install-tests'))

executable('dxbc-disasm',   files(test_dxbc_src_dir + 'test_dxbc_disasm.cpp'),
  dependencies : test_hlsl_deps,
  name_suffix: 'exe', install : get_option('install-tests'))

executable('hlsl-compiler', files(test_dxbc_src_dir + 'test_hlsl_compiler.cpp'),
  dependencies : test_hlsl_deps,
  name_suffix: 'exe', install : get_option('install-tests'))

# installation control for name.exe
executable('dxbc-compiler.exe', build_by_default: false, name_suffix: 'so', install : get_option('install-tests'))
executable('dxbc-disasm.exe',   build_by_default: false, name_suffix: 'so', install : get_option('install-tests'))
executable('hlsl-compiler.exe', build_by_default: false, name_suffix: 'so', install : get_option('install-tests'))


# tests/d3d11
test_d3d11_src_dir = meson.source_root() + '/tests/d3d11/'
test_d3d11_deps = [ util_dep, declare_dependency(
    link_args : ['-L'+dxvk_library_path, '-ldxgi', '-ld3d11', '-ld3dcompiler_47','-mwindows']) ]

executable('d3d11-compute',  files(test_d3d11_src_dir + 'test_d3d11_compute.cpp'),
  dependencies : test_d3d11_deps,
  name_suffix: 'exe', install : get_option('install-tests'))

executable('d3d11-triangle', files(test_d3d11_src_dir + 'test_d3d11_triangle.cpp'),
  dependencies : test_d3d11_deps,
  name_suffix: 'exe', install : get_option('install-tests'))

# installation control for name.exe
executable('d3d11-compute.exe',  build_by_default: false, name_suffix: 'so', install : get_option('install-tests'))
executable('d3d11-triangle.exe', build_by_default: false, name_suffix: 'so', install : get_option('install-tests'))


# tests/dxgi
test_dxgi_src_dir = meson.source_root() + '/tests/dxgi/'
test_dxgi_deps = [ util_dep, declare_dependency(link_args : ['-L'+dxvk_library_path, '-ldxgi', '-mwindows']) ]

executable('dxgi-factory', files(test_dxgi_src_dir + 'test_dxgi_factory.cpp'),
  dependencies : test_dxgi_deps,
  name_suffix: 'exe', install: get_option('install-tests'))

# installation control for name.exe
executable('dxgi-factory.exe', build_by_default: false, name_suffix: 'so', install : get_option('install-tests'))

endif # get_option('enable_tests')
