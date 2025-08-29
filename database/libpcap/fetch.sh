#!/bin/bash

COMMIT_ID="$1"
REPO_URL="https://github.com/the-tcpdump-group/libpcap.git"

git clone "$REPO_URL" code
if [ $? -ne 0 ]; then
    echo "Failed to clone repository. Exiting."
    exit 1
fi

if [ -n "$COMMIT_ID" ]; then
    cd code
    git checkout "$COMMIT_ID"
    if [ $? -ne 0 ]; then
        echo "Failed to checkout to commit $COMMIT_ID. Exiting."
        exit 1
    fi
    cd ..
fi

mkdir latest
mv code latest

cp ./build.sh ./lib.toml latest

# apply patch to disable abort(), which causes libfuzzer to crash
pushd latest/code
git apply ../../disable_aborts.patch
popd

# make seeds directory
rm -rf in
mkdir in
cp latest/code/testprogs/BPF/* in/
cp -r latest/code/tests/* in/