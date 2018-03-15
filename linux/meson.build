dxvk_include_path = include_directories('./include')

# path to libwine.so
wine_library_path = get_option('wine-libdir')

if (cpu_family == 'x86_64') and not get_option('x86_32')
  target_arch = '-m64'
  dxvk_library_path = meson.source_root() + '/linux/lib64'
  if (wine_library_path == '')
    wine_library_path = '/usr/lib64/wine'
  endif
else
  target_arch = '-m32'
  dxvk_library_path = meson.source_root() + '/linux/lib'
  if (wine_library_path == '')
    wine_library_path = '/usr/lib/wine'
  endif
endif

# path to libwinecrt0.a
winecrt0_library_path = wine_library_path + '/wine'

# needed to generate WINE *.dll and dependency objects
winebuild = find_program('winebuild')

# vulkan-1.dll
#lib_vulkan = declare_dependency(link_args : ['-L'+dxvk_library_path, '-lvulkan-1', '-lpthread'])
# FIXME: used in src/dxvk/
lib_vulkan = declare_dependency()

# -----------------------------------------------------------
# flags used by winegcc to build binaries
# -----------------------------------------------------------
wine_x86_64_flags = []

if (target_arch == '-m64')
  wine_x86_64_flags = [
    '-DWIN64',
    '-D_WIN64',
    '-D__WIN64',
    '-D__WIN64__' ]
  
  wine_call_defs = [
    '-D__stdcall=__attribute__((ms_abi))',
    '-D__cdecl=__attribute__((ms_abi))',
    '-D_stdcall=__attribute__((ms_abi))',
    '-D_cdecl=__attribute__((ms_abi))',
    '-D__fastcall=__attribute__((ms_abi))',
    '-D_fastcall=__attribute__((ms_abi))' ]

  wine_long_type = '-D__int64=long'
else
  wine_x86_64_flags = [
    '-D__i386__',
    '-U__x86_64__',
    '-UWIN64',
    '-U_WIN64',
    '-U__WIN64',
    '-U__WIN64__' ]

  wine_call_defs = [
    '-D__stdcall=__attribute__((__stdcall__)) __attribute__((__force_align_arg_pointer__))',
    '-D__cdecl=__attribute__((__cdecl__)) __attribute__((__force_align_arg_pointer__))',
    '-D_stdcall=__attribute__((__stdcall__)) __attribute__((__force_align_arg_pointer__))',
    '-D_cdecl=__attribute__((__cdecl__)) __attribute__((__force_align_arg_pointer__))',
    '-D__fastcall=__attribute__((__fastcall__))',
    '-D_fastcall=__attribute__((__fastcall__))' ]

  wine_long_type = '-D__int64=long long'
endif

wine_flags_list = [
  target_arch,

  '-fPIC',
  '-D_REENTRANT',

  '-DWINEBUILD',
  '-DNOMINMAX',    # disalble min()/max()
  '-faligned-new', # silence gcc aligned "new" warnings

  '-DWINE_UNICODE_NATIVE',

  #'-fasynchronous-unwind-tables',
  #'-U_FORTIFY_SOURCE',
  #'-D_FORTIFY_SOURCE=0',


  '-D_UNICODE',
  '-DUNICODE',
  '-D__WINE__',

  # from winebuild output
  '-fshort-wchar',

  wine_x86_64_flags,

  '-DWIN32',
  '-D_WIN32',
  '-D__WIN32',
  '-D__WIN32__',
  '-D__WINNT',
  '-D__WINNT__',

  wine_call_defs,

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
  wine_long_type,

  '-isystem/usr/include/wine/windows']

add_global_arguments(wine_flags_list, language : ['c', 'cpp'])
add_global_link_arguments(wine_flags_list, language : ['c', 'cpp'])
