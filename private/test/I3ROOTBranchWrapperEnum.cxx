#include <I3Test.h>

#include <tableio/I3TableRowDescription.h>
#include <tableio/I3TableRow.h>
#include <rootwriter/I3ROOTTableService.h>
#include <rootwriter/I3ROOTTable.h>
#include "rootwriter/I3ROOTBranchWrapperEnum.h"
#include "OnlyForTest.h"

#include <dataclasses/physics/I3EventHeader.h>

#include <boost/shared_ptr.hpp>
#include "boost/make_shared.hpp"

#include "TTree.h"

TEST_GROUP(I3ROOTBranchWrapperEnum_Test);

TEST(I3ROOTBranchWrapperEnum_Constructors_Test)
{
  TTree *tree=  new TTree("tree","TTree for testin Coverage");
  I3Datatype i3intdatatype = I3DatatypeFromNativeType<int>();
  const std::string branchname= "branchname_tree";
  const std::string docstring= "docstring_tree";

  size_t arraylength=3;//any value
  /**
     index needs to be 0 due to somecontainer.at(index) in 
     I3TableRow::GetPointerToField(size_t index, size_t row) 
  */
  unsigned int index=0;
  I3ROOTBranchWrapperEnumPtr ctor_wrappeenur
    (new I3ROOTBranchWrapperEnum(tree, i3intdatatype, branchname, 
				 docstring, index, arraylength)); 
  
  I3ROOTBranchWrapperEnumPtr ctor_wrappeenur_cp(ctor_wrappeenur);

  ENSURE(ctor_wrappeenur==ctor_wrappeenur_cp,
	 "copy for ctor I3ROOTBranchWrapperEnum does not match");
}

TEST(I3ROOTBranchWrapperEnum_Fill_Test)
{
  /**  
       For creating an I3TableRowPtr
  */
  const char *filename = "rootwriter_test_single_signed_char.root";
  const char *treename = "tTree";
  const char *fieldname = "char_array_field";
  const int8_t value = 52;
  
  I3TableRowDescriptionPtr desc(new I3TableRowDescription());
  desc->AddField<int8_t>(fieldname, "test-units", "A single byte value");
  
  I3TableServicePtr writer_service(new I3ROOTTableService(filename));
  I3TablePtr table = writer_service->GetTable(treename, desc);
  I3TableRowPtr rows = table->CreateRow(1);

  I3EventHeaderConstPtr fake_header(new I3EventHeader());
  rows->Set<int8_t>(fieldname, value);
  /**  
       For creating an instance of I3ROOTBranchWrapperEnum
  */
  TTree *tree=  new TTree("tree","TTree for testin Coverage");
  I3Datatype i3intdatatype = I3DatatypeFromNativeType<int>();
  const std::string branchname= "branchname_tree";
  const std::string docstring= "docstring_tree";

  size_t arraylength=3;
  unsigned int index=0;
  I3ROOTBranchWrapperEnumPtr ctor_wrappeenur
    (new I3ROOTBranchWrapperEnum(tree, i3intdatatype, 
				 branchname, 
				 docstring, 
				 index, arraylength));
                                                      
  /**
     The function that we need to test: 
  */
  ctor_wrappeenur->Fill(rows);
  /**
     clean up:
  */
  writer_service->Finish();
}

TEST(I3ROOTBranchWrapperEnum_FillImp)
{
  TTree *tree=  new TTree("tree","TTree for testin Coverage");
  I3Datatype i3intdatatype = I3DatatypeFromNativeType<int8_t>();
  const std::string branchname= "branchname_tree";
  const std::string docstring= "docstring_tree";
  /**
    index needs to be 0 due to somecontainer.at(index) in 
    I3TableRow::GetPointerToField(size_t index, size_t row) 
    arraylength we give any value
  */
  unsigned int index=0;
  size_t arraylength=3;
  I3ROOTBranchWrapperEnumPtr ctor_wrappeenur
    (new I3ROOTBranchWrapperEnum(tree, i3intdatatype, 
				 branchname, 
				 docstring, 
				 index, arraylength));
                                                      
  /**
     The function that we need to test needs I3TableRowConstPtr
     Then, for creating a I3TableRowPtr
  */
  const char *filename = "rootwriter_test_single_signed_char.root";
  const char *treename = "tTree";
  const char *fieldname = "char_array_field_int8_t";
  
  I3TableRowDescriptionPtr desc(new I3TableRowDescription());
  desc->AddField<int8_t>(fieldname, "test-units", "A single byte value");
  
  I3TableServicePtr writer_service(new I3ROOTTableService(filename));
  I3TablePtr table = writer_service->GetTable(treename, desc);
  I3TableRowPtr rows = table->CreateRow(1);

  const int8_t value = 52;
  I3EventHeaderConstPtr fake_header(new I3EventHeader());
  rows->Set<int8_t>(fieldname, value);

  I3TableRowConstPtr constrows= 
    boost::const_pointer_cast<const I3TableRow>(rows);
  /**
     The function that we need to test is I3ROOTBranchWrapperEnum::FillImp(constrows)
     nevertheless, this is private, then we create a friend class 
     OnlyForTest (placed in private/test/OnlyForTest.h) just for testing
  */
  boost::shared_ptr<OnlyForTest> onlyfortest(new OnlyForTest(ctor_wrappeenur));
  onlyfortest->ForTestFillImp<int8_t>(constrows);
 
  writer_service->Finish();
}


TEST(I3ROOTBranchWrapperEnum_selectFillImp_Test)
{
  TTree *tree=  new TTree("tree","TTree for testin Coverage");
  const std::string branchname= "branchname_tree";
  const std::string docstring= "docstring_tree";
  /**
     Below, index needs to be 0 due to somecontainer.at(index) in
     I3TableRow::GetPointerToField(size_t index, size_t row)  
  */
  unsigned int index=0;
  size_t arraylength=3;

  /**
     Test for int8_t type::
  */

  I3Datatype i3intdatatype = I3DatatypeFromNativeType<int8_t>();
  I3ROOTBranchWrapperEnumPtr ctor_wrappeenur
    (new I3ROOTBranchWrapperEnum(tree, i3intdatatype, 
				 branchname, 
				 docstring, 
				 index, arraylength));
                                                      
  boost::shared_ptr<OnlyForTest> onlyfortest(new OnlyForTest(ctor_wrappeenur));
  I3ROOTBranchWrapperEnum::FillFn fillfn= 
    onlyfortest->GetForTestselectFillImp(i3intdatatype);
   
  ENSURE_EQUAL(i3intdatatype.size,sizeof(int8_t), 
	       "I3Datatype has wrong size");
  
  ENSURE_EQUAL(i3intdatatype.is_signed, true, 
	       "I3Datatype is not signed");
  /**
     We need to use I3TableRowConstPtr for 
     I3ROOTBranchWrapperEnum::FillImp(I3TableRowConstPtr), 
     then we create the intance of I3TableRowConstPtr
  */
  const char *filename = "rootwriter_test_single_signed_char.root";
  const char *treename = "tTree";
  const char *fieldname = "char_array_field";
  const int8_t value = 52;
  
  I3TableRowDescriptionPtr desc(new I3TableRowDescription());
  desc->AddField<int8_t>(fieldname, "test-units", "A single byte value");
  
  I3TableServicePtr writer_service(new I3ROOTTableService(filename));
  I3TablePtr table = writer_service->GetTable(treename, desc);
  I3TableRowPtr rows = table->CreateRow(1);
 
  I3EventHeaderConstPtr fake_header(new I3EventHeader());
  rows->Set<int8_t>(fieldname, value);
 
  I3TableRowConstPtr constrows= 
    boost::const_pointer_cast<const I3TableRow>(rows);
 
  boost::shared_ptr<OnlyForTest> onlyfortest_cp(onlyfortest);

  ENSURE(onlyfortest!=NULL,
	 "The Constructor is Null");
  ENSURE_EQUAL(onlyfortest,onlyfortest_cp,
	       "Copy of OnlyForParticle does not match");
  ENSURE_EQUAL(onlyfortest->GetForTestselectFillImp(i3intdatatype),
	       onlyfortest_cp->GetForTestselectFillImp(i3intdatatype),
	       "Copy of OnlyForParticle::GetForTestselectFillImp  does not match");
  

  writer_service->Finish();
}



