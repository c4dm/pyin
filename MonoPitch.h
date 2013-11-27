#ifndef _MONOPITCH_H_
#define _MONOPITCH_H_

#include "MonoPitchHMM.h"

#include <iostream>
#include <vector>
#include <exception>

using std::vector;
using std::pair;

class MonoPitch {
public:
    MonoPitch();
    virtual ~MonoPitch();
    
    // pitchProb is a frame-wise vector carrying a vector of pitch-probability pairs
    const vector<float> process(const vector<vector<pair<double, double> > > pitchProb);
private:
    MonoPitchHMM hmm;
};

#endif