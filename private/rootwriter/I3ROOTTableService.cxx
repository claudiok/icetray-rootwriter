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

#include <TFile.h>

#include <boost/foreach.hpp>

#include <iostream>
using namespace std;
#define DEBUG_ENTER() cout << "Entering " << __PRETTY_FUNCTION__ << endl
#define DEBUG_LEAVE() cout << "Leaving " << __PRETTY_FUNCTION__ << endl
#define DEBUG_VALUE(expr) cout << #expr << " = " << expr << endl


I3ROOTTableService::I3ROOTTableService(const std::string &filename, int compress,
				       const std::string &mode)
  : I3TableService(), file_(new TFile(filename.c_str(), mode.c_str(), "", compress)),
    tables_()
{
  DEBUG_ENTER();
  if (!file_->IsOpen())
    log_fatal("Cannot open file %s", filename.c_str());
  DEBUG_LEAVE();
}

I3ROOTTableService::~I3ROOTTableService() { DEBUG_ENTER(); DEBUG_LEAVE(); }
  
I3TablePtr I3ROOTTableService::CreateTable(const std::string &tableName, 
					   I3TableRowDescriptionConstPtr description)
{
  DEBUG_ENTER();
  I3ROOTTablePtr table(new I3ROOTTable(*this, tableName, description));
  tables_.push_back(table);
  DEBUG_LEAVE();
  return table;
}

void I3ROOTTableService::CloseFile()
{
  DEBUG_ENTER();
  log_warn("Closing '%s'. Did I want to do some sanity checks first?",
	   file_->GetName());
  file_->cd();
  BOOST_FOREACH(I3ROOTTablePtr table, tables_) {
    table->Write();
  }
  file_->Close();
  DEBUG_LEAVE();
}
