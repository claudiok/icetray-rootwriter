from icecube.load_pybindings import load_pybindings
from icecube import icetray, tableio

load_pybindings(__name__, __path__)

@icetray.traysegment
def I3ROOTWriter(tray, name, Output=None, **kwargs):
	"""Tabulate data to a ROOT file.

	Arguments:
		Output: Path to output file
		Keys: Key names of frame objects to tabulate
		Streams: Subevent streams to include
		(See I3TableWriter documentation for others)
	"""
	tabler = I3ROOTTableService(Output)
	tray.AddModule(tableio.I3TableWriter, name, TableService=tabler,
	    **kwargs)

# clean the local dictionary
del icetray,tableio
