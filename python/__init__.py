from icecube.load_pybindings import load_pybindings
from icecube import icetray, tableio

load_pybindings(__name__, __path__)

@icetray.traysegment(parent=tableio.I3TableWriter, removeopts=('TableService',))
def I3ROOTWriter(tray, name, Output=None, **kwargs):
	"""Tabulate data to a ROOT file.

	:param Output: Path to output file
	"""
	tabler = I3ROOTTableService(Output)
	tray.AddModule(tableio.I3TableWriter, name, TableService=tabler,
	    **kwargs)

# clean the local dictionary
del icetray
