if (get_option('wine-build'))
test_dxbc_deps = [ dxbc_dep, dxvk_dep, declare_dependency(link_args : ['-mwindows']) ]

executable('dxbc-compiler', files('test_dxbc_compiler.cpp'), dependencies : test_dxbc_deps, name_suffix: 'exe', install : true)
executable('dxbc-disasm',   files('test_dxbc_disasm.cpp'),   dependencies : [ test_dxbc_deps, lib_d3dcompiler_47 ], name_suffix: 'exe', install : true)
executable('hlsl-compiler', files('test_hlsl_compiler.cpp'), dependencies : [ test_dxbc_deps, lib_d3dcompiler_47 ], name_suffix: 'exe', install : true)

executable('dxbc-compiler.exe', build_by_default: false, name_suffix: 'so', install : true)
executable('dxbc-disasm.exe', build_by_default: false, name_suffix: 'so', install : true)
executable('hlsl-compiler.exe', build_by_default: false, name_suffix: 'so', install : true)
else
test_dxbc_deps = [ dxbc_dep, dxvk_dep ]

executable('dxbc-compiler', files('test_dxbc_compiler.cpp'), dependencies : test_dxbc_deps, install : true)
executable('dxbc-disasm',   files('test_dxbc_disasm.cpp'),   dependencies : [ test_dxbc_deps, lib_d3dcompiler_47 ], install : true)
executable('hlsl-compiler', files('test_hlsl_compiler.cpp'), dependencies : [ test_dxbc_deps, lib_d3dcompiler_47 ], install : true)
endif