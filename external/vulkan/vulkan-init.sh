#!/bin/sh

# prepare tree
git init

mkdir -p libs
mkdir -p include
mkdir -p dlls



# path to WINE sources
git remote add wine_staging git://github.com/wine-compholio/wine-patched.git

# fetch WINE git info
git fetch --depth=1 wine_staging master



# get wine port
cd libs
git checkout wine_staging/master -- ../libs/port
cd ..


# get wine include files
cd include
git checkout wine_staging/master -- ../include/wine
cd ..


# get vulkan dlls
cd dlls
git checkout wine_staging/master -- ../dlls/vulkan
git checkout wine_staging/master -- ../dlls/vulkan-1
cd ..
