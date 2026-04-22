# Copyright Contributors to the OpenImageIO project.
# SPDX-License-Identifier: Apache-2.0
# https://github.com/Academ SoftwareFoundation/OpenImageIO

set_cache (Ktx_BUILD_VERSION v4.4.2 "Ktx version for local builds")
set (Ktx_GIT_REPOSITORY "https://github.com/KhronosGroup/KTX-Software.git")
set (Ktx_GIT_TAG "${Ktx_BUILD_VERSION}")
set (Ktx_GIT_COMMIT "4d6fc70eaf62ad0558e63e8d97eb9766118327a6")
set_cache (Ktx_BUILD_SHARED_LIBS OFF #${LOCAL_BUILD_SHARED_LIBS_DEFAULT}
           DOC "Should a local Ktx build, if necessary, build shared libraries" ADVANCED)

string (MAKE_C_IDENTIFIER ${Ktx_BUILD_VERSION} Ktx_VERSION_IDENT)

# for detailed build instructions, see:
#   https://github.com/KhronosGroup/KTX-Software/blob/main/BUILDING.md
# KTX-Software not only provides Ktx but also a set of cli tools and load
# test applications that we do not need.
build_dependency_with_cmake(Ktx
    VERSION         ${Ktx_BUILD_VERSION}
    GIT_REPOSITORY  ${Ktx_GIT_REPOSITORY}
    GIT_TAG         ${Ktx_GIT_TAG}
    GIT_COMMIT      ${Ktx_GIT_COMMIT}
    SOURCE_SUBDIR   lib  # To only build Ktx, cmake has to point to: KTX-Software/lib
    CMAKE_ARGS
        -D BUILD_SHARED_LIBS=${Ktx_BUILD_SHARED_LIBS}
        -D CMAKE_INSTALL_LIBDIR=lib
        -D CMAKE_POSITION_INDEPENDENT_CODE=1
    )
# Set some things up that we'll need for a subsequent find_package to work
set (Ktx_ROOT ${Ktx_LOCAL_INSTALL_DIR})

# Signal to caller that we need to find again at the installed location
set (Ktx_REFIND TRUE)
set (Ktx_REFIND_ARGS CONFIG)

if (Ktx_BUILD_SHARED_LIBS)
    install_local_dependency_libs (Ktx Ktx)
endif ()
