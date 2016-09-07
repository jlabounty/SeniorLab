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

	int line_count = 1;
	while (std::getline(file, str))
	{
		if(line_count > 12 && line_count < 2060)
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

	for(int i = 0; i< count.size(); i++)
	{
		bin_i = bin[i];
		count_i = count[i];
		t->Fill();
	}

	f.Write();
	f.Close();

	cout << "File: " << file_name << " converted to " << data_file_root << endl;

	return 0;

}
