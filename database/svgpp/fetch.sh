#!/bin/bash

COMMIT_ID="$1"
REPO_URL="https://github.com/svgpp/svgpp.git"

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

# since this is a header-only library, we add a source file to include the header
cat <<EOF > code/svgpp.cpp
#include "svgpp/attribute_dispatcher.hpp"
#include "svgpp/config.hpp"
#include "svgpp/definitions.hpp"
#include "svgpp/document_traversal.hpp"
#include "svgpp/number_type.hpp"
#include "svgpp/svgpp.hpp"
#include "svgpp/template_parameters.hpp"
EOF

# build documents
pushd code/doc/sphinx
make text
popd

mkdir latest
mv code latest

cp ./build.sh ./lib.toml latest
