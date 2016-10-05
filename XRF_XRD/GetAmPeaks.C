int GetAmPeaks(
	       TString infile = "data/Am_241_100516_132724.root"
)
{
  TFile *amFile = TFile::Open(infile); 
  TH1D *amHraw = new TH1D();
  amHraw = (TH1D*)amFile->Get("h");
  TCanvas *c1 = new TCanvas();
  amHraw->Draw();
  vector<double> mean, stdev, energy;

  /*========Am-241 13.6 keV Peak=========*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *amHist_013 = (TH1D*)h->Clone("amHraw");
  /*Define Spectrum Fit Function*/
  TF1 *fSpec_013 = new TF1("fSpec_013", "gaus", 375., 400.);
  /*Estimate Parameters of Fit*/
  fSpec_013->SetParameters(400, 75, 2);
  TCanvas *c2 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  amHist_013->Fit("fSpec_013", "Q", "", 375., 400.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_013 = amHist_013->GetFunction("fSpec_013");

  /*Assign Fit Parameters to Variables*/
  double Peak_013 = fStat_013->GetParameter(1);
  double Stdv_013 = fStat_013->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_013 = fStat_013->GetChisquare();
  double NDF_013 = fStat_013->GetNDF();
  double Red_013 = Chi_013/NDF_013;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!                     !" << endl;
  cout << "!       Am-241        !" << endl;
  cout << "!                     !" << endl;
  cout << "=======================" << endl;

  cout << "=======================" << endl;
  cout << "!Finding 13.6 keV Peak!" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_013 << " +/- " << Stdv_013 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_013 << endl;
  cout << "DoF        |  " << NDF_013 << endl;
  cout << "Red Chi-Sq |  " << Red_013 << endl;
  cout << "=======================" << endl;

  /*Append Values to Vectors*/
  energy.push_back(13.6);
  mean.push_back(Peak_013);
  stdev.push_back(Stdv_013);

  /*===================================*/

  /*========Am-241 17.8 keV Peak=======*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *amHist_017 = (TH1D*)h->Clone("amHraw");
  /*Define Spectrum Fit*/
  TF1 *fSpec_017 = new TF1("fSpec_017", "gaus", 440., 470.);
  /*Estimate Parameters of Fit Function*/
  // fSpec_017->SetParNames("Strength", "Mean","Sigma", "Back1", "Back2", "Back3"); 
  fSpec_017->SetParameters(450., 1000, 2);
  TCanvas *c3 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  amHist_017->Fit("fSpec_017", "Q", "", 440., 470.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_017 = amHist_017->GetFunction("fSpec_017");

  /*Assign Fit Parameters to Variables*/
  double Peak_017 = fStat_017->GetParameter(1);
  double Stdv_017 = fStat_017->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_017 = fStat_017->GetChisquare();
  double NDF_017 = fStat_017->GetNDF();
  double Red_017 = Chi_017/NDF_017;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!Finding 17.8 keV Peak!" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_017 << " +/- " << Stdv_017 << endl;
  cout << "-----------------------" << endl;
  cout << "-----Fit Statistics----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_017 << endl;
  cout << "DoF        |  " << NDF_017 << endl;
  cout << "Red Chi-Sq |  " << Red_017 << endl;
  cout << "=======================" << endl;
  
  /*Append Values to Vectors*/
  energy.push_back(17.8);
  mean.push_back(Peak_017);
  stdev.push_back(Stdv_017);

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
	std::string title = "^{241}Am Uncalibrated Spectrum";

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
	hist = (TH1D*)amFile->Get("h");
	hist->Draw("SAME");
	fStat_017->SetLineColor(kBlue);
	fStat_017->Draw("SAME");
	fStat_013->SetLineColor(kRed);
	fStat_013->Draw("SAME");

//	c22->Print("./plots/CsBinnedSpectrum.png");

  c1->Close();
  c2->Close();
  c3->Close();
  c22->Close();



  return 0;
}
