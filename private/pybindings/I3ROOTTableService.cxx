/**
 * I3ROOTTableService.cxx (pybindings)
 *
 * copyright  (C) 2010
 * The Icecube Collaboration
 *
 * $Id$
 *
 * @version $Revision$
 * @date $LastChangedDate$
 * @author Fabian Kislat <fabian.kislat@desy.de> Last changed by: $LastChangedBy$
 */

#include <rootwriter/I3ROOTTableService.h>

namespace bp = boost::python;


void register_I3ROOTTableService() {
  bp::class_<I3ROOTTableService, 
    boost::shared_ptr<I3ROOTTableService>, bp::bases<I3TableService> >
    ("I3ROOTTableService", bp::init<const std::string>(bp::args("filename")))
    .def(bp::init<const std::string&, int>(bp::args("filename","compression_level")))
    .def(bp::init<const std::string&, int, const std::string&>(bp::args("filename","compression_level","mode")))
    ;
}
