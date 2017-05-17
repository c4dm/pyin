#!/bin/bash

set -eu

testdir=$(dirname "$0")
rootdir="$testdir/../.."

if ! sonic-annotator -v >/dev/null ; then
    echo "No sonic-annotator available in PATH, skipping regression test"
    exit 0
fi

echo "Running regression test..."

for output in smoothedpitchtrack notes ; do

    ( time ( VAMP_PATH="$rootdir" sonic-annotator \
	              -d vamp:pyin:pyin:$output \
	              -w csv --csv-stdout --csv-omit-filename \
	              "$rootdir/testdata/bob_02.wav" \
	              > "$testdir/obtained-$output.csv" \
	              2> "$testdir/log-$output.txt" ) ) 2>&1 | \
        grep -i real | \
        sed 's/^real/Elapsed time/'

    if ! cmp -s "$testdir/expected-$output.csv" "$testdir/obtained-$output.csv" ; then
        echo "*** FAILED for output $output, diff follows:"
        sdiff -w78 "$testdir/expected-$output.csv" "$testdir/obtained-$output.csv"
    else
        echo "Succeeded for output $output"
    fi
done


