# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2019-2025, The OpenROAD Authors

include("openroad")

# https://github.com/The-OpenROAD-Project/OpenROAD/issues/1186
find_package(LEMON NAMES LEMON lemon REQUIRED)

add_library(cts_lib
    Clock_new.cpp
    TreeBuilder_new.cpp
    HTreeBuilder_new.cpp
    SinkClustering_new.cpp
    TechChar_new.cpp
    TritonCTS_new.cpp
    Clustering_new.cpp
    LatencyBalancer_new.cpp
    CtsOptions.cpp
)

swig_lib(NAME      cts
         NAMESPACE cts
         I_FILE    TritonCTS.i
         SCRIPTS   TritonCTS.tcl
)

target_sources(cts
  PRIVATE
    MakeTritoncts.cpp
    CtsGraphics.cpp
)

target_include_directories(cts_lib
  PUBLIC
    ../include
  PRIVATE
    .
  ${LEMON_INCLUDE_DIRS}
 )

target_include_directories(cts
  PUBLIC
    ../include
  PRIVATE
    .
 )

target_link_libraries(cts_lib
  PUBLIC
    rsz_lib
  PRIVATE
    odb
    dbSta_lib
    OpenSTA
    stt_lib
    utl_lib
    Boost::headers
)

target_link_libraries(cts
  PRIVATE
    odb
    cts_lib
    dbSta_lib
    rsz_lib
    OpenSTA
    gui
    Boost::headers
 )

messages(
  TARGET cts
  OUTPUT_DIR ..
)

if (Python3_FOUND AND BUILD_PYTHON)
  swig_lib(NAME          cts_py
           NAMESPACE     cts
           LANGUAGE      python
           I_FILE        TritonCTS-py.i
           SWIG_INCLUDES ${PROJECT_SOURCE_DIR}/../include/cts
                         ${PROJECT_SOURCE_DIR}
           SCRIPTS       ${CMAKE_CURRENT_BINARY_DIR}/cts_py.py
  )

  target_include_directories(cts_py
    PUBLIC
      .
  )
  
  target_link_libraries(cts_py
    PUBLIC
      cts
      dbSta
      OpenSTA
      odb
      rsz
  )

endif()
