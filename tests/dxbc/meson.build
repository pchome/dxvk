if (get_option('wine-build'))
test_dxbc_deps = [ dxbc_dep, dxvk_dep, declare_dependency(link_args : ['-mwindows']) ]
test_hlsl_deps = [ test_dxbc_deps, declare_dependency(link_args : ['-L'+dxvk_library_path, '-ld3dcompiler_47']) ]

executable('dxbc-compiler', files('test_dxbc_compiler.cpp'), dependencies : test_dxbc_deps, name_suffix: 'exe', install : get_option('install-tests'))
executable('dxbc-disasm',   files('test_dxbc_disasm.cpp'),   dependencies : test_hlsl_deps, name_suffix: 'exe', install : get_option('install-tests'))
executable('hlsl-compiler', files('test_hlsl_compiler.cpp'), dependencies : test_hlsl_deps, name_suffix: 'exe', install : get_option('install-tests'))

executable('dxbc-compiler.exe', build_by_default: false, name_suffix: 'so', install : get_option('install-tests'))
executable('dxbc-disasm.exe',   build_by_default: false, name_suffix: 'so', install : get_option('install-tests'))
executable('hlsl-compiler.exe', build_by_default: false, name_suffix: 'so', install : get_option('install-tests'))
else
test_dxbc_deps = [ dxbc_dep, dxvk_dep ]

executable('dxbc-compiler', files('test_dxbc_compiler.cpp'), dependencies : test_dxbc_deps, install : get_option('install-tests'))
executable('dxbc-disasm',   files('test_dxbc_disasm.cpp'),   dependencies : [ test_dxbc_deps, lib_d3dcompiler_47 ], install : get_option('install-tests'))
executable('hlsl-compiler', files('test_hlsl_compiler.cpp'), dependencies : [ test_dxbc_deps, lib_d3dcompiler_47 ], install : get_option('install-tests'))
endif
