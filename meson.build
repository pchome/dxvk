project('dxvk', ['c', 'cpp'])

cpu_family = target_machine.cpu_family()

dxvk_compiler = meson.get_compiler('cpp')
if dxvk_compiler.get_id() == 'msvc'
  add_global_arguments('-DNOMINMAX', language : 'cpp')
  dxvk_cpp_std='c++latest'
else
  dxvk_cpp_std='c++1z'
endif

dxvk_include_path = include_directories('./include')

if (cpu_family == 'x86_64')
  dxvk_library_path = meson.source_root() + '/lib'
else
  dxvk_library_path = meson.source_root() + '/lib32'
endif

if not get_option('wine-build')
lib_vulkan = dxvk_compiler.find_library('vulkan-1', dirs : dxvk_library_path)

lib_spirvtools     = dxvk_compiler.find_library('libSPIRV-Tools',     dirs : dxvk_library_path)
lib_spirvtools_opt = dxvk_compiler.find_library('libSPIRV-Tools-opt', dirs : dxvk_library_path)

lib_d3d11          = dxvk_compiler.find_library('d3d11')
lib_dxgi           = dxvk_compiler.find_library('dxgi')
if dxvk_compiler.get_id() != 'msvc'
  lib_d3dcompiler_47 = dxvk_compiler.find_library('d3dcompiler_47')
endif

else
  # linux specific settings
  subdir('linux')
endif

if (get_option('hud'))
  add_global_arguments('-DWANT_HUD', language : ['c', 'cpp'])

  glsl_compiler = find_program('glslangValidator')
  glsl_generator = generator(glsl_compiler,
    output    : [ '@BASENAME@.h' ],
    arguments : [ '-V', '--vn', '@BASENAME@', '@INPUT@', '-o', '@OUTPUT@' ])
endif

if (get_option('dll-redirects'))
  redirect_suffix = '_vk'
else
  redirect_suffix = ''
endif

if (get_option('env'))
  add_global_arguments('-DWANT_ENV', language : ['c', 'cpp'])
endif

if (get_option('logger'))
  add_global_arguments('-DWANT_LOGGER', language : ['c', 'cpp'])
endif


subdir('src')

if dxvk_compiler.get_id() != 'msvc'
if (get_option('tests'))
  subdir('tests')
endif

if (get_option('utils'))
  subdir('wine_utils')
endif
endif

# linux specific build targets
if get_option('wine-build')
  subdir('linux/build')
endif
