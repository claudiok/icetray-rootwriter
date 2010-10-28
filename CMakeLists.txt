#
# $Id$
#

i3_project(rootwriter 
  DOCS_DIR resources/docs
)

if(USE_ROOT)

  i3_add_library(roottable
    private/libroottable/TTableDescription.cxx

    USE_TOOLS boost root
    
    ROOTCINT public/rootwriter/TTableDescription.h

    WITHOUT_I3_HEADERS
    )

  set_target_properties(roottable PROPERTIES
    LINK_FLAGS "-Wl,--as-needed"
    )

  i3_add_library(rootwriter
    private/rootwriter/*.cxx
  
    USE_TOOLS log4cplus boost root python
    # add all the projects needed, in particular those needed by the converters
    USE_PROJECTS icetray dataclasses tableio
    )

  add_dependencies(rootwriter roottable)
  target_link_libraries(rootwriter roottable)

  add_subdirectory(private/pybindings)

  i3_test_executable(test 
    private/test/*.cxx
    USE_TOOLS root
    USE_PROJECTS dataclasses icetray phys-services rootwriter tableio)


else(USE_ROOT)

  message(STATUS "ROOT has been disabled in your configuration.")
  message(STATUS "Skipping build of ${PROJECT_NAME}")

endif(USE_ROOT)

