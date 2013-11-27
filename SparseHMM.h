/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */
/*
    This file is Copyright (c) 2012 Matthias Mauch

*/

#ifndef _SPARSEHMM_H_
#define _SPARSEHMM_H_

#include <vector>
#include <cstdio>

using std::vector;
using std::pair;

class SparseHMM
{
public:
    virtual const std::vector<double> calculateObsProb(const vector<pair<double, double> >);
    const std::vector<int> decodeViterbi(std::vector<vector<double> > obs, 
                                   vector<double> *scale);
    vector<double> init;
    vector<size_t> from;
    vector<size_t> to;
    vector<double> transProb;
};

#endif