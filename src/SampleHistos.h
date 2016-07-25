// SampleHistos.h

#ifndef PLOTS
#define PLOTS

#include <vector>
#include <iostream>

#include "Sample.h"
#include "../selection/Cuts.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TString.h"

class SampleHistos
{
   public:
	SampleHistos();
	SampleHistos(Sample* sample, Cuts* cut, TString cutName);

	Sample* sample;

	void setHistTitles(TH1F* hist, TString xtitle, TString ytitle);
	float getTrackNumDiff(std::size_t emTracks, std::size_t cscTracks);
	float getEMPtResolution(unsigned j, unsigned k);
	float getCSCPtResolution(unsigned j, unsigned k);

   protected:
	TFile* file;  // output file with histograms

};

#endif
