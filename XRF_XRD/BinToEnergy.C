#include "headers/exist_test.h"

#include "GetAmPeaks.C"
#include "GetFePeaks.C"

#include "GetAgPeaks.C"
#include "GetAuPeaks.C"
#include "GetCdPeaks.C"
#include "GetCoPeaks.C"
#include "GetCuPeaks.C"
#include "GetGdPeaks.C"
#include "GetInPeaks.C"
#include "GetMoPeaks.C"
#include "GetNbPeaks.C"
#include "GetNiPeaks.C"
#include "GetWXPeaks.C"

int BinToEnergy()
{

	//Create Empty Root File
        std::string file_root = "OutputFile.root";
        TFile f(("./"+file_root).c_str(),"RECREATE");
        TTree *t = new TTree("t","Peaks of Functions and their Standard Deviations");
        double mean_i, stdev_i, energy_i, Z_i;
	int line_i;

        TBranch *b_mean = t->Branch("mean",&mean_i,"Mean bin of the energy peak/D");
        TBranch *b_stdev = t->Branch("stdev",&stdev_i,"Standard deviation of gaussian fit to the energy peak/D");
        TBranch *b_energy = t->Branch("energy",&energy_i,"Known energy of the peak/D");
        TBranch *b_Z = t->Branch("Z",&Z_i,"Atomic Number of the Element/D");
	TBranch *b_line = t->Branch("Ident", &line_i,"Identifier of the specific transition. Kalpha = 01, Lbeta = 12, etc./I");

	f.Write();
	f.Close();

	//Run Fitting macros which write to file
	// GetAmPeaks("data/Am_241_100516_132724.root");	
	// GetAmPeaks("data/Am_241_100516_140641.root");	
	GetAmPeaks("data/Am_241_101016_144743.root");	
	GetFePeaks("data/Fe_055_100516_140912.root");	
	GetAgPeaks();
	GetAuPeaks();
	GetCdPeaks();
	GetCoPeaks();
	GetCuPeaks();
	GetGdPeaks();
	GetInPeaks();
	GetMoPeaks();
	GetNbPeaks();
	GetNiPeaks();
	GetWXPeaks();
	//Perform analysis on output data
	gStyle->SetOptStat(0); 

	std::string file = "./OutputFile.root";
	TFile f(file.c_str());
	TTree *t = (TTree*)f.Get("t");
	t->Draw("mean:stdev:energy","","goff");
	vector<double> err_energy;
	vector<double> mean, stdev, energy;
	for(int i = 0; i < t->GetEntries(); i++) 
	{
		err_energy.push_back(0.00000);
		mean.push_back((t->GetV1())[i]);
		stdev.push_back(TMath::Abs((t->GetV2())[i]));
		energy.push_back((t->GetV3())[i]);

		//cout << mean[i] << " | " << energy[i] << endl;

	}
	f.Close();

	std::string title = "Known Energy vs. Bin Numbers";
	//Makes canvas large enough for png printing.
        TCanvas *c = new TCanvas("c",title.c_str(),750,750);
		c->cd();
		c->SetGridx(1);
		c->SetGridy(1);
		//		c->SetFixedAspectRatio();
        //Use blank histogram to set the parameters of the canvas
        TH1F *hcalib = new TH1F("hcalib",title.c_str(),10, 0, 2048);
                hcalib->GetYaxis()->SetRangeUser(0, 30);
                hcalib->GetXaxis()->SetTitle("Bin Number");
                hcalib->GetYaxis()->SetTitle("Energy (keV)");
                hcalib->GetXaxis()->SetNdivisions(505);
                hcalib->GetYaxis()->SetNdivisions(505);
                hcalib->SetLineColor(0);
        hcalib->Draw();

	TGraphErrors *gr = new TGraphErrors(err_energy.size(), &(mean[0]),  &(energy[0]), &(stdev[0]), &(err_energy[0]) );
	gr->Draw("p SAME");

	TF1 *fit1 = new TF1("fit1","pol1", 0, 2048);
	fit1->SetParameters(10, 2);
	gr->Fit("fit1", "0");
	cout << "Chi-Squared: " << fit1->GetChisquare() << endl;
	cout << "NDF: " << fit1->GetNDF() << endl; 
	
	TF1 *f1 = new TF1("f1", "pol1", 0, 2048);
		f1->SetParameter(0, fit1->GetParameter(0));
		f1->SetParameter(1, fit1->GetParameter(1));
		f1->SetLineStyle(7);
	f1->Draw("l SAME");
	
	c->Update();

	TCanvas *c2 = new TCanvas();

        TH1F *h_CS137 = new TH1F("h_CS137","^{137}Cs Calibrated Spectrum",10, 0, 1000);
       	h_CS137->GetYaxis()->SetRangeUser(0.0, 200.);
	h_CS137->GetXaxis()->SetTitle("Energy (keV)");
	h_CS137->GetYaxis()->SetTitle("Photon Count");
	h_CS137->GetYaxis()->SetTitleOffset(1.65);
	h_CS137->GetXaxis()->SetNdivisions(505);
	h_CS137->GetYaxis()->SetNdivisions(505);
	h_CS137->SetLineColor(0);
        h_CS137->Draw();

	TFile *csFile = TFile::Open("data/Rh_045_100516_125309.root");
        TTree *t2 = (TTree*)csFile->Get("t");
        t2->Draw("Count:Bin","","goff");
        vector<double> v_count, v_bin;
        for(int i = 0; i < t2->GetEntries(); i++)
	  {
	    v_count.push_back(t2->GetV1()[i]);
	    v_bin.push_back( fit1->Eval(t2->GetV2()[i]) );

	  }
        TGraph *gr1 = new TGraph(v_count.size(), &(v_bin[0]), &(v_count[0]));
        gr1->Draw("p SAME");

	return 0;
}
