for i in `seq 1 5`;
do
  condor_submit condor_CP${i}.jdl
#  condor_submit condor_CP${i}_up.jdl
#  condor_submit condor_CP${i}_down.jdl
done
