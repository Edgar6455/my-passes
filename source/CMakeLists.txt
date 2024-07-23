set(MY_PLUGINS
    1_Functions
    2_BasicBlocksCount
    3_InstructionsInBB
    4_Opcodes
    5_FunctionCallsCount
    6_AddToSub
    )

set(1_Functions_SOURCES
    1_Functions.cpp)
set(2_BasicBlocksCount_SOURCES
    2_BasicBlocksCount.cpp)
set(3_InstructionsInBB_SOURCES
    3_InstructionsInBB.cpp)
set(4_Opcodes_SOURCES
    4_Opcodes.cpp)
set(5_FunctionCallsCount_SOURCES
    5_FunctionCallsCount.cpp)
set(6_AddToSub_SOURCES
    6_AddToSub.cpp)

# Configure the plugin libraries
foreach( plugin ${MY_PLUGINS} )
    # Create a library corresponding to 'plugin'
    add_library(
      ${plugin}
      SHARED
      ${${plugin}_SOURCES}
      )

    # Configure include directories for 'plugin'
    target_include_directories(
      ${plugin}
      PRIVATE
      "${CMAKE_CURRENT_SOURCE_DIR}/../include"
    )

    install(TARGETS ${plugin} LIBRARY DESTINATION "${CMAKE_SOURCE_DIR}/lib")
endforeach()
