#include "headers/exist_test.h"

#include "GetCsPeaks_Angle.C"

int PeakShift()
{

	//Create Empty Root File
        std::string file_root = "OutputFile_PeakShift.root";
        TFile f(("./"+file_root).c_str(),"RECREATE");
        TTree *t = new TTree("t","Peaks of Functions and their Standard Deviations");
        double mean_i, stdev_i, energy_i, integral_i, dsigma_dOmega_i, angle_i2; 

        TBranch *b_mean = t->Branch("mean",&mean_i,"Mean bin of the energy peak/D");
        TBranch *b_stdev = t->Branch("stdev",&stdev_i,"Standard deviation of gaussian fit to the energy peak/D");
        TBranch *b_energy = t->Branch("energy",&energy_i,"Known energy of the peak/D");
        TBranch *b_integral = t->Branch("integral",&integral_i,"Integral under gaussian curve/D");
        TBranch *b_dsigma_dOmega = t->Branch("dsigma_dOmega",&dsigma_dOmega_i,"dsigma_dOmega/D");
        TBranch *b_angle = t->Branch("angle",&angle_i2,"Angle of detector wrt source/D");

	f.Write();
	f.Close();

	//Run Fitting macros which write to file
	vector<std::string> files;
	vector<double> means;
	files.push_back("data/Cs_137_Angle_030_AlScatter_091416_143045.root");
		means.push_back(800);
	files.push_back("data/Cs_137_Angle_025_AlScatter_091416_134820.root");
		means.push_back(875);
	vector<double> angle;
	std::string angle_string;
	int angle_i;
	std::string file1;
	for(int i = 0; i < files.size(); i++)
	{
		file1 = files[i];
		angle_string = ((file1.erase(0,18)).erase(3,file1.size()-3));
		if(angle_string[0] == '0') angle_string.erase(0,1);
		cout << angle_string << endl;
		angle_i = std::atoi(angle_string.c_str());
		cout << "Angle: " <<  angle_i << endl;
		angle.push_back(angle_i);
		GetCsPeaks_Angle(files[i], means[i], angle[i]);
	}

	//Perform analysis on output data
	gStyle->SetOptStat(0); 

	std::string file = "./OutputFile_PeakShift.root";
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

	return 0;
}
