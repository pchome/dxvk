if (get_option('wine-build'))
test_dxgi_deps = [ util_dep, lib_dxgi, declare_dependency(link_args : ['-mwindows']) ]

executable('dxgi-factory', files('test_dxgi_factory.cpp'), dependencies : test_dxgi_deps, name_suffix: 'exe', install: true)

executable('dxgi-factory.exe', build_by_default: false, name_suffix: 'so', install : true)
else
test_dxgi_deps = [ util_dep, lib_dxgi ]

executable('dxgi-factory', files('test_dxgi_factory.cpp'), dependencies : test_dxgi_deps, install: true)
endif