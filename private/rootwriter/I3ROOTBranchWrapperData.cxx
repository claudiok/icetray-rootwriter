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

#include "I3ROOTBranchWrapperData.h"

#include <icetray/I3Logging.h>
#include <tableio/I3Datatype.h>
#include <tableio/I3TableRow.h>

#include <TBranch.h>
#include <TTree.h>

#include <boost/lexical_cast.hpp>

#include <cassert>
#include <cctype>
#include <cstring>


char I3DatatypeToROOTType(const I3Datatype &type)
{
  char typechar = '\0';

  switch (type.kind) {
  case I3Datatype::Float:
    if (type.size == 4) {
      typechar = 'F';
    } else if (type.size == 8) {
      typechar = 'D';
    } else {
      log_fatal("Cannot book variables of type '%s' with a size of %lu bits",
		type.description.c_str(), type.size*8);
    }
    break;
  case I3Datatype::Int:
  case I3Datatype::Enum:
    if (type.size == 1) {
      typechar = 'b';
    } else if (type.size == 2) {
      typechar = 's';
    } else if (type.size == 4) {
      typechar = 'i';
    } else if (type.size == 8) {
      typechar = 'l';
    } else {
      log_fatal("Cannot book variables of type %s with a size of %lu bits",
		type.description.c_str(), type.size*8);
    }
    break;
  case I3Datatype::Bool:
    typechar = 'O';
    break;
  default:
    assert(false);
  }

  if (type.is_signed) typechar = toupper(typechar);

  return typechar;
}


I3ROOTBranchWrapperData::I3ROOTBranchWrapperData()
  : I3ROOTBranchWrapper(), datasize_(0), data_(new std::vector<char>)
{}

I3ROOTBranchWrapperData::I3ROOTBranchWrapperData(TTree *tree, const I3Datatype &type,
						 const std::string &branchname,
						 const std::string &docstring,
						 unsigned int index,
						 size_t arrayLength,
						 const I3ROOTBranchWrapperConstPtr &counter)
  : I3ROOTBranchWrapper(tree, index, arrayLength, counter),
    datasize_(type.size), data_(new std::vector<char>),
    rootSignedCharArrayHack_(false)
{
  // generate a type description
  std::string leafdescription = branchname;

  // create the field to hold the data
  data_->resize(datasize_*arrayLength_);

  // generate description of the array length
  if (multirow_) {
    leafdescription.push_back('[');
    leafdescription.append(counter->Branch()->GetName());
    leafdescription.push_back(']');
  }
  if (arrayLength_ > 1) {
    leafdescription.push_back('[');
    leafdescription.append(boost::lexical_cast<std::string>(arrayLength_));
    leafdescription.push_back(']');
  }

  char typechar = I3DatatypeToROOTType(type);

  // when reading the tree ROOT cannot distinguish an array of signed char
  // and a string (char*)
  // workaround: book array of signed shorts
  // a single signed byte and unsigned char arrays should be fine
  if (((arrayLength_ > 1) || multirow_) && (typechar == 'B')) {
    typechar = 'S';
    // this requires some conversion when filling the data (see below)
    // if anyone comes up with a better idea (or fixes ROOT), I'd be VERY happy to hear about it
    rootSignedCharArrayHack_ = true;
  }

  // generate the type of the field
  leafdescription.push_back('/');
  leafdescription.push_back(typechar);

  // finally: create the branch
  TBranch *branch = tree->Branch(branchname.c_str(), &(data_->at(0)),
				  leafdescription.c_str());
  branch->SetTitle(docstring.c_str());
  SetBranch(branch);
}

I3ROOTBranchWrapperData::I3ROOTBranchWrapperData(const I3ROOTBranchWrapperData &rhs)
  : I3ROOTBranchWrapper(rhs), data_(rhs.data_)
{}

I3ROOTBranchWrapperData::~I3ROOTBranchWrapperData() {}

void I3ROOTBranchWrapperData::Fill(const I3TableRowConstPtr &data)
{
  // in the particular case that we are booking an array of signed bytes
  // some conversion needs to be done (see constructor)
  if (rootSignedCharArrayHack_) {
    RootSignedCharArrayHackFillData(data);
    return;
  }

  // make sure we have enough room to store all elements
  if (data->GetNumberOfRows()*datasize_*arrayLength_ > data_->size()) {
    char *olddata = &(data_->at(0));
    data_->resize(data->GetNumberOfRows()*datasize_*arrayLength_);
    if (olddata != &(data_->at(0))) {
      setBranchAddress();
    }
  }

  // copy all elements to our internal data array
  size_t fieldlength = datasize_*arrayLength_;
  for (unsigned int row = 0; row < data->GetNumberOfRows(); ++row) {
    const void *source = data->GetPointerToField(index_, row);
    memcpy(&(data_->at(row*fieldlength)), source, fieldlength);
  }
}

void I3ROOTBranchWrapperData::setBranchAddress()
{
  branch_->SetAddress(&(data_->at(0)));
}

void I3ROOTBranchWrapperData::RootSignedCharArrayHackFillData(const I3TableRowConstPtr &data)
{
  // this function really is just a hack to allow for the explicit
  // conversion of signed char arrays to signed short arrays
  // (see explanation in the constructor)

  static const size_t datasize = sizeof(int16_t);
  
  // make sure we have enough room to store all elements
  if (data->GetNumberOfRows()*datasize*arrayLength_ > data_->size()) {
    char *olddata = &(data_->at(0));
    data_->resize(data->GetNumberOfRows()*datasize*arrayLength_);
    if (olddata != &(data_->at(0))) {
      setBranchAddress();
    }
  }

  // copy all elements to our internal data array
  size_t fieldlength = datasize*arrayLength_;
  for (unsigned int row = 0; row < data->GetNumberOfRows(); ++row) {
    const int8_t *source = data->GetPointer<int8_t>(index_, row);
    for (size_t i = 0; i < arrayLength_; ++i) {
      // really a hack. any better idea?
      int16_t *dest = reinterpret_cast<int16_t*>(&data_->at(row*fieldlength + i*datasize));
      *dest = source[i];
    }
  }
}
