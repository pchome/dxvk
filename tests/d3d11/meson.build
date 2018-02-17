if (get_option('wine-build'))
test_d3d11_deps = [ util_dep, declare_dependency(
    link_args : ['-L'+dxvk_library_path, '-ldxgi', '-ld3d11', '-ld3dcompiler_47','-mwindows']) ]

executable('d3d11-compute',  files('test_d3d11_compute.cpp'),  dependencies : test_d3d11_deps, name_suffix: 'exe', install : get_option('install-tests'))
executable('d3d11-triangle', files('test_d3d11_triangle.cpp'), dependencies : test_d3d11_deps, name_suffix: 'exe', install : get_option('install-tests'))

executable('d3d11-compute.exe',  build_by_default: false, name_suffix: 'so', install : get_option('install-tests'))
executable('d3d11-triangle.exe', build_by_default: false, name_suffix: 'so', install : get_option('install-tests'))
else
test_d3d11_deps = [ util_dep, lib_dxgi, lib_d3d11, lib_d3dcompiler_47 ]

executable('d3d11-compute',  files('test_d3d11_compute.cpp'),  dependencies : test_d3d11_deps, install : get_option('install-tests'))
executable('d3d11-triangle', files('test_d3d11_triangle.cpp'), dependencies : test_d3d11_deps, install : get_option('install-tests'))
endif
