//#include "OnlyForTest.h"

#include <I3Test.h>
#include <tableio/I3TableRowDescription.h>
#include <rootwriter/I3ROOTTableService.h>
#include <rootwriter/I3ROOTTable.h>
#include "rootwriter/I3ROOTBranchWrapperEnum.h"

#include <boost/shared_ptr.hpp>

#include "TTree.h"

TEST_GROUP(I3ROOTBranchWrapperEnum_Test);

TEST(I3ROOTBranchWrapperEnum_Constructors_Test)
{
  TTree *tree=  new TTree("tree","TTree for testin Coverage");
  I3Datatype i3intdatatype = I3DatatypeFromNativeType<int>();
  const std::string branchname= "branchname_tree";
  const std::string docstring= "docstring_tree";

  I3ROOTBranchWrapperEnumPtr ctor_wrappeenur
    (new I3ROOTBranchWrapperEnum(tree, i3intdatatype, branchname, 
				 docstring, 1, sizeof(int))); 
  
  I3ROOTBranchWrapperEnumPtr ctor_wrappeenur_cp
    (new I3ROOTBranchWrapperEnum(*ctor_wrappeenur));
}

TEST(I3ROOTBranchWrapperEnum_Fill_Test)
{
  const char *filename = "rootwriter_test_single_signed_char.root";
  const char *treename = "tTree";
  const char *fieldname = "char_field";
  const int8_t value = 52;
  
  I3TableServicePtr writer_service = 
    I3TableServicePtr(new I3ROOTTableService(filename));
  I3TableRowDescriptionPtr desc = 
    I3TableRowDescriptionPtr(new I3TableRowDescription());

  desc->AddField<int8_t>(fieldname, "test-units", "A single byte value");
  I3TablePtr table = writer_service->GetTable(treename, desc);
  const I3TableRowConstPtr rows= table->CreateRow(1);
  
  I3ROOTBranchWrapperEnumPtr branchwrapper(new I3ROOTBranchWrapperEnum());
  branchwrapper->Fill(rows);
}

TEST(I3ROOTBranchWrapperEnum_selectFillImp_Test)
{
  I3Datatype i3intdatatype = I3DatatypeFromNativeType<int>();
  ENSURE_EQUAL(i3intdatatype.is_signed, true, 
	       "ENSURE_EQUAL is_signed");
  ENSURE_EQUAL(i3intdatatype.size, sizeof(int), 
	       "ENSURE_EQUAL size is okay");
  ENSURE_EQUAL((int)i3intdatatype.kind, (int)I3Datatype::Int, 
	       "ENSURE_EQUAL Int is recognized");

  //boost::shared_ptr<OnlyForTest> onlyfortest (new OnlyForTest());
  //onlyfortest->GetForTestselectFillImp(i3intdatatype);
  
}


