#include "MonoPitch.h"
#include "MonoPitchHMM.h"
#include <vector>

#include <cstdio>
#include <cmath>
#include <complex>

using std::vector;
using std::pair;

MonoPitch::MonoPitch() :
    hmm()
{
}

MonoPitch::~MonoPitch()
{
}

const vector<float>
MonoPitch::process(const vector<vector<pair<double, double> > > pitchProb)
{
    // std::cerr << "before observation prob calculation" << std::endl;
    vector<vector<double> > obsProb;
    for (size_t iFrame = 0; iFrame < pitchProb.size(); ++iFrame)
    {
        obsProb.push_back(hmm.calculateObsProb(pitchProb[iFrame]));
    }
    for (size_t i = 0; i < obsProb[0].size(); ++i) {
        obsProb[0][i] = 0;
    }
    obsProb[0][obsProb[0].size()-1] = 1;
    
    // std::cerr << "after observation prob calculation" << std::endl;
    
    vector<double> *scale = new vector<double>(pitchProb.size());
    
    vector<float> out; 
    
    // std::cerr << "before Viterbi decoding" << obsProb.size() << "ng" << obsProb[1].size() << std::endl;
    vector<int> path = hmm.decodeViterbi(obsProb, scale);
    // std::cerr << "after Viterbi decoding" << std::endl;
    
    for (size_t iFrame = 0; iFrame < path.size(); ++iFrame)
    {
        // std::cerr << path[iFrame] << " " << hmm.m_freqs[path[iFrame]] << std::endl;
        float hmmFreq = hmm.m_freqs[path[iFrame]];
        float bestFreq = 0;
        float leastDist = 10000;
        if (hmmFreq > 0)
        {
            // This was a Yin estimate, so try to get original pitch estimate back
            // ... a bit hacky, since we could have direclty saved the frequency
            // that was assigned to the HMM bin in hmm.calculateObsProb -- but would
            // have had to rethink the interface of that method.
            for (size_t iPitch = 0; iPitch < pitchProb[iFrame].size(); ++iPitch)
            {
                float freq = 440. * std::pow(2, (pitchProb[iFrame][iPitch].first - 69)/12);
                float dist = std::abs(hmmFreq-freq);
                if (dist < leastDist)
                {
                    leastDist = dist;
                    bestFreq = freq;
                }
            }
        } else {
            bestFreq = hmmFreq;
        }
        out.push_back(bestFreq);
    }
    delete scale;
    return(out);
}