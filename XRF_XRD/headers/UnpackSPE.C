#include "exist_test.h"

int UnpackSPE(std::string file_name)
{

	if(!exists_test(file_name))
	{
		cerr << "ERROR: File " << file_name << " not found. Aborting." << endl;
		return -1;
	}

	std::ifstream file(file_name.c_str());
	std::string str;
	vector<int> bin, count;
	int count_i, bin_i;
	vector<double> time;
	double measurement_time, live_time;

	int line_count = 1;
	while (std::getline(file, str))
	{
		if(line_count == 9)
		{
			if(file >> live_time >> measurement_time) 
			{
				time.push_back(measurement_time);
				// cout << measurement_time << endl;
			}
		}
		else if(line_count > 12 && line_count < 2060)
		{
			if(file >> count_i)
			{
				bin.push_back(line_count);
				count.push_back(count_i);
			}
		}
		line_count++;
	}

	std::string data_file_root = (file_name.erase(file_name.size()-3,3)).append("root");
	TFile f((data_file_root).c_str(),"RECREATE");
	TTree *t = new TTree("t","Compton Effect Measurement");

	TBranch *b_bin = t->Branch("Bin",&bin_i,"Bin Number/I");
	TBranch *b_count = t->Branch("Count",&count_i,"Count of Photons in Bin/I");
	TBranch *b_time = t->Branch("Time",&measurement_time,"Time the measurement was live/D");

	for(int i = 0; i< count.size(); i++)
	{
		bin_i = bin[i];
		count_i = count[i];
		t->Fill();
	}

	std::string file_name_2 = file_name;
	std::string element = (file_name_2.erase(file_name_2.size()-24,24)).erase(0,41);
	TH1F *h = new TH1F("h",("Histogram of "+element).c_str(), count.size(), 0, count.size());
	for(int i = 0; i < count.size(); i++)
	{
		h->SetBinContent(i,count[i]);
	}


	f.Write();
	f.Close();

	cout << "File: " << file_name << " converted to " << data_file_root << endl;

	return 0;

}
