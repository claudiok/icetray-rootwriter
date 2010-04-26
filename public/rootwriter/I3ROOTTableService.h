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

#include <icetray/I3PointerTypedefs.h>
#include <tableio/internals/I3TableService.h>

#include <boost/shared_ptr.hpp>
#include <vector>

class TFile;

I3_FORWARD_DECLARATION(I3ROOTTable);


class I3ROOTTableService : public I3TableService {
public:
  I3ROOTTableService(const std::string &filename,
		     const std::string &master = "MasterTree", int compress = 1, 
		     const std::string &mode = "RECREATE");
  virtual ~I3ROOTTableService();
  
protected:
  virtual I3TablePtr CreateTable(const std::string &tableName, 
				 I3TableRowDescriptionConstPtr description);
  virtual void CloseFile();
  
private:
  boost::shared_ptr<TFile> file_;
  std::vector< I3ROOTTablePtr > tables_;
  bool open_;

  I3ROOTTablePtr mastertable_;
  
  SET_LOGGER("I3ROOTTableService");
};


#endif // ROOTWRITER_I3ROOTTABLESERVICE_H_INCLUDED
