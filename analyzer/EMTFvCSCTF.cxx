#include "../src/Sample.h"
#include "../selection/Cuts.h"
#include "SampleHistos.h"
#include "Plots.h"

#include "TLorentzVector.h"

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <utility>

//////////////////////////////////////////////////
//------------------------------------------------
//////////////////////////////////////////////////

int main()
{
    // Should use this as the main database and choose from it to make the vector
    std::map<std::string, Sample*> samples;
       
    // Second container so that we can have a copy sorted by cross section.
    //std::vector<Sample*> samplevec;

    ///////////////////////////////////////////////////////////////////
    // SAMPLES---------------------------------------------------------
    ///////////////////////////////////////////////////////////////////
   
    //float luminosity = 2169;
    //float lumiSF = 10;
    
    // use this to scale the MC for some projected amount of luminosity
    //luminosity *= lumiSF;
    
    //float signalSF = 100;
    
    // ================================================================
    // Data -----------------------------------------------------------
    // ================================================================
    
    std::cout << "============ Accessing Data ===============" << std::endl;           
    
    TString datafilename = TString("/home/bregnery/EMTFvCSCTF/ntuples/EMTF_NTuple_ZMu_274442_emtfStage2Digis_40k.root");
    //TString datafilename = TString("/cms/data/store/user/t2/users/acarnes/h2mumu/samples/stage1/data_from_json/25ns/golden/stage_1_singleMuon_RunDBoth_MINIAOD_GOLDEN_ALL.root");
    samples["Data"] = new Sample(datafilename, "Data", "data");

    // Debugging
    //Sample sample;
    //std::cout << "lumi: " << sample.lumi << std::endl;
 
    ///////////////////////////////////////////////////////////////////
    // Cuts------------------------------------------------------------
    ///////////////////////////////////////////////////////////////////
    
    // map containing the cuts
    std::map<std::string, Cuts*> cuts;   
                        
    std::cout << "=========== Applying Selection Criteria to Data ======" << std::endl;
    cuts["Data"] = new Cuts(samples["Data"]);

    ///////////////////////////////////////////////////////////////////
    // Histograms------------------------------------------------------
    ///////////////////////////////////////////////////////////////////    
    
    // map containg the Histogram variables
    std::map<std::string, SampleHistos*> sampleHistos;
    
    std::cout << "=========== Creating Data Histogram file ===========" << std::endl;
    sampleHistos["Data"] = new SampleHistos(samples["Data"], cuts["Data"], "Comparison");

    ///////////////////////////////////////////////////////////////////
    // CMS style Plots-------------------------------------------------
    ///////////////////////////////////////////////////////////////////    

    std::cout << "=========== Creating CMS Style Plots ===============" << std::endl;
    Plots *plots = new Plots(samples["Data"], cuts["Data"], sampleHistos["Data"], "Comparison");

    ///////////////////////////////////////////////////////////////////
    // Close TFiles----------------------------------------------------
    ///////////////////////////////////////////////////////////////////

    sampleHistos["Data"]->closeFile();

    return 0;
}
