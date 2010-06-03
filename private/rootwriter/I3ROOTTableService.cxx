/*
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
#include <tableio/I3TableRowDescription.h>

#include <TFile.h>
#include <TTree.h>

#include <boost/foreach.hpp>


I3ROOTTableService::I3ROOTTableService(const std::string &filename, const std::string &master,
				       int compress, const std::string &mode)
  : I3TableService(), file_(new TFile(filename.c_str(), mode.c_str(), "", compress)),
    tables_()
{
  if (!file_->IsOpen())
    log_fatal("Cannot open file %s", filename.c_str());
  mastertable_ = dynamic_pointer_cast<I3ROOTTable>(GetTable(master, I3TableRowDescriptionPtr(new I3TableRowDescription)));
  open_ = true;
}

I3ROOTTableService::~I3ROOTTableService() {}
  
I3TablePtr I3ROOTTableService::CreateTable(const std::string &tableName, 
					   I3TableRowDescriptionConstPtr description)
{
  I3ROOTTablePtr table(new I3ROOTTable(*this, tableName, description));
  if (mastertable_) {  // will not do this for the master table
    tables_.push_back(table);
  }
  return table;
}

void I3ROOTTableService::CloseFile()
{
  if (open_) {
    // log_warn("Closing '%s'. Did I want to do some sanity checks first?",
         // file_->GetName());
    file_->cd();
    mastertable_->Align();
    BOOST_FOREACH(I3ROOTTablePtr table, tables_) {
      mastertable_->tree_->AddFriend(table->tree_);
      table->Write();
    }
    mastertable_->Write();
    file_->Close();
    open_ = false;
  }
}
