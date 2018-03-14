dxvk_include_path = include_directories('./include')

if (cpu_family == 'x86_64') and not get_option('x86_32')
  target_arch = '-m64'
  dxvk_library_path = meson.source_root() + '/linux/lib64'
else
  target_arch = '-m32'
  dxvk_library_path = meson.source_root() + '/linux/lib'
endif

winebuild = find_program('winebuild')
#winegcc   = find_program('winegcc')

# vulkan-1.dll
#lib_vulkan = declare_dependency(link_args : ['-L'+dxvk_library_path, '-lvulkan-1', '-lpthread'])
lib_vulkan = declare_dependency()

#lib_wine = dxvk_compiler.find_library('wine')

# FIXME: hardcoded WINE path
wine_library_path = '/usr/lib64/wine-staging-3.3'
winecrt0_library_path = wine_library_path + '/wine'

#lib_wine = declare_dependency(link_args : ['-L'+wine_library_path, '-lwine', '-lm', '-lc', '-lpthread'])
#lib_winecrt0 = declare_dependency(link_args : ['-L'+wine_library_path+'/wine', '-lwinecrt0'])

wine_flags_list = [
  target_arch,

  '-fPIC',
  '-D_REENTRANT',

  '-DWINEBUILD',
  '-DNOMINMAX',    # disalble min()/max()
  '-faligned-new', # silence gcc aligned "new" warnings

  '-DWINE_UNICODE_NATIVE',

  '-fasynchronous-unwind-tables',
  '-U_FORTIFY_SOURCE',
  '-D_FORTIFY_SOURCE=0',


  '-D_UNICODE',
  '-DUNICODE',
  '-D__WINE__',

  # from winebuild output
  '-fshort-wchar',

  '-DWIN64',
  '-D_WIN64',
  '-D__WIN64',
  '-D__WIN64__',

  '-DWIN32',
  '-D_WIN32',
  '-D__WIN32',
  '-D__WIN32__',
  '-D__WINNT',
  '-D__WINNT__',

  '-D__stdcall=__attribute__((ms_abi))',
  '-D__cdecl=__attribute__((ms_abi))',
  '-D_stdcall=__attribute__((ms_abi))',
  '-D_cdecl=__attribute__((ms_abi))',
  '-D__fastcall=__attribute__((ms_abi))',
  '-D_fastcall=__attribute__((ms_abi))',

  '-D__declspec(x)=__declspec_##x',
  '-D__declspec_align(x)=__attribute__((aligned(x)))',
  '-D__declspec_allocate(x)=__attribute__((section(x)))',
  '-D__declspec_deprecated=__attribute__((deprecated))',
  '-D__declspec_dllimport=__attribute__((dllimport))',
  '-D__declspec_dllexport=__attribute__((dllexport))',
  '-D__declspec_naked=__attribute__((naked))',
  '-D__declspec_noinline=__attribute__((noinline))',
  '-D__declspec_noreturn=__attribute__((noreturn))',
  '-D__declspec_nothrow=__attribute__((nothrow))',
  '-D__declspec_novtable=__attribute__(())',
  '-D__declspec_selectany=__attribute__((weak))',
  '-D__declspec_thread=__thread',

  '-D__int8=char',
  '-D__int16=short',
  '-D__int32=int',
  '-D__int64=long',

  '-isystem/usr/include/wine/windows']

add_global_arguments(wine_flags_list, language : ['c', 'cpp'])
