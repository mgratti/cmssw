## Instructions to set up environment for HNL generation

First Installation
```
cmsrel CMSSW_10_2_3
cd CMSSW_10_2_3/src
cmsenv
git cms-init

curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/BPH-RunIIFall17GS-00087 --retry 2 --create-dirs -o Configuration/GenProduction/python/BPH-RunIIFall17GS-00087-fragment.py
[ -s Configuration/GenProduction/python/BPH-RunIIFall17GS-00087-fragment.py ] || exit $?;

git cms-addpkg GeneratorInterface/EvtGenInterface

scram b

cmsDriver.py Configuration/GenProduction/python/BPH-RunIIFall17GS-00087-fragment.py --fileout file:BPH-RunIIFall17GS-00087.root --mc --eventcontent RAWSIM --datatier GEN-SIM --conditions 93X_mc2017_realistic_v3 --beamspot Realistic25ns13TeVEarly2017Collision --step GEN,SIM --nThreads 2 --geometry DB:Extended --era Run2_2017 --python_filename BPH-RunIIFall17GS-00087_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 21456 || exit $? ;
```

After first installation:
```
cd CMSSW_10_2_3/src
cmsenv
export CMSSW_SEARCH_PATH=$CMSSW_BASE/src/GeneratorInterface/EvtGenInterface/data/:$CMSSW_SEARCH_PATH  # needed to use local evt.pdf file
```

## Cfgs 

BPH-RunIIFall17GS-00087_1_cfg.py  => tau->3mu      with Fall17
BTV-RunIIFall18GS-00035_1_cfg.py  => W+W-          with Fall18 
BPH_start_cfg.py                  => mod tau->3mu  with Fall18 
BPH_mod_cfg.py                    => tentative HNL with Fall18


## Decay files (for reference)

tentative_B_decay_evtgen.DEC     => B+ -> nu  mu+ D0, D0 -> K- pi+
tentative_B_decay_HNL_evtgen.DEC => B+ -> HNL mu+ D0, D0 -> K- pi+

