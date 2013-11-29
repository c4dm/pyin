/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */
/*
    This file is Copyright (c) 2012 Matthias Mauch

*/

#ifndef _PYIN_H_
#define _PYIN_H_

#include <vamp-sdk/Plugin.h>

#include "Yin.h"

class PYIN : public Vamp::Plugin
{
public:
    PYIN(float inputSampleRate);
    virtual ~PYIN();

    std::string getIdentifier() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getMaker() const;
    int getPluginVersion() const;
    std::string getCopyright() const;

    InputDomain getInputDomain() const;
    size_t getPreferredBlockSize() const;
    size_t getPreferredStepSize() const;
    size_t getMinChannelCount() const;
    size_t getMaxChannelCount() const;

    ParameterList getParameterDescriptors() const;
    float getParameter(std::string identifier) const;
    void setParameter(std::string identifier, float value);

    ProgramList getPrograms() const;
    std::string getCurrentProgram() const;
    void selectProgram(std::string name);

    OutputList getOutputDescriptors() const;

    bool initialise(size_t channels, size_t stepSize, size_t blockSize);
    void reset();

    FeatureSet process(const float *const *inputBuffers,
                       Vamp::RealTime timestamp);

    FeatureSet getRemainingFeatures();

protected:
    size_t m_channels;
    size_t m_stepSize;
    size_t m_blockSize;
    float m_fmin;
    float m_fmax;
    Yin m_yin;
    
    mutable int m_oF0Candidates;
    mutable int m_oF0Probs;
    mutable int m_oVoicedProb;
    mutable int m_oCandidateSalience;
    mutable int m_oSmoothedPitchTrack;
    mutable int m_oNotes;

    float m_threshDistr;
    float m_outputUnvoiced;
    vector<vector<pair<double, double> > > m_pitchProb;
    vector<Vamp::RealTime> m_timestamp;
};

#endif
