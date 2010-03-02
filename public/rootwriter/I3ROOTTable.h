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

#ifndef	I3ROOTTABLE_H_INCLUDED
#define I3ROOTTABLE_H_INCLUDED

#include <tableio/internals/I3Table.h>
#include <rootwriter/I3ROOTBranchWrapper.h>

#include <vector>


I3_FORWARD_DECLARATION(I3TableService);
I3_FORWARD_DECLARATION(I3TableRowDescription);
I3_FORWARD_DECLARATION(I3TableRow);

class TBranch;


class I3ROOTTable : public I3Table {
public:
  I3ROOTTable(I3TableService& service, const std::string& name,
	      I3TableRowDescriptionConstPtr description);
  virtual ~I3ROOTTable();
protected:
  virtual void WriteRows(I3TableRowConstPtr row);
  virtual I3Table::AlignmentType GetAlignmentType();

private:
  TTree *tree_;
  bool multirow_;
  std::vector<I3ROOTBranchWrapper> branches_;
  I3ROOTBranchWrapper counter_;

  SET_LOGGER("I3ROOTTable");
};

#endif
