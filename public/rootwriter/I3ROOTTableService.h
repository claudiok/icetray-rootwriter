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

#ifndef ROOTWRITER_I3ROOTTABLESERVICE_H_INCLUDED
#define ROOTWRITER_I3ROOTTABLESERVICE_H_INCLUDED

#include "tableio/internals/I3TableService.h"

#include <TFile.h>


class I3ROOTTableService : public I3TableService {
public:
  I3ROOTTableService(const std::string &filename, int compress = 1,
		     const std::string &mode = "RECREATE");
  virtual ~I3ROOTTableService();
  
protected:
  virtual I3TablePtr CreateTable(const std::string &tableName, 
				 I3TableRowDescriptionConstPtr description);
  virtual void CloseFile();
  
private:
  TFile file_;
  
  SET_LOGGER("I3ROOTTableService");
};


#endif // ROOTWRITER_I3ROOTTABLESERVICE_H_INCLUDED
