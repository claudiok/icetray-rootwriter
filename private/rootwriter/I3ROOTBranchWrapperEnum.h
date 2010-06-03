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

#ifndef ROOTWRITER_I3ROOTBRANCHWRAPPERENUM_H_INCLUDED
#define ROOTWRITER_I3ROOTBRANCHWRAPPERENUM_H_INCLUDED

#include "I3ROOTBranchWrapper.h"
#include <icetray/I3PointerTypedefs.h>

#include <boost/shared_ptr.hpp>
#include <map>
#include <string>


I3_FORWARD_DECLARATION(I3TableRow);

class I3Datatype;
class TBranch;
class TTree;


class I3ROOTBranchWrapperEnum : public I3ROOTBranchWrapper {
public:
  I3ROOTBranchWrapperEnum();
  I3ROOTBranchWrapperEnum(TTree *tree, const I3Datatype &type, const std::string &branchname,
			  const std::string &docstring, unsigned int index, size_t arrayLength = 1,
			  const I3ROOTBranchWrapperConstPtr &counter = I3ROOTBranchWrapperConstPtr());
  I3ROOTBranchWrapperEnum(const I3ROOTBranchWrapperEnum &rhs);
  ~I3ROOTBranchWrapperEnum();

  void Fill(const I3TableRowConstPtr &data);

private:
  boost::shared_ptr<std::string> data_;
  std::map<long, std::string> mapping_;
};

I3_POINTER_TYPEDEFS(I3ROOTBranchWrapperEnum);

#endif // ROOTWRITER_I3ROOTBRANCHWRAPPER_H_INCLUDED