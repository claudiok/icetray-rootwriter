..
.. copyright  (C) 2010
.. The Icecube Collaboration
..
.. $Id$
..
.. @version $Revision: -1 $
.. @date $LastChangedDate: $
.. @author Fabian Kislat <fabian.kislat@desy.de>, $LastChangedBy: $

.. ctype:: I3ROOTTableService

    encapsulates a root file and provides methods of writing data to that ROOT
    file in the tableio framework.

    .. cfunction:: I3ROOTTableService(const std::string &filename, const std::string &master = "MasterTree", int compress = 1, const std::string &mode = "RECREATE")

        creates a new I3ROOTTableService with the given parameters:
	
	* ``filename`` - Name of the ROOT files to be written;
	* ``master`` -  Name of the master tree in the ROOT file. All other trees are friends of this tree.
   	* ``compress`` - Compression parameter. See the documentation of ``TFile`` in the ROOT documentation for the
	  meaning of this number. The default should be okay for most people.
	* ``mode`` - The file mode of the ROOT file. See the documentation of ``TFile`` in the ROOT documentation.
	  Only change this if you really know what you are doing!

    All other functions are private/protected and do not need to be accessed by the user.
