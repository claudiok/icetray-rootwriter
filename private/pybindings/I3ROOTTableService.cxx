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

  typedef bp::init<const std::string&,const std::string&,
    int,const std::string&> ctor;
  bp::class_<I3ROOTTableService, 
    boost::shared_ptr<I3ROOTTableService>, bp::bases<I3TableService> >
    ("I3ROOTTableService",ctor((bp::args("filename"), bp::arg("master")="MasterTree",
        bp::arg("compression_level")=1, bp::arg("mode")="RECREATE")))
    ;

  bp::def("setMaxTreeSize", &I3ROOTTableService::setMaxTreeSize, bp::args("maxSize"),
	  "Set the maximum file size in MiB. ROOT will automatically do the splitting.");

}
