#!/bin/env python

import sys

from I3Tray import *

from icecube.tableio import I3TableWriter
from icecube.rootwriter import I3ROOTTableService
from icecube import dataclasses, linefit

from icecube import dataio 

outfile = sys.argv[1]
infiles = sys.argv[2:]

tray = I3Tray()

# Read .i3 file
tray.AddModule("I3Reader", "reader",
               FileNameList = infiles
               )

# Open output file
table_service = I3ROOTTableService(outfile)

# Book data
tray.AddModule(I3TableWriter, "writer",
               TableService = table_service,
               Keys = [ "LineFit", "LineFitParams" ]
               )

tray.AddModule("TrashCan", "trash")

tray.Execute()
tray.Finish()

