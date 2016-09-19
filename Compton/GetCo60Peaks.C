int GetCo60Peaks(
	       TString infile = "data/Co_60_Weak_091216_131604.root"
)
{
  TFile *csFile = TFile::Open(infile); 
  TH1D *csHraw = new TH1D();
  csHraw = (TH1D*)csFile->Get("h");
  TCanvas *c1 = new TCanvas();
  csHraw->Draw();

  vector<double> mean, stdev, energy;

  /*========Co-60 1173 keV Peak=========*/

  TH1D *csHist_1173 = (TH1D*)h->Clone("csHraw");
  TF1 *fSpec_1173 = new TF1("fSpec_1173", "gaus", 1330., 1450.);
  fSpec_1173->SetParameters(100, 1400, 2);
  TCanvas *c2 = new TCanvas();
  csHist_1173->Fit("fSpec_1173", "Q", "", 1330., 1450.);

  TF1 *fGausStat_1173 = csHist_1173->GetFunction("fSpec_1173");

  double Chi_1173 = fGausStat_1173->GetChisquare();
  double NDF_1173 = fGausStat_1173->GetNDF();
  double Red_1173 = Chi_1173/NDF_1173;

  cout << "=======================" << endl;
  cout << "!                     !" << endl;
  cout << "!       Co-60         !" << endl;
  cout << "!                     !" << endl;
  cout << "=======================" << endl;

  cout << "=======================" << endl;
  cout << "!!Finding 1173 keV Peak!!" << endl;
  cout << "-----------------------" << endl;
  double Peak_1173 = fGausStat_1173->GetParameter(1);
  double Stdv_1173 = fGausStat_1173->GetParameter(2);
  cout << "Peak Occurs at: " << endl;
  cout << Peak_1173 << " +/- " << Stdv_1173 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_1173 << endl;
  cout << "DoF        |  " << NDF_1173 << endl;
  cout << "Red Chi-Sq |  " << Red_1173 << endl;
  cout << "=======================" << endl;

  energy.push_back(1173.0);
  mean.push_back(Peak_1173);
  stdev.push_back(Stdv_1173);

  /*========Co-60 1332 keV Peak=========*/

  TH1D *csHist_1332 = (TH1D*)h->Clone("csHraw");
  TF1 *fSpec_1332 = new TF1("fSpec_1332", "gaus", 1470., 1640.);
  fSpec_1332->SetParameters(100, 1520, 2);
  TCanvas *c3 = new TCanvas();
  csHist_1332->Fit("fSpec_1332", "Q", "", 1470., 1640.);

  TF1 *fGausStat_1332 = csHist_1332->GetFunction("fSpec_1332");

  double Chi_1332 = fGausStat_1332->GetChisquare();
  double NDF_1332 = fGausStat_1332->GetNDF();
  double Red_1332 = Chi_1332/NDF_1332;

  cout << "=======================" << endl;
  cout << "!                     !" << endl;
  cout << "!       Co-60         !" << endl;
  cout << "!                     !" << endl;
  cout << "=======================" << endl;

  cout << "=======================" << endl;
  cout << "!!Finding 1332 keV Peak!!" << endl;
  cout << "-----------------------" << endl;
  double Peak_1332 = fGausStat_1332->GetParameter(1);
  double Stdv_1332 = fGausStat_1332->GetParameter(2);
  cout << "Peak Occurs at: " << endl;
  cout << Peak_1332 << " +/- " << Stdv_1332 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_1332 << endl;
  cout << "DoF        |  " << NDF_1332 << endl;
  cout << "Red Chi-Sq |  " << Red_1332 << endl;
  cout << "=======================" << endl;

  energy.push_back(1332.0);
  mean.push_back(Peak_1332);
  stdev.push_back(Stdv_1332);

  /*===================================*/
  
	//Output the data to a root file
	//Create a root file to store the data taken from the files
	std::string file_root = "OutputFile.root";
	TFile f(("./"+file_root).c_str(),"UPDATE");
	TTree *t = (TTree*)f.Get("t");
	double mean_i, stdev_i, energy_i; 

	t->SetBranchAddress("mean",&mean_i);
	t->SetBranchAddress("stdev",&stdev_i);
	t->SetBranchAddress("energy",&energy_i);


	//Fill the output file branches with the data from the file 
	for(int i = 0; i < mean.size(); i++)
	{
		mean_i = mean[i];
		energy_i = energy[i];
		stdev_i = stdev[i];
		t->Fill();
	}

	f.Write();
	f.Close();

	c1->Close();
	c2->Close();
	c3->Close();

  return 0;
}
