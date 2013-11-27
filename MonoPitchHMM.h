/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */
/*
    This file is Copyright (c) 2012 Matthias Mauch

*/

#ifndef _MONOPITCHHMM_H_
#define _MONOPITCHHMM_H_

#include "SparseHMM.h"

#include <boost/math/distributions.hpp>

#include <vector>
#include <cstdio>

using std::vector;

class MonoPitchHMM : public SparseHMM
{
public:
    MonoPitchHMM();
    const std::vector<double> calculateObsProb(const vector<pair<double, double> >);
    // double getMidiPitch(size_t index);
    // double getFrequency(size_t index);
    void build();
    double m_minFreq; // 82.40689f/2
    size_t m_nBPS;
    size_t m_nPitch;
    size_t m_transitionWidth;
    double m_selfTrans;
    double m_yinTrust;
    vector<double> m_freqs;
};

#endif
