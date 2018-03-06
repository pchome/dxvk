# prevent creating immutable build target
if not get_option('wine-build')

test_dxgi_deps = [ util_dep, lib_dxgi ]

executable('dxgi-factory', files('test_dxgi_factory.cpp'), dependencies : test_dxgi_deps, install: true)

endif
