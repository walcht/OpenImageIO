# Copyright Contributors to the OpenImageIO project.
# SPDX-License-Identifier: Apache-2.0
# https://github.com/AcademySoftwareFoundation/OpenImageIO

if (ON)
    # use same bcdec.h header file (BCn decompression library) as one in dds.imageio
    add_oiio_plugin (ktxinput.cpp
                     LINK_LIBRARIES ktx
                     INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/src/dds.imageio)
                   # DEFINITIONS "USE_DCMTK=1")
else ()
  message (WARNING "KTX plugin will not be built, no libktx")
endif ()
