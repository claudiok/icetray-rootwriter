..
.. copyright  (C) 2010
.. The Icecube Collaboration
..
.. $Id$
..
.. @version $Revision: -1 $
.. @date $LastChangedDate: $
.. @author Fabian Kislat <fabian.kislat@desy.de>, $LastChangedBy: $

.. highlight:: pycon

rootwriter
=================

A tableio backend for writing root files

Usage
^^^^^^^^
This page summarizes the usage of the rootwriter tableio backend. For more
details on tableio, please read :ref:`the tableio documentation <tableio-main>`.

The rootwriter project supplies a tableio :class:`I3TableService` and an :class:`I3Table`
implementation to export data from IceTray to root trees. Tableio converters
are used to convert the objects in the :class:`I3Frame`. In order to use the 
rootwriter backend, construct an :class:`I3ROOTTableService` object in the steering
file::

    rootout = I3ROOTTableService(outputfilename)

The first parameter of the constructor is the filename of the output file.
For a documentation of the other (optional) parameters, read the 
documentation of :class:`I3ROOTTableService`. Once created you can pass this
object as the ``tableservice`` parameter to an :class:`I3TableWriter`::

    tray.AddModule(I3TableWriter, "recowriter",
                   tableservice = rootout,
		   ...
		   )

The ROOT files created by rootwriter contain a ``TTree`` for each
frame object. The trees themselves have an entirely flat structure. Each
tree contains at least three branches:

* ``UInt_t Run`` - the run number,
* ``UInt_t Event`` - the event number,
* ``Bool_t exists`` - set to false, if the corresponding object did not exist
  in the frame.

In order to align the trees every tree contains one line for each event. 
Therefore it is important to always check the value of ``exists``. 
If the object stored in the tree was an array like structure (like e.g. an
:class:`I3RecoPulseSeriesMap`) an additional branch is added to the tree

* ``ULong64_t Count_<tree_name>`` - the number of items in the current event.

.. highlight:: c++
All further branches are then arrays of the given length. Every branch 
has the description stored in the branch title. You can access it via ::

    tree->GetBranch("branch")->GetTitle();

These descriptions are provided by the individual converters and are the
same as those stored in the hdf header.

All trees are friends of a master tree, which by default is called 
``MasterTree``. Using this master tree, individual branches can be
refered to as branches of this master tree, under the name 
``tree_name.branch_name``.
