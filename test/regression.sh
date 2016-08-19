#!/bin/bash

set -eu

testdir=$(dirname "$0")

if ! sonic-annotator -v >/dev/null ; then
    echo "No sonic-annotator available in PATH, skipping regression test"
    exit 0
fi

echo "Running regression test..."

( time ( VAMP_PATH="$testdir/.." sonic-annotator \
	 -d vamp:pyin:pyin:smoothedpitchtrack \
	 -w csv --csv-stdout --csv-omit-filename \
	 "$testdir/../testdata/bob_02.wav" \
	 > "$testdir/obtained.csv" \
	 2> "$testdir/log.txt" ) ) 2>&1 | \
    grep -i real | \
    sed 's/^real/Elapsed time/'

if ! cmp -s "$testdir/expected.csv" "$testdir/obtained.csv" ; then
    echo "*** FAILED, diff follows:"
    sdiff -w78 "$testdir/expected.csv" "$testdir/obtained.csv"
else
    echo "Succeeded"
fi

