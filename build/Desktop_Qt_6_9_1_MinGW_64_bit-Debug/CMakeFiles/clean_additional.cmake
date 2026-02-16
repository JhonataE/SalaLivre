# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SalaLivre_Sprint1_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SalaLivre_Sprint1_autogen.dir\\ParseCache.txt"
  "SalaLivre_Sprint1_autogen"
  "UnitTests\\CMakeFiles\\UnitTests_autogen.dir\\AutogenUsed.txt"
  "UnitTests\\CMakeFiles\\UnitTests_autogen.dir\\ParseCache.txt"
  "UnitTests\\UnitTests_autogen"
  )
endif()
