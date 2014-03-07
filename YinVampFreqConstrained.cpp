/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */

/*
    pYIN - A fundamental frequency estimator for monophonic audio
    Centre for Digital Music, Queen Mary, University of London.
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.  See the file
    COPYING included with this distribution for more information.
*/

#include "YinVampFreqConstrained.h"
#include "MonoNote.h"

#include "vamp-sdk/FFT.h"

#include <vector>
#include <algorithm>

#include <cstdio>
#include <cmath>
#include <complex>

using std::string;
using std::vector;
using Vamp::RealTime;


YinVampFreqConstrained::YinVampFreqConstrained(float inputSampleRate) :
    Plugin(inputSampleRate),
    m_channels(0),
    m_stepSize(256),
    m_blockSize(2048),
    m_fmin(40),
    m_fmax(1000),
    m_yin(2048, inputSampleRate, 0.0),
    m_yinFmin(100.f),
    m_yinFmax(400.f)
{
}

YinVampFreqConstrained::~YinVampFreqConstrained()
{
}

string
YinVampFreqConstrained::getIdentifier() const
{
    return "yinfc";
}

string
YinVampFreqConstrained::getName() const
{
    return "Frequency-constrained Yin";
}

string
YinVampFreqConstrained::getDescription() const
{
    return "A vamp implementation of the Yin algorithm for monophonic frequency estimation with frequency constraints.";
}

string
YinVampFreqConstrained::getMaker() const
{
    return "Matthias Mauch";
}

int
YinVampFreqConstrained::getPluginVersion() const
{
    // Increment this each time you release a version that behaves
    // differently from the previous one
    return 1;
}

string
YinVampFreqConstrained::getCopyright() const
{
    return "GPL";
}

YinVampFreqConstrained::InputDomain
YinVampFreqConstrained::getInputDomain() const
{
    return TimeDomain;
}

size_t
YinVampFreqConstrained::getPreferredBlockSize() const
{
    return 2048;
}

size_t 
YinVampFreqConstrained::getPreferredStepSize() const
{
    return 256;
}

size_t
YinVampFreqConstrained::getMinChannelCount() const
{
    return 1;
}

size_t
YinVampFreqConstrained::getMaxChannelCount() const
{
    return 1;
}

YinVampFreqConstrained::ParameterList
YinVampFreqConstrained::getParameterDescriptors() const
{
    ParameterList list;
    
    ParameterDescriptor d;

    d.identifier = "minfreq";
    d.name = "Minimum frequency";
    d.description = "Minimum frequency used when searching for difference function minimum.";
    d.unit = "Hz";
    d.minValue = 40.f;
    d.maxValue = 1000.0f;
    d.defaultValue = 100.f;
    d.isQuantized = false;
    d.valueNames.clear();
    list.push_back(d);
    
    d.identifier = "maxfreq";
    d.name = "Maximum frequency";
    d.description = "Maximum frequency used when searching for difference function minimum.";
    d.unit = "Hz";
    d.minValue = 40.f;
    d.maxValue = 1000.0f;
    d.defaultValue = 400.f;
    d.isQuantized = false;
    d.valueNames.clear();
    list.push_back(d);
    
    return list;
}

float
YinVampFreqConstrained::getParameter(string identifier) const
{
    if (identifier == "minfreq") {
        return m_yinFmin;
    }
    if (identifier == "maxfreq") {
        return m_yinFmax;
    }
    return 0.f;
}

void
YinVampFreqConstrained::setParameter(string identifier, float value) 
{
    if (identifier == "minfreq")
    {
        m_yinFmin = value;
    }
    if (identifier == "maxfreq")
    {
        m_yinFmax = value;
    }
}

YinVampFreqConstrained::ProgramList
YinVampFreqConstrained::getPrograms() const
{
    ProgramList list;
    return list;
}

string
YinVampFreqConstrained::getCurrentProgram() const
{
    return ""; // no programs
}

void
YinVampFreqConstrained::selectProgram(string name)
{
}

YinVampFreqConstrained::OutputList
YinVampFreqConstrained::getOutputDescriptors() const
{
    OutputList outputs;

    OutputDescriptor d;
    
    int outputNumber = 0;

    d.identifier = "f0";
    d.name = "Estimated f0";
    d.description = "Estimated fundamental frequency";
    d.unit = "Hz";
    d.hasFixedBinCount = true;
    d.binCount = 1;
    d.hasKnownExtents = true;
    d.minValue = m_fmin;
    d.maxValue = 500;
    d.isQuantized = false;
    d.sampleType = OutputDescriptor::FixedSampleRate;
    d.sampleRate = (m_inputSampleRate / m_stepSize);
    d.hasDuration = false;
    outputs.push_back(d);

    return outputs;
}

bool
YinVampFreqConstrained::initialise(size_t channels, size_t stepSize, size_t blockSize)
{
    if (channels < getMinChannelCount() ||
	channels > getMaxChannelCount()) return false;

/*
    std::cerr << "YinVampFreqConstrained::initialise: channels = " << channels
          << ", stepSize = " << stepSize << ", blockSize = " << blockSize
          << std::endl;
*/
    m_channels = channels;
    m_stepSize = stepSize;
    m_blockSize = blockSize;
    
    reset();

    return true;
}

void
YinVampFreqConstrained::reset()
{    
    m_yin.setFrameSize(m_blockSize);
}

YinVampFreqConstrained::FeatureSet
YinVampFreqConstrained::process(const float *const *inputBuffers, RealTime timestamp)
{
    timestamp = timestamp + Vamp::RealTime::frame2RealTime(m_blockSize/2, lrintf(m_inputSampleRate));
    FeatureSet fs;
    
    double *dInputBuffers = new double[m_blockSize];
    for (size_t i = 0; i < m_blockSize; ++i) dInputBuffers[i] = inputBuffers[0][i];
    
    // std::cerr << "f0 in YinVampFreqConstrained: " << yo.f0 << std::endl;
    Feature f;
    f.hasTimestamp = true;
    f.timestamp = timestamp;
    f.values.push_back(m_yin.constrainedMinPick(dInputBuffers, m_yinFmin, m_yinFmax));
    fs[0].push_back(f);
    
    delete [] dInputBuffers;
    return fs;
}

YinVampFreqConstrained::FeatureSet
YinVampFreqConstrained::getRemainingFeatures()
{
    FeatureSet fs;
    return fs;
}
