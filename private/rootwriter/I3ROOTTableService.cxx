/**
 * copyright  (C) 2010
 * The Icecube Collaboration
 *
 * $Id$
 *
 * @version $Revision$
 * @date $LastChangedDate$
 * @author Fabian Kislat <fabian.kislat@desy.de> Last changed by: $LastChangedBy$
 */

#include "rootwriter/I3ROOTTableService.h"
#include "rootwriter/I3ROOTTable.h"

I3ROOTTableService::I3ROOTTableService(const std::string &filename, int compress,
				       const std::string &mode)
  : I3TableService(), file_(filename.c_str(), mode.c_str(), "", compress)
{
  if (!file_.IsOpen())
    log_fatal("Cannot open file %s", filename.c_str());

  file_.cd();
}

I3ROOTTableService::~I3ROOTTableService() {}
  
I3TablePtr I3ROOTTableService::CreateTable(const std::string &tableName, 
					   I3TableRowDescriptionConstPtr description)
{
  return I3TablePtr(new I3ROOTTable(*this, tableName, description));
}

void I3ROOTTableService::CloseFile()
{
  log_warn("Closing '%s'. Did I want to do some sanity checks first?",
	   file_.GetName());
  file_.Write();
  file_.Close();
}
