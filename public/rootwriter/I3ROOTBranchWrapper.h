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

#ifndef ROOTWRITER_I3ROOTBRANCHWRAPPER_H_INCLUDED
#define ROOTWRITER_I3ROOTBRANCHWRAPPER_H_INCLUDED

#include <icetray/I3PointerTypedefs.h>

#include <boost/shared_ptr.hpp>
#include <cassert>
#include <vector>


I3_FORWARD_DECLARATION(I3TableRow);

class I3Datatype;
class TBranch;
class TTree;


class I3ROOTBranchWrapper {
public:
  I3ROOTBranchWrapper();
  I3ROOTBranchWrapper(TTree *tree, const I3Datatype &type, const std::string &branchname,
		      const std::string &docstring, unsigned int index,
		      size_t arrayLength = 1, const I3ROOTBranchWrapper *counter = 0);
  I3ROOTBranchWrapper(const I3ROOTBranchWrapper &rhs);
  ~I3ROOTBranchWrapper();

  template <typename T>
  void Fill(const T &data)
  {
    assert(datasize_ == sizeof(T));

    if (data_->size() < datasize_) {
      char *olddata = &(data_->at(0));
      data_->resize(datasize_);
      if (olddata != &(data_->at(0))) {
	setBranchAddress();
      }
    }
    *(reinterpret_cast<T*>(&data_->at(0))) = data;
  }

  void Fill(const I3TableRowConstPtr &data);
  TBranch* Branch() { return branch_; }

private:
  TTree *tree_;
  TBranch *branch_;
  unsigned int index_;
  size_t arrayLength_;
  bool multirow_;
  size_t datasize_;

  boost::shared_ptr< std::vector<char> > data_;
  void setBranchAddress();
};

#endif // ROOTWRITER_I3ROOTBRANCHWRAPPER_H_INCLUDED
