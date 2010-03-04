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

#include "rootwriter/I3ROOTTable.h"
#include "tableio/internals/I3TableRow.h"
#include "tableio/internals/I3TableRowDescription.h"

#include <boost/foreach.hpp>

#include <TTree.h>

#include <iostream>
using namespace std;
#define DEBUG_ENTER() cout << "Entering " << __PRETTY_FUNCTION__ << endl
#define DEBUG_LEAVE() cout << "Leaving " << __PRETTY_FUNCTION__ << endl
#define DEBUG_VALUE(expr) cout << #expr << " = " << expr << endl

/******************************************************************************/

I3ROOTTable::I3ROOTTable(I3TableService& service, const std::string& name,
			 I3TableRowDescriptionConstPtr description)
  : I3Table(service, name, description),
    tree_(new TTree(name.c_str(), name.c_str())), multirow_(false)
{
  DEBUG_ENTER();

  I3ROOTBranchWrapper *counterwrapper = 0;
  if (description->GetIsMultiRow()) {
    std::string countername = "Count_" + name;
    static const std::string counterdescription =
      "Number of objects in each field";
    counter_ = I3ROOTBranchWrapper(tree_,
				   I3Datatype(I3Datatype::Int,
					      sizeof(uint64_t),
					      false),
				   countername, counterdescription, 0);
    counterwrapper = &counter_;
    multirow_ = true;
  }

  for (size_t field = 0; field < description->GetFieldNames().size(); ++field) {
    std::string branchname = description->GetFieldNames().at(field);
    I3Datatype datatype = description->GetFieldTypes().at(field);
    size_t arrayLength = description->GetFieldArrayLengths().at(field);
    std::string docstring = description->GetFieldDocStrings().at(field);

    branches_.push_back(I3ROOTBranchWrapper(tree_, datatype, branchname, 
					    docstring, field, arrayLength,
					    counterwrapper));
  }

  DEBUG_LEAVE();
}

/******************************************************************************/

I3ROOTTable::~I3ROOTTable() { DEBUG_ENTER(); DEBUG_LEAVE(); }

/******************************************************************************/

void I3ROOTTable::Write()
{
  DEBUG_ENTER();
  tree_->Write();
  DEBUG_LEAVE();
}

/******************************************************************************/

void I3ROOTTable::WriteRows(I3TableRowConstPtr rows) {
  DEBUG_ENTER();
  if (multirow_) {
    counter_.Fill((uint64_t)rows->GetNumberOfRows());
  }

  BOOST_FOREACH(I3ROOTBranchWrapper branch, branches_) {
    branch.Fill(rows);
  }
  DEBUG_LEAVE();
}

/******************************************************************************/

I3Table::AlignmentType I3ROOTTable::GetAlignmentType()
{
  DEBUG_ENTER();
  DEBUG_LEAVE();
  return I3Table::Strict;
}
