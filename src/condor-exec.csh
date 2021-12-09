#!/bin/tcsh
echo "Starting job on " `date` #Date/time of start of job
echo "Running on: `uname -a`" #Condor job is running on this node
echo "System software: `cat /etc/redhat-release`" #Operating System on that node
source /cvmfs/cms.cern.ch/cmsset_default.csh

# Input section
set input=$1
set output=$2

# Unpack, setup and execute the code
tar -xf env.tgz
rm env.tgz
setenv SCRAM_ARCH slc7_amd64_gcc900
cd qcdGen
source /cvmfs/sft.cern.ch/lcg/views/LCG_100/x86_64-centos7-gcc9-opt/setup.csh
cd src
make clean
make
./qcdGen ${input} ${output}

# Output stage
xrdcp -f ${output} root://cmseos.fnal.gov//store/user/${USER}/pythiaGen/
cd ${_CONDOR_SCRATCH_DIR}
rm -rf env
