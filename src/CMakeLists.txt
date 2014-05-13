#David Coeurjolly <david.coeurjolly@liris.cnrs.fr>
# -----------------------------------------------------------------------------
# Project definition
# -----------------------------------------------------------------------------
PROJECT(ChamferSubQuad)

cmake_minimum_required (VERSION 2.6)

FIND_PACKAGE(DGtal 0.6 REQUIRED)
INCLUDE_DIRECTORIES(${DGTAL_INCLUDE_DIRS})
LINK_DIRECTORIES(${DGTAL_LIBRARY_DIRS})


SET(Boost_USE_STATIC_LIBS   ON)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)
SET(Boost_FOUND FALSE)
FIND_PACKAGE(Boost 1.46.0 REQUIRED COMPONENTS program_options)
if ( Boost_FOUND )
  message(STATUS "Boost and boost_program_options found.")
  include_directories( ${Boost_INCLUDE_DIRS} )
  SET(DGtalToolsLibDependencies ${DGtalToolsLibDependencies}
     ${Boost_LIBRAIRIES}
     ${Boost_PROGRAM_OPTIONS_LIBRARY})
   SET(DGtalLibInc ${Boost_INCLUDE_DIRS})
endif( Boost_FOUND )


INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

SET(DGTAL_TOOLS_SRC
  testLogChamfer
  statDistances
  statVoronoi
  statVoronoil2
  statVoronoi-raster
)


FOREACH(FILE ${DGTAL_TOOLS_SRC})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE}  ${CGAL_LIBRARIES} ${DGtalToolsLibDependencies} ${DGTAL_LIBRARIES})
ENDFOREACH(FILE)
