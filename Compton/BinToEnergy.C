#include "headers/exist_test.h"

#include "GetCsPeaks.C"
#include "GetNaPeaks.C"
#include "GetBaPeaks.C"

int BinToEnergy()
{

	//Create Empty Root File
        std::string file_root = "OutputFile.root";
        TFile f(("./"+file_root).c_str(),"RECREATE");
        TTree *t = new TTree("t","Peaks of Functions and their Standard Deviations");
        double mean_i, stdev_i, energy_i; 

        TBranch *b_mean = t->Branch("mean",&mean_i,"Mean bin of the energy peak/D");
        TBranch *b_stdev = t->Branch("stdev",&stdev_i,"Standard deviation of gaussian fit to the energy peak/D");
        TBranch *b_energy = t->Branch("energy",&energy_i,"Known energy of the peak/D");

	f.Write();
	f.Close();

	//Run Fitting macros which write to file
	GetCsPeaks();
	GetBaPeaks();
	GetNaPeaks();

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

		cout << mean[i] << " | " << energy[i] << endl;

	}
	f.Close();

	std::string title = "Known Energy vs. Bin Numbers";

        TCanvas *c = new TCanvas("c",title.c_str(),750,750);        //Makes canvas large enough for png printing.
		c->cd();
		c->SetGridx(1);
		c->SetGridy(1);
		c->SetFixedAspectRatio();
        //Use blank histogram to set the parameters of the canvas
        TH1F *blank = new TH1F("blank",title.c_str(),10, 0, 2048);
                blank->GetYaxis()->SetRangeUser(0, 2048);
                blank->GetXaxis()->SetTitle("Energy (keV)");
                //blank->GetYaxis()->SetTitle("B_{0} - B_{i} (mT)");    //Shielding Factor y-axis
                blank->GetYaxis()->SetTitle("Bin Number");              //Internal vs. External Field y-axis
                blank->GetXaxis()->SetNdivisions(505);
                blank->GetYaxis()->SetNdivisions(505);
                blank->SetLineColor(0);
        blank->Draw();

	TGraphErrors *gr = new TGraphErrors(err_energy.size(), &(energy[0]), &(mean[0]), &(err_energy[0]), &(stdev[0]));
	gr->Draw("p SAME");

	TF1 *fit1 = new TF1("fit1","pol1");
	gr->Fit("fit1","0 Q");
	double slope = fit1->GetParameter(1);
	cout << "The slope is: " << slope << " Bins/keV" << endl;

	TF1 *f1 = new TF1("f1", "pol1", 0, 2048);
		f1->SetParameter(0, fit1->GetParameter(0));
		f1->SetParameter(1, fit1->GetParameter(1));
		f1->SetLineStyle(7);
	f1->Draw("l SAME");
	
	c->Update();
	return 0;
}
