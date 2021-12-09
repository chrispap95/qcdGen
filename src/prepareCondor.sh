#!/bin/sh
USERBASE=`pwd`
rm env.tgz
cd ../../
echo -n "Creating tarball..."
tar --exclude="*.root" --exclude="*.nfs*" --exclude-vcs -zcf env.tgz qcdGen
mv env.tgz qcdGen/src
cd $USERBASE
if [ ! -f env.tgz ]; then
echo -e "\nError: tarball doesn't exist!"
else
echo " Done!"
fi
