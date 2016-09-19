int GetCsPeaks(
	       TString infile = "data/Cs_137_Weak_090716_141039.root"
)
{
  TFile *csFile = TFile::Open(infile); 
  TH1D *csHraw = new TH1D();
  csHraw = (TH1D*)csFile->Get("h");
  TCanvas *c1 = new TCanvas();
  csHraw->Draw();
  vector<double> mean, stdev, energy;

  /*========Cs-137 32 keV Peak=========*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *csHist_032 = (TH1D*)h->Clone("csHraw");
  /*Define Spectrum Fit Function*/
  TF1 *fSpec_032 = new TF1("fSpec_032", "gaus+pol2(3)", 20., 100.);
  /*Estimate Parameters of Fit*/
  fSpec_032->SetParameters(100, 75, 2, 200, 1);
  TCanvas *c2 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  csHist_032->Fit("fSpec_032", "Q", "", 20., 100.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_032 = csHist_032->GetFunction("fSpec_032");

  /*Assign Fit Parameters to Variables*/
  double Peak_032 = fStat_032->GetParameter(1);
  double Stdv_032 = fStat_032->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_032 = fStat_032->GetChisquare();
  double NDF_032 = fStat_032->GetNDF();
  double Red_032 = Chi_032/NDF_032;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!                     !" << endl;
  cout << "!       Cs-137        !" << endl;
  cout << "!                     !" << endl;
  cout << "=======================" << endl;

  cout << "=======================" << endl;
  cout << "!!Finding 32 keV Peak!!" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_032 << " +/- " << Stdv_032 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_032 << endl;
  cout << "DoF        |  " << NDF_032 << endl;
  cout << "Red Chi-Sq |  " << Red_032 << endl;
  cout << "=======================" << endl;

  /*Append Values to Vectors*/
  energy.push_back(32.0);
  mean.push_back(Peak_032);
  stdev.push_back(Stdv_032);

  /*===================================*/

  /*======Cs-137 661.6 keV Peak======*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *csHist_662 = (TH1D*)h->Clone("csHraw");
  /*Define Spectrum Fit*/
  TF1 *fSpec_662 = new TF1("fSpec_662", "gaus+pol0(3)+expo(4)", 650., 2000.);
  /*Estimate Parameters of Fit Function*/
  fSpec_662->SetParNames("Strength", "Mean","Sigma", "Back1", "Back2", "Back3"); 
  fSpec_662->SetParameters(100, 1000, 2, 50, 0, 0);
  TCanvas *c3 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  csHist_662->Fit("fSpec_662", "Q", "", 650., 2000.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_662 = csHist_662->GetFunction("fSpec_662");

  /*Assign Fit Parameters to Variables*/
  double Peak_662 = fStat_662->GetParameter(1);
  double Stdv_662 = fStat_662->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_662 = fStat_662->GetChisquare();
  double NDF_662 = fStat_662->GetNDF();
  double Red_662 = Chi_662/NDF_662;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!Finding 661.6 keV Peak!" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_662 << " +/- " << Stdv_662 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_662 << endl;
  cout << "DoF        |  " << NDF_662 << endl;
  cout << "Red Chi-Sq |  " << Red_662 << endl;
  cout << "=======================" << endl;
  
  /*Append Values to Vectors*/
  energy.push_back(661.6);
  mean.push_back(Peak_662);
  stdev.push_back(Stdv_662);

  /*===================================*/

  /*Output the data to a root file*/
  /*Create a root file to store the data taken from the files*/
  std::string file_root = "OutputFile.root";
  TFile f(("./"+file_root).c_str(),"UPDATE");
  TTree *t = (TTree*)f.Get("t");
  double mean_i, stdev_i, energy_i; 

  t->SetBranchAddress("mean",&mean_i);
  t->SetBranchAddress("stdev",&stdev_i);
  t->SetBranchAddress("energy",&energy_i);

  /*Fill the output file branches with the data from the file*/
  for(int i = 0; i < mean.size(); i++)
    {
      mean_i = mean[i];
      energy_i = energy[i];
      stdev_i = stdev[i];
      t->Fill();
    }

  f.Write();
  f.Close();


	gStyle->SetOptStat(0);
	std::string title = "^{137}Cs Uncalibrated Spectrum";

	TCanvas *c22 = new TCanvas("c22",title.c_str(),750,750);     //Makes canvas large enough for png printing.
		c22->cd();
		c22->SetGridx(1);
		c22->SetGridy(1);
//		c->SetFixedAspectRatio();
	//Use blank histogram to set the parameters of the canvas
	TH1F *blank3 = new TH1F("blank",title.c_str(),10, 0, 2048);
		blank3->GetYaxis()->SetRangeUser(0, 2600);
		blank3->GetXaxis()->SetTitle("Bin Number");
		blank3->GetYaxis()->SetTitle("Photon Count");
		blank3->GetYaxis()->SetTitleOffset(1.65);
		blank3->GetXaxis()->SetNdivisions(505);
		blank3->GetYaxis()->SetNdivisions(505);
		blank3->SetLineColor(0);
	blank3->Draw();

	TH1D *hist = new TH1D();
	hist = (TH1D*)csFile->Get("h");
	hist->Draw("SAME");
	fStat_662->SetLineColor(kBlue);
	fStat_662->Draw("SAME");
	fStat_032->SetLineColor(kRed);
	fStat_032->Draw("SAME");

//	c22->Print("./plots/CsBinnedSpectrum.png");

  c1->Close();
  c2->Close();
  c3->Close();
  c22->Close();



  return 0;
}
