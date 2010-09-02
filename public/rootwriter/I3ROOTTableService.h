/*
 * Copyright  (C) 2010
 * The Icecube Collaboration
 *
 * $Id$
 *
 * @version $Revision$
 * @date $LastChangedDate$
 * @author Fabian Kislat <fabian.kislat@desy.de> Last changed by: $LastChangedBy$
 */

/**
 * \file I3ROOTTableService.h
 */

#ifndef ROOTWRITER_I3ROOTTABLESERVICE_H_INCLUDED
#define ROOTWRITER_I3ROOTTABLESERVICE_H_INCLUDED

#include <icetray/I3PointerTypedefs.h>
#include <tableio/I3TableService.h>

#include <boost/shared_ptr.hpp>
#include <vector>

I3_FORWARD_DECLARATION(I3ROOTTable);


/**
 * \brief Table service to write root table
 *
 * Encapsulates a root file and provides methods of writing data to that ROOT
 * file in the tableio framework.
 */
class I3ROOTTableService : public I3TableService {
public:
  /**
   * \brief The only constructor
   *
   * \param filename Name of the ROOT files to be written.
   * \param master Name of the master tree in the ROOT file. All other trees are
   *               friends of this tree.
   * \param compress Compression parameter. See the documentation of 
   *                 <code>TFile</code> in the ROOT documentation for the
   *                 meaning of this number. The default should be okay for most
   *                 people.
   * \param mode The file mode of the ROOT file. See the documentation of 
   *             <code>TFile</code> in the ROOT documentation. Only change this
   *             if you really know what you are doing!
   */
  I3ROOTTableService(const std::string &filename,
		     const std::string &master = "MasterTree", int compress = 1, 
		     const std::string &mode = "RECREATE");
  virtual ~I3ROOTTableService();

  /**
   * \brief Set the maximum file size when writing ROOT trees.
   *
   * ROOT will automatically split files when they reach a certain size limit.
   * By default, this size is set to 1TB in rootwriter to essentially keep 
   * ROOT from splitting files. If your file sizes have to be below some
   * limit you can use this function to set the maximum file size. You should, 
   * however, be aware that this feature is <strong>experimental</strong> in
   * rootwriter. Also, the files will not be independent, since rootwriter
   * cannot guarantee that all trees have the same number of entries in every
   * file. Especially, all entries of the master tree will be in the last
   * file.
   * \param maxSize The maximum file size in MiB.
   */
  static void setMaxTreeSize(long long int maxSize);
  
protected:
  /**
   * \brief Creates a ROOT tree with the given name and description.
   *
   * Used by tableio.
   */
  virtual I3TablePtr CreateTable(const std::string &tableName, 
				 I3TableRowDescriptionConstPtr description);
  /**
   * \brief Close the ROOT file.
   */
  virtual void CloseFile();
  
private:
  std::vector< I3ROOTTablePtr > tables_;
  bool open_;

  I3ROOTTablePtr mastertable_;
  
  SET_LOGGER("I3ROOTTableService");
};


#endif // ROOTWRITER_I3ROOTTABLESERVICE_H_INCLUDED
