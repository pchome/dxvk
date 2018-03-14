dxvk_include_path = include_directories('./include')

if (cpu_family == 'x86_64') and not get_option('x86_32')
  target_arch = '-m64'
  dxvk_library_path = meson.source_root() + '/linux/lib64'
else
  target_arch = '-m32'
  dxvk_library_path = meson.source_root() + '/linux/lib'
endif

winebuild = find_program('winebuild')
winegcc   = find_program('winegcc')

# vulkan-1.dll
lib_vulkan = declare_dependency(link_args : ['-L'+dxvk_library_path, '-lvulkan-1', '-lpthread'])


wine_flags_list = [ '-DWINEBUILD',

  # disalble min()/max()
  '-DNOMINMAX',

  # from WINE build log
  #'-D__WINESRC__',
  '-D_REENTRANT',
  '-fPIC',
  #'-Wall',
  '-fno-tree-loop-distribute-patterns',
  '-fno-strict-aliasing',
  #'-Wdeclaration-after-statement',
  '-Wempty-body',
  '-Wignored-qualifiers',
  #'-Wno-packed-not-aligned',
  '-Wshift-overflow=2',
  #'-Wstrict-prototypes',
  '-Wtype-limits',
  '-Wunused-but-set-parameter',
  '-Wvla',
  '-Wwrite-strings',
  '-Wpointer-arith',
  '-Wlogical-op',
  '-fno-omit-frame-pointer',

  '-U_FORTIFY_SOURCE',
  '-D_FORTIFY_SOURCE=0',

  '-DWINE_UNICODE_NATIVE',
  '-D_UNICODE',
  '-DUNICODE',
  '-D__WINE__',

  # from winebuild output
  #'-fshort-wchar',

  # for test
  #'-fno-short-wchar',

  #'-DWIN64',
  #'-D_WIN64',
  #'-D__WIN64',
  #'-D__WIN64__',

  #'-D__stdcall=__attribute__((ms_abi))',
  #'-D__cdecl=__attribute__((ms_abi))',
  #'-D_stdcall=__attribute__((ms_abi))',
  #'-D_cdecl=__attribute__((ms_abi))',
  #'-D__fastcall=__attribute__((ms_abi))',
  #'-D_fastcall=__attribute__((ms_abi))',

  #'-D__declspec(x)=__declspec_##x',
  #'-D__declspec_align(x)=__attribute__((aligned(x)))',
  #'-D__declspec_allocate(x)=__attribute__((section(x)))',
  #'-D__declspec_deprecated=__attribute__((deprecated))',
  #'-D__declspec_dllimport=__attribute__((dllimport))',
  #'-D__declspec_dllexport=__attribute__((dllexport))',
  #'-D__declspec_naked=__attribute__((naked))',
  #'-D__declspec_noinline=__attribute__((noinline))',
  #'-D__declspec_noreturn=__attribute__((noreturn))',
  #'-D__declspec_nothrow=__attribute__((nothrow))',
  #'-D__declspec_novtable=__attribute__(())',
  #'-D__declspec_selectany=__attribute__((weak))',
  #'-D__declspec_thread=__thread',

  #'-D__int8=char',
  #'-D__int16=short',
  #'-D__int32=int',
  #'-D__int64=long',


  # additional includes
  #'-I/usr/include/c++/v1',

  #'-Iinclude',
  #'-Isrc/dxbc',
  #'-Isrc/dxvk',

  '-isystem/usr/include/wine/windows' ]

add_global_arguments(target_arch,     language : ['c', 'cpp'])

# TODO: this is for pure gcc build
#add_global_arguments(wine_flags_list, language : ['c', 'cpp'])

tst_wine_flags_list = [
  '-DWINEBUILD',
  '-DNOMINMAX',
#  '-fshort-wchar',
#  '-DWIN64',
#  '-D_WIN64',
#  '-D__WIN64',
#  '-D__WIN64__',
#  '-DWINE_UNICODE_NATIVE',
#  '-D_UNICODE',
#  '-DUNICODE',
#  '-D__WINE__',
#  '-faligned-new',
  '-isystem/usr/include/wine/windows']

add_global_arguments(tst_wine_flags_list, language : ['c', 'cpp'])

