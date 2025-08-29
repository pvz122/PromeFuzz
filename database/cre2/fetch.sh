#!/bin/bash

COMMIT_ID="$1"
REPO_URL="https://github.com/marcomaggi/cre2.git"
REPO_URL_2="https://github.com/google/re2.git"

git clone "$REPO_URL" cre2
if [ $? -ne 0 ]; then
    echo "Failed to clone cre2 repository. Exiting."
    exit 1
fi
git clone "$REPO_URL_2" re2
if [ $? -ne 0 ]; then
    echo "Failed to clone re2 repository. Exiting."
    exit 1
fi

if [ -n "$COMMIT_ID" ]; then
    cd re2
    git checkout "$COMMIT_ID"
    if [ $? -ne 0 ]; then
        echo "Failed to checkout to commit $COMMIT_ID. Exiting."
        exit 1
    fi
    cd ..
fi

mkdir code
mv cre2 code
mv re2 code

pushd code/cre2
autoreconf -fi
popd

mkdir latest
mv code latest

cp ./build.sh ./lib.toml latest

echo "Repository successfully cloned and copied to 'latest' directory."