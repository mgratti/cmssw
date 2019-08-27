from __future__ import absolute_import
import FWCore.ParameterSet.Config as cms

from .particleFlowCaloResolution_cfi import _timeResolutionECALBarrel, _timeResolutionECALEndcap

#### PF CLUSTER ECAL ####

#cleaning
_spikeAndDoubleSpikeCleaner_ECAL = cms.PSet(
    algoName = cms.string("SpikeAndDoubleSpikeCleaner"),    
    cleaningByDetector = cms.VPSet(
    cms.PSet( detector = cms.string("ECAL_BARREL"),
              #single spike
              singleSpikeThresh = cms.double(4.0),
              minS4S1_a = cms.double(0.04), #constant term
              minS4S1_b = cms.double(-0.024), #log pt scaling
              #double spike
              doubleSpikeThresh = cms.double(10.0),
              doubleSpikeS6S2 = cms.double(0.04),
              energyThresholdModifier = cms.double(2.0), ## aka "tighterE"
              fractionThresholdModifier = cms.double(3.0) ## aka "tighterF"
              ),
    cms.PSet( detector = cms.string("ECAL_ENDCAP"),
              #single spike
              singleSpikeThresh = cms.double(15.0),
              minS4S1_a = cms.double(0.02), #constant term
              minS4S1_b = cms.double(-0.0125), #log pt scaling
              #double spike
              doubleSpikeThresh = cms.double(1e9),
              doubleSpikeS6S2 = cms.double(-1.0),
              energyThresholdModifier = cms.double(2.0), ## aka "tighterE"
              fractionThresholdModifier = cms.double(3.0) ## aka "tighterF"
              )
    )
)

_depths_EB = cms.vint32(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170)
_seedingThresholdsE_EB = cms.vdouble(0.1014, 0.0995, 0.1009, 0.1006, 0.1013, 0.1009, 0.1007, 0.1016, 0.1011, 0.1003, 0.1, 0.0993, 0.0991, 0.0976, 0.0986, 0.099, 0.0968, 0.0971, 0.0964, 0.0957, 0.0939, 0.0931, 0.0927, 0.092, 0.0921, 0.0895, 0.0889, 0.0893, 0.088, 0.088, 0.0866, 0.0857, 0.0858, 0.085, 0.0849, 0.0849, 0.0836, 0.0843, 0.0838, 0.0842, 0.0831, 0.0822, 0.0826, 0.0819, 0.0824, 0.0809, 0.08, 0.0804, 0.0789, 0.0797, 0.0795, 0.0787, 0.0789, 0.0785, 0.0784, 0.0782, 0.0777, 0.0777, 0.0771, 0.0776, 0.0771, 0.0768, 0.0769, 0.0761, 0.0771, 0.0758, 0.0754, 0.076, 0.075, 0.076, 0.0744, 0.0751, 0.0748, 0.0746, 0.0751, 0.0743, 0.074, 0.0735, 0.0737, 0.0749, 0.0738, 0.0733, 0.0742, 0.0739, 0.0745, 0.0745, 0.0739, 0.0742, 0.0733, 0.0738, 0.0749, 0.0737, 0.0735, 0.074, 0.0743, 0.0751, 0.0746, 0.0748, 0.0751, 0.0744, 0.076, 0.075, 0.076, 0.0754, 0.0758, 0.0771, 0.0761, 0.0769, 0.0768, 0.0771, 0.0776, 0.0771, 0.0777, 0.0777, 0.0782, 0.0784, 0.0785, 0.0789, 0.0787, 0.0795, 0.0797, 0.0789, 0.0804, 0.08, 0.0809, 0.0824, 0.0819, 0.0826, 0.0822, 0.0831, 0.0842, 0.0838, 0.0843, 0.0836, 0.0849, 0.0849, 0.085, 0.0858, 0.0857, 0.0866, 0.088, 0.088, 0.0893, 0.0889, 0.0895, 0.0921, 0.092, 0.0927, 0.0931, 0.0939, 0.0957, 0.0964, 0.0971, 0.0968, 0.099, 0.0986, 0.0976, 0.0991, 0.0993, 0.1, 0.1003, 0.1011, 0.1016, 0.1007, 0.1009, 0.1013, 0.1006, 0.1009, 0.0995, 0.1014)
_seedingThresholdsPt_EB = cms.vdouble(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

#_depths_EE = cms.vint32()

#_seedingThresholdsE_EE = cms.vdouble()

#_seedingThresholdsPt_EE = cms.vdouble()

#seeding
_localMaxSeeds_ECAL = cms.PSet(
    algoName = cms.string("LocalMaximumSeedFinder"),
    thresholdsByDetector = cms.VPSet(
    cms.PSet( detector = cms.string("ECAL_ENDCAP"),
              seedingThreshold = cms.double(0.60),
              seedingThresholdPt = cms.double(0.15)
#              depths = _depths_EE
#              seedingThreshold = _seedingThresholdsE_EE
#              seedingThresholdPt = _seedingThresholdsPt_EE
              ),
    cms.PSet( detector = cms.string("ECAL_BARREL"),
              #seedingThreshold = cms.double(0.23),
              #seedingThresholdPt = cms.double(0.0)
              depths = _depths_EB,
              seedingThreshold = _seedingThresholdsE_EB,
              seedingThresholdPt = _seedingThresholdsPt_EB,
              )
    ),
    nNeighbours = cms.int32(8)
)

# topo clusterizer
_topoClusterizer_ECAL = cms.PSet(
    algoName = cms.string("Basic2DGenericTopoClusterizer"),
    thresholdsByDetector = cms.VPSet(
    cms.PSet( detector = cms.string("ECAL_BARREL"),
              gatheringThreshold = cms.double(0.08),
              gatheringThresholdPt = cms.double(0.0)
              ),
    cms.PSet( detector = cms.string("ECAL_ENDCAP"),
              gatheringThreshold = cms.double(0.3),
              gatheringThresholdPt = cms.double(0.0)
              )
    ),
    useCornerCells = cms.bool(True)
)

#position calculations
_positionCalcECAL_all_nodepth = cms.PSet(
    algoName = cms.string("Basic2DGenericPFlowPositionCalc"),
    ##
    minFractionInCalc = cms.double(1e-9),
    posCalcNCrystals = cms.int32(-1),
    logWeightDenominator = cms.double(0.08), # same as gathering threshold
    minAllowedNormalization = cms.double(1e-9),
    timeResolutionCalcBarrel = _timeResolutionECALBarrel,
    timeResolutionCalcEndcap = _timeResolutionECALEndcap,
)
_positionCalcECAL_3x3_nodepth = _positionCalcECAL_all_nodepth.clone(
    posCalcNCrystals = cms.int32(9)
)
_positionCalcECAL_all_withdepth = cms.PSet(
    algoName = cms.string("ECAL2DPositionCalcWithDepthCorr"),
    ##
    minFractionInCalc = cms.double(0.0),
    minAllowedNormalization = cms.double(0.0),
    T0_EB = cms.double(7.4),
    T0_EE = cms.double(3.1),
    T0_ES = cms.double(1.2),
    W0 = cms.double(4.2),
    X0 = cms.double(0.89)
)

# pf clustering
_pfClusterizer_ECAL = cms.PSet(
    algoName = cms.string("Basic2DGenericPFlowClusterizer"),
    #pf clustering parameters
    minFractionToKeep = cms.double(1e-7),
    positionCalc = _positionCalcECAL_3x3_nodepth,
    allCellsPositionCalc = _positionCalcECAL_all_nodepth,
    positionCalcForConvergence = _positionCalcECAL_all_withdepth,
    showerSigma = cms.double(1.5),
    stoppingTolerance = cms.double(1e-8),
    maxIterations = cms.uint32(50),
    excludeOtherSeeds = cms.bool(True),
    minFracTot = cms.double(1e-20), ## numerical stabilization
    recHitEnergyNorms = cms.VPSet(
    cms.PSet( detector = cms.string("ECAL_BARREL"),
              recHitEnergyNorm = cms.double(0.08)
              ),
    cms.PSet( detector = cms.string("ECAL_ENDCAP"),
              recHitEnergyNorm = cms.double(0.3)
              )
    )
)

particleFlowClusterECALUncorrected = cms.EDProducer(
    "PFClusterProducer",
    recHitsSource = cms.InputTag("particleFlowRecHitECAL"),
    recHitCleaners = cms.VPSet(),
    seedFinder = _localMaxSeeds_ECAL,
    initialClusteringStep = _topoClusterizer_ECAL,
    pfClusterBuilder = _pfClusterizer_ECAL,
    positionReCalc = _positionCalcECAL_all_withdepth,
    energyCorrector = cms.PSet()
    )
