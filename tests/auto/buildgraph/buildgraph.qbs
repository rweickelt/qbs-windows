import qbs

QbsAutotest {
    testName: "buildgraph"
    condition: false
    files: [
        "tst_buildgraph.cpp",
        "tst_buildgraph.h"
    ]
}
