int GetAgPeaks(
	       TString infile = "data/Scattering_Ag_100516_143056.root"
)
{
  TFile *agFile = TFile::Open(infile); 
  TH1D *agHraw = new TH1D();
  agHraw = (TH1D*)agFile->Get("h");
  TCanvas *c1 = new TCanvas();
  agHraw->Draw();
  vector<double> mean, stdev, energy, Z;

  /*==============Ag-107 K1 Peak==============*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *agHist_K1 = (TH1D*)h->Clone("agHraw");
  /*Define Spectrum Fit Function*/
  TF1 *fSpec_K1 = new TF1("fSpec_K1", "gaus", 890., 920.);
  /*Estimate Parameters of Fit*/
  fSpec_K1->SetParameters(900, 10, 2);
  TCanvas *c2 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  agHist_K1->Fit("fSpec_K1", "Q", "", 890., 920.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_K1 = agHist_K1->GetFunction("fSpec_K1");

  /*Assign Fit Parameters to Variables*/
  double Peak_K1 = fStat_K1->GetParameter(1);
  double Stdv_K1 = fStat_K1->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_K1 = fStat_K1->GetChisquare();
  double NDF_K1 = fStat_K1->GetNDF();
  double Red_K1 = Chi_K1/NDF_K1;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!                     !" << endl;
  cout << "!       Ag-107        !" << endl;
  cout << "!                     !" << endl;
  cout << "=======================" << endl;

  cout << "=======================" << endl;
  cout << "!   Finding K1 Peak   !" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_K1 << " +/- " << Stdv_K1 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_K1 << endl;
  cout << "DoF        |  " << NDF_K1 << endl;
  cout << "Red Chi-Sq |  " << Red_K1 << endl;
  cout << "=======================" << endl;

  /*Append Values to Vectors*/
  energy.push_back(22.16);
  Z.push_back(47.);
  mean.push_back(Peak_K1);
  stdev.push_back(Stdv_K1);

  /*===================================*/

  /*===========Ag-107 K2 Peak==========*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *agHist_K2 = (TH1D*)h->Clone("agHraw");
  /*Define Spectrum Fit*/
  TF1 *fSpec_K2 = new TF1("fSpec_K2", "gaus", 1005., 1030.);
  /*Estimate Parameters of Fit Function*/
  // fSpec_K2->SetParNames("Strength", "Mean","Sigma", "Back1", "Back2", "Back3"); 
  fSpec_K2->SetParameters(1020., 1000, 2);
  TCanvas *c3 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  agHist_K2->Fit("fSpec_K2", "Q", "", 1005., 1030.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_K2 = agHist_K2->GetFunction("fSpec_K2");

  /*Assign Fit Parameters to Variables*/
  double Peak_K2 = fStat_K2->GetParameter(1);
  double Stdv_K2 = fStat_K2->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_K2 = fStat_K2->GetChisquare();
  double NDF_K2 = fStat_K2->GetNDF();
  double Red_K2 = Chi_K2/NDF_K2;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!   Finding K2 Peak   !" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_K2 << " +/- " << Stdv_K2 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_K2 << endl;
  cout << "DoF        |  " << NDF_K2 << endl;
  cout << "Red Chi-Sq |  " << Red_K2 << endl;
  cout << "=======================" << endl;
  
  /*Append Values to Vectors*/
  energy.push_back(24.94);
  Z.push_back(47.);
  mean.push_back(Peak_K2);
  stdev.push_back(Stdv_K2);

  /*===================================*/

  /*==============Ag-107 L1 Peak==============*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *agHist_L1 = (TH1D*)h->Clone("agHraw");
  /*Define Spectrum Fit Function*/
  TF1 *fSpec_L1 = new TF1("fSpec_L1", "landau", 9., 15.);
  /*Estimate Parameters of Fit*/
  fSpec_L1->SetParameters(12, 75);
  TCanvas *c2 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  agHist_L1->Fit("fSpec_L1", "Q", "", 9., 15.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_L1 = agHist_L1->GetFunction("fSpec_L1");

  /*Assign Fit Parameters to Variables*/
  double Peak_L1 = fStat_L1->GetParameter(1);
  double Stdv_L1 = fStat_L1->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_L1 = fStat_L1->GetChisquare();
  double NDF_L1 = fStat_L1->GetNDF();
  double Red_L1 = Chi_L1/NDF_L1;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!   Finding L1 Peak   !" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_L1 << " +/- " << Stdv_L1 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_L1 << endl;
  cout << "DoF        |  " << NDF_L1 << endl;
  cout << "Red Chi-Sq |  " << Red_L1 << endl;
  cout << "=======================" << endl;

  /*Append Values to Vectors*/
  // energy.push_back(2.98);
  // Z.push_back(47.);
  // mean.push_back(Peak_L1);
  // stdev.push_back(Stdv_L1);

  /*===================================*/

  /*==============Ag-107 L2 Peak==============*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *agHist_L2 = (TH1D*)h->Clone("agHraw");
  /*Define Spectrum Fit Function*/
  TF1 *fSpec_L2 = new TF1("fSpec_L2", "gaus", 700., 720.);
  /*Estimate Parameters of Fit*/
  fSpec_L2->SetParameters(710, 75, 2);
  TCanvas *c2 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  agHist_L2->Fit("fSpec_L2", "Q", "", 700., 720.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_L2 = agHist_L2->GetFunction("fSpec_L2");

  /*Assign Fit Parameters to Variables*/
  double Peak_L2 = fStat_L2->GetParameter(1);
  double Stdv_L2 = fStat_L2->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_L2 = fStat_L2->GetChisquare();
  double NDF_L2 = fStat_L2->GetNDF();
  double Red_L2 = Chi_L2/NDF_L2;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!   Finding L2 Peak   !" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_L2 << " +/- " << Stdv_L2 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_L2 << endl;
  cout << "DoF        |  " << NDF_L2 << endl;
  cout << "Red Chi-Sq |  " << Red_L2 << endl;
  cout << "=======================" << endl;

  /*Append Values to Vectors*/
  // energy.push_back(3.15);
  // Z.push_back(47.);
  // mean.push_back(Peak_L2);
  // stdev.push_back(Stdv_L2);

  /*===================================*/

  // /*==============Ag-107 L3 Peak==============*/
  // /*Clone Histogram of Spectrum from Data File*/
  // TH1D *agHist_L3 = (TH1D*)h->Clone("agHraw");
  // /*Define Spectrum Fit Function*/
  // TF1 *fSpec_L3 = new TF1("fSpec_L3", "gaus", 700., 720.);
  // /*Estimate Parameters of Fit*/
  // fSpec_L3->SetParameters(710, 75, 2);
  // TCanvas *c2 = new TCanvas();
  // /*Fit Pre-Defined Function to Spectrum*/
  // agHist_L3->Fit("fSpec_L3", "Q", "", 700., 720.);

  // /*Obtain Fit Function from Histogram*/
  // TF1 *fStat_L3 = agHist_L3->GetFunction("fSpec_L3");

  // /*Assign Fit Parameters to Variables*/
  // double Peak_L3 = fStat_L3->GetParameter(1);
  // double Stdv_L3 = fStat_L3->GetParameter(2);
  // /*Assign Fit Statistics to Variables*/
  // double Chi_L3 = fStat_L3->GetChisquare();
  // double NDF_L3 = fStat_L3->GetNDF();
  // double Red_L3 = Chi_L3/NDF_L3;

  // /*Output Results to Terminal*/
  // cout << "=======================" << endl;
  // cout << "!   Finding L3 Peak   !" << endl;
  // cout << "-----------------------" << endl;
  // cout << "Peak Occurs at: " << endl;
  // cout << Peak_L3 << " +/- " << Stdv_L3 << endl;
  // cout << "-----------------------" << endl;
  // cout << "-----Fit Statistics----" << endl;
  // cout << "-----------------------" << endl;
  // cout << "Chi-Sq     |  " << Chi_L3 << endl;
  // cout << "DoF        |  " << NDF_L3 << endl;
  // cout << "Red Chi-Sq |  " << Red_L3 << endl;
  // cout << "=======================" << endl;

  // /*Append Values to Vectors*/
  // // energy.push_back(13.6);
  // Z.push_back(47.);
  // // mean.push_back(Peak_L3);
  // // stdev.push_back(Stdv_L3);

  // /*===================================*/


  /*Output the data to a root file*/
  /*Create a root file to store the data taken from the files*/
  std::string file_root = "OutputFile.root";
  TFile f(("./"+file_root).c_str(),"UPDATE");
  TTree *t = (TTree*)f.Get("t");
  double mean_i, stdev_i, energy_i, Z_i; 

  t->SetBranchAddress("mean",&mean_i);
  t->SetBranchAddress("stdev",&stdev_i);
  t->SetBranchAddress("energy",&energy_i);
  t->SetBranchAddress("Z",&Z_i);

  /*Fill the output file branches with the data from the file*/
  for(int i = 0; i < mean.size(); i++)
    {
      mean_i = mean[i];
      energy_i = energy[i];
      Z_i = Z[i];
      stdev_i = stdev[i];
      t->Fill();
    }

  f.Write();
  f.Close();


	gStyle->SetOptStat(0);
	std::string title = "^{107}Ag Uncalibrated Spectrum";

	TCanvas *c22 = new TCanvas("c22",title.c_str(),750,750);     //Makes canvas large enough for png printing.
		c22->cd();
		c22->SetGridx(1);
		c22->SetGridy(1);
//		c->SetFixedAspectRatio();
	//Use blank histogram to set the parameters of the canvas
	TH1F *blank3 = new TH1F("blank",title.c_str(),10, 0, 2048);
		blank3->GetYaxis()->SetRangeUser(0, 600);
		blank3->GetXaxis()->SetTitle("Bin Number");
		blank3->GetYaxis()->SetTitle("Photon Count");
		blank3->GetYaxis()->SetTitleOffset(1.65);
		blank3->GetXaxis()->SetNdivisions(505);
		blank3->GetYaxis()->SetNdivisions(505);
		blank3->SetLineColor(0);
	blank3->Draw();

	TH1D *hist = new TH1D();
	hist = (TH1D*)agFile->Get("h");
	hist->Draw("SAME");
	fStat_K1->SetLineColor(kRed);
	fStat_K1->Draw("SAME");
	fStat_K2->SetLineColor(kOrange+10);
	fStat_K2->Draw("SAME");
	fStat_L1->SetLineColor(kGreen+3);
	fStat_L1->Draw("SAME");
	fStat_L2->SetLineColor(kBlue);
	fStat_L2->Draw("SAME");
	// fStat_L3->SetLineColor(kViolet);
	// fStat_L3->Draw("SAME");

//	c22->Print("./plots/AgBinnedSpectrum.png");

  c1->Close();
  c2->Close();
  c3->Close();
  c22->Close();



  return 0;
}
