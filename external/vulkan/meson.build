project('vulkan', ['c'])

cpu_family = target_machine.cpu_family()

include_path = include_directories('./include')

compiler = meson.get_compiler('c')

lib_X11    = compiler.find_library('X11')
lib_Xext   = compiler.find_library('Xext')
lib_user32 = compiler.find_library('user32')
lib_vulkan = compiler.find_library('vulkan')

winebuild = find_program('winebuild')
winegcc   = find_program('winegcc')

if (cpu_family == 'x86_64')
target_arch = '-m64'
else
target_arch = '-m32'
endif

def_generator = generator(winebuild,
  output    : [ '@BASENAME@.def' ],
  arguments : [ '-w', ' --def', '--export', '@INPUT@', '-o', '@OUTPUT@' ])

subdir('libs')
subdir('dlls')
