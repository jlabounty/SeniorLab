#include "headers/exist_test.h"

#include "GetCsPeaks_Angle.C"

int PeakShift()
{

	//Create Empty Root File
        std::string file_root = "OutputFile_PeakShift.root";
        TFile f(("./"+file_root).c_str(),"RECREATE");
        TTree *t = new TTree("t","Peaks of Functions and their Standard Deviations");
        double mean_i, stdev_i, energy_i, integral_i, dsigma_dOmega_i, angle_i2, err_dsigma_dOmega_i; 

        TBranch *b_mean = t->Branch("mean",&mean_i,"Mean bin of the energy peak/D");
        TBranch *b_stdev = t->Branch("stdev",&stdev_i,"Standard deviation of gaussian fit to the energy peak/D");
        TBranch *b_energy = t->Branch("energy",&energy_i,"Known energy of the peak/D");
        TBranch *b_integral = t->Branch("integral",&integral_i,"Integral under gaussian curve/D");
        TBranch *b_dsigma_dOmega = t->Branch("dsigma_dOmega",&dsigma_dOmega_i,"dsigma_dOmega/D");
        TBranch *b_err_dsigma_dOmega = t->Branch("err_dsigma_dOmega",&err_dsigma_dOmega_i,"Error in dsigma_dOmega/D");
        TBranch *b_angle = t->Branch("angle",&angle_i2,"Angle of detector wrt source/D");

	f.Write();
	f.Close();

	//Run Fitting macros which write to file
	vector<std::string> files;
	vector<double> means, fit_low, fit_high;
//	files.push_back("");
//		means.push_back();
//		fit_low.push_back(650);
//		fit_high.push_back(2000);
	//First Set of Angular Measurements
/*
	files.push_back("data/Cs_137_Angle_000_AlScatter_091416_124734.root");
		means.push_back(920);
		fit_low.push_back(650);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_018_AlScatter_091416_132231.root");
		means.push_back(890);
		fit_low.push_back(600);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_020_AlScatter_091416_133342.root");
		means.push_back(875);
		fit_low.push_back(650);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_025_AlScatter_091416_134820.root");
		means.push_back(875);
		fit_low.push_back(820);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_030_AlScatter_091416_143045.root");
		means.push_back(800);
		fit_low.push_back(650);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_040_AlScatter_091916_115732.root");
		means.push_back(800);
		fit_low.push_back(600);
		fit_high.push_back(2000);
*/
	files.push_back("data/Cs_137_Angle_045_AlScatter_091416_125458.root");
		means.push_back(700);
		fit_low.push_back(550);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_050_AlScatter_091916_120943.root");
		means.push_back(600);
		fit_low.push_back(400);
		fit_high.push_back(1000);
	files.push_back("data/Cs_137_Angle_060_AlScatter_091916_122242.root");
		means.push_back(600);
		fit_low.push_back(400);
		fit_high.push_back(1000);
	files.push_back("data/Cs_137_Angle_070_AlScatter_091916_123953.root");
		means.push_back(600);
		fit_low.push_back(400);
		fit_high.push_back(1000);
	files.push_back("data/Cs_137_Angle_080_AlScatter_091916_130206.root");
		means.push_back(500);
		fit_low.push_back(400);
		fit_high.push_back(600);
	files.push_back("data/Cs_137_Angle_090_AlScatter_091916_131941.root");
		means.push_back(500);
		fit_low.push_back(400);
		fit_high.push_back(600);
	files.push_back("data/Cs_137_Angle_100_AlScatter_091916_133846.root");
		means.push_back(450);
		fit_low.push_back(200);
		fit_high.push_back(700);
	files.push_back("data/Cs_137_Angle_110_AlScatter_091916_140207.root");
		means.push_back(350);
		fit_low.push_back(200);
		fit_high.push_back(500);

	//Second Set of Angular Measurements
/*
	files.push_back("data/Cs_137_Angle_000_AlScatter_092116_115514.root");
		means.push_back(920);
		fit_low.push_back(650);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_018_AlScatter_092116_115904.root");
		means.push_back(932);
		fit_low.push_back(800);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_020_AlScatter_092116_121006.root");
		means.push_back(850);
		fit_low.push_back(650);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_025_AlScatter_092116_122952.root");
		means.push_back(875);
		fit_low.push_back(800);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_030_AlScatter_092116_132830.root");
		means.push_back(800);
		fit_low.push_back(650);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_040_AlScatter_092116_124648.root");
		means.push_back(800);
		fit_low.push_back(600);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_045_AlScatter_092116_130347.root");
		means.push_back(700);
		fit_low.push_back(550);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_050_AlScatter_092116_131450.root");
		means.push_back(600);
		fit_low.push_back(400);
		fit_high.push_back(1000);
	files.push_back("data/Cs_137_Angle_060_AlScatter_092116_132443.root");
		means.push_back(570);
		fit_low.push_back(400);
		fit_high.push_back(800);
	files.push_back("data/Cs_137_Angle_070_AlScatter_092116_133313.root");
		means.push_back(600);
		fit_low.push_back(400);
		fit_high.push_back(1000);
	files.push_back("data/Cs_137_Angle_080_AlScatter_092116_134533.root");
		means.push_back(500);
		fit_low.push_back(400);
		fit_high.push_back(600);
	files.push_back("data/Cs_137_Angle_090_AlScatter_092116_140030.root");
		means.push_back(500);
		fit_low.push_back(400);
		fit_high.push_back(600);
	files.push_back("data/Cs_137_Angle_100_AlScatter_092116_141259.root");
		means.push_back(450);
		fit_low.push_back(200);
		fit_high.push_back(700);
	files.push_back("data/Cs_137_Angle_110_AlScatter_092116_142619.root");
		means.push_back(350);
		fit_low.push_back(200);
		fit_high.push_back(500);	
*/

	//FIles 10/3
/*
	files.push_back("data/Cs_137_Angle_000_AlScatter_100316_121843.root");
		means.push_back(920);
		fit_low.push_back(650);
		fit_high.push_back(2000);
*/
	files.push_back("data/Cs_137_Angle_018_AlScatter_100316_122311.root");
		means.push_back(860);
		fit_low.push_back(650);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_020_AlScatter_100316_123454.root");
		means.push_back(840);
		fit_low.push_back(600);
		fit_high.push_back(1200);
	files.push_back("data/Cs_137_Angle_025_AlScatter_100316_124456.root");
		means.push_back(800);
		fit_low.push_back(600);
		fit_high.push_back(2000);
	files.push_back("data/Cs_137_Angle_030_AlScatter_100316_125213.root");
		means.push_back(800);
		fit_low.push_back(650);
		fit_high.push_back(2000);
/*
	files.push_back("data/Cs_137_Angle_040_AlScatter_100316_131109.root");
		means.push_back(800);
		fit_low.push_back(600);
		fit_high.push_back(2000);
*/	

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
		GetCsPeaks_Angle(files[i], means[i], angle[i], fit_low[i], fit_high[i]);
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
