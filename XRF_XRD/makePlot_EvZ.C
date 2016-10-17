
#include "headers/exist_test.h"

#include "GetAuPeaks.C"
#include "GetAgPeaks.C"
#include "GetCoPeaks.C"
#include "GetCuPeaks.C"

int makePlot_EvZ()
{

	//Create Empty Root File
        std::string file_root = "OutputFile.root";
        TFile f(("./"+file_root).c_str(),"RECREATE");
        TTree *t = new TTree("t","Peaks of Functions and their Standard Deviations");
        double mean_i, stdev_i, energy_i, Z_i; 

        TBranch *b_mean = t->Branch("mean",&mean_i,"Mean bin of the energy peak/D");
        TBranch *b_stdev = t->Branch("stdev",&stdev_i,"Standard deviation of gaussian fit to the energy peak/D");
        TBranch *b_energy = t->Branch("energy",&energy_i,"Known energy of the peak/D");
        TBranch *b_Z = t->Branch("Z",&Z_i,"Atomic Number/D");

	f.Write();
	f.Close();

	//Run Fitting macros which write to file
	GetAuPeaks();
	GetAgPeaks();
	GetCoPeaks();
	GetCuPeaks();
	//Perform analysis on output data
	gStyle->SetOptStat(0); 

	std::string file = "./OutputFile.root";
	TFile f(file.c_str());
	TTree *t = (TTree*)f.Get("t");
	t->Draw("mean:stdev:energy:Z","","goff");
	vector<double> err_energy;
	vector<double> mean, stdev, energy, Z, err_Z;
	for(int i = 0; i < t->GetEntries(); i++) 
	{
		err_energy.push_back(0.00000);
		mean.push_back(sqrt((t->GetV1())[i] / TMath::H()) / 10**16.);
		stdev.push_back(TMath::Abs((t->GetV2())[i]));
		energy.push_back((t->GetV3())[i]);
		Z.push_back((t->GetV4())[i]);
		err_Z.push_back(0.00000);

		// cout << Z[i] << " | " << mean[i] << endl;

	}
	f.Close();

	std::string titleZ = "";
	//Makes canvas large enough for png printing.
        TCanvas *c31 = new TCanvas("c31",titleZ.c_str(),750,750);
		c31->cd();
		c31->SetGridx(1);
		c31->SetGridy(1);
		//		c->SetFixedAspectRatio();
        //Use blank histogram to set the parameters of the canvas
        TH1F *hcalibZ = new TH1F("hcalibZ",titleZ.c_str(),10, 0, 200);
                hcalibZ->GetYaxis()->SetRangeUser(0, 100);
                hcalibZ->GetXaxis()->SetTitle("#sqrt{#nu}");
                hcalibZ->GetYaxis()->SetTitle("Z");
                hcalibZ->GetXaxis()->SetNdivisions(505);
                hcalibZ->GetYaxis()->SetNdivisions(505);
                hcalibZ->SetLineColor(0);
        hcalibZ->Draw();

	TGraphErrors *grZ = new TGraphErrors(err_energy.size(), &(mean[0]), &(Z[0]), &(stdev[0]), &(err_Z[0]) );
	grZ->Draw("p SAME");

	return 0;
}
