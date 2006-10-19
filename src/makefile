include ../makefile.config

SUBDIRS=core graph hash misc poly stack

SRCS= graph/detectAndDeleteLoop.cpp \
	core/deleteContract.cpp \
	core/eliminateTriangle.cpp \
	core/newOps.cpp \
	core/multEdgeSmallGraphElimination.cpp \
	core/contractAfterDelete.cpp \
	core/findDegOne.cpp \
	core/evaluateTutte.cpp \
	graph/operationsOnGraphs.cpp \
	graph/buildGraph.cpp \
	graph/buildGrapha.cpp \
	graph/dataStructureOperations.cpp \
	graph/isoTests.cpp \
	graph/gotMultiple.cpp \
	graph/treeRoutines.cpp \
	graph/removeMultEdge.cpp \
	hash/hashIsoRtns.cpp \
	hash/findInvariant.cpp \
	matchers/sevenpart1.cpp \
	matchers/sevenpart11.cpp \
	matchers/sevenpart12.cpp \
	matchers/sevenpart13.cpp \
	matchers/sevenpart2dra.cpp \
	matchers/sevenpart2drb.cpp \
	matchers/sevenpart2drc.cpp \
	matchers/sevenpart2drd.cpp \
	matchers/sevenpart2dre.cpp \
	matchers/sevenpart2drf.cpp \
	matchers/sevenpart2drg.cpp \
	matchers/sevenpart2drh.cpp \
	matchers/sevenpart2driver.cpp \
	matchers/sevenpart3dr.cpp \
	matchers/sevenpart3dra.cpp \
	matchers/sevenpart3drb.cpp \
	matchers/sevenpart3drb1.cpp \
	matchers/sevenpart4.cpp \
	matchers/sevenpart3drb2.cpp \
	matchers/sevenpart3drb3.cpp \
	matchers/sevenpart3drc.cpp \
	matchers/sevenpart3drc1.cpp \
	matchers/sevenpart3drc2.cpp \
	matchers/sevenpart3drc3.cpp \
	matchers/sevenpart3drd.cpp \
	matchers/sevenpart3drd1.cpp \
	matchers/sevenpart3drd2.cpp \
	matchers/sevenpart3drd3.cpp \
	matchers/sevenpart3dre.cpp \
	matchers/sevenpart3dre1.cpp \
	matchers/sevenpart3dre2.cpp \
	matchers/sevenpart3dre3.cpp \
	matchers/sevenpart3drf.cpp \
	matchers/sevenpart3drf1.cpp \
	matchers/sevenpart3drf2.cpp \
	matchers/sevenpart3drf3.cpp \
	matchers/sevenpart41.cpp \
	matchers/sevenpart42.cpp \
	matchers/sevenpart43.cpp \
	matchers/sevenpart44.cpp \
	matchers/sevenpart45.cpp \
	matchers/sevenpart4a.cpp \
	matchers/sevenpart4b.cpp \
	matchers/evaluateFives.cpp \
	matchers/evaluateFivesA.cpp \
	matchers/evaluateFivesa1.cpp \
	matchers/evaluateFivesb.cpp \
	matchers/evaluateFivesc.cpp \
	matchers/evaluateFivesd.cpp \
	matchers/evaluateFivese.cpp \
	matchers/identifyFives.cpp \
	matchers/identifySixes.cpp \
	matchers/identifySixesA1.cpp \
	matchers/identifySixesA2.cpp \
	matchers/identifySixesB1.cpp \
	matchers/identifySixesB2.cpp \
	matchers/evaluateFours.cpp \
	matchers/evaluateFoursDriver.cpp \
	matchers/sevenPart14.cpp \
	matchers/sevensDriver.cpp \
	matchers/preSevenFindDeg2.cpp \
	matchers/sixOrFewer.cpp \
	matchers/evaluateSmallGraphs.cpp \
	matchers/evaluateThrees.cpp \
	misc/printRoutine.cpp \
	misc/permEdges.cpp \
	misc/setThresholds.cpp \
	misc/recapStats.cpp \
	misc/enterEdgesBuildGraph.cpp \
	poly/multiplyByFactors.cpp \
	poly/multiplyByYPowers.cpp \
	poly/smallMultipleEliminations.cpp \
	stack/stackUtil.cpp \
	startRoutine.cpp \
	tutte.cpp

LDFLAGS += -L../nauty
LIBS = -lnauty

TARGET=testor

include ../makefile.std






