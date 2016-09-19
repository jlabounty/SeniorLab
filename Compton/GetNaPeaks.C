int GetNaPeaks(
	       TString infile = "data/Na_22_Weak_091216_143229.root"
)
{
  TFile *naFile = TFile::Open(infile); 
  TH1D *naHraw = new TH1D();
  naHraw = (TH1D*)naFile->Get("h");
  TCanvas *c1 = new TCanvas();
  naHraw->Draw();

  vector<double> energy, mean, stdev;

  /*========Na-22 511 keV e-e+ Peak=========*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *naHist_511 = (TH1D*)h->Clone("naHraw");
  /*Define Spectrum Fit Function*/
  TF1 *fSpec_511 = new TF1("fSpec_511", "gaus+pol0(3)+expo(4)", 500., 1000.);
  /*Estimate Parameters of Fit*/
  fSpec_511->SetParameters(100, 700, 2, 50, 0, 0);
  TCanvas *c2 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  naHist_511->Fit("fSpec_511", "Q", "", 500., 1000.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_511 = naHist_511->GetFunction("fSpec_511");

  /*Assign Fit Parameters to Variables*/
  double Peak_511 = fStat_511->GetParameter(1);
  double Stdv_511 = fStat_511->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_511 = fStat_511->GetChisquare();
  double NDF_511 = fStat_511->GetNDF();
  double Red_511 = Chi_511/NDF_511;

  cout << "=======================" << endl;
  cout << "!                     !" << endl;
  cout << "!        Na-22        !" << endl;
  cout << "!                     !" << endl;
  cout << "=======================" << endl;

  cout << "=======================" << endl;
  cout << "!Finding 511 keV Peak!" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_511 << " +/- " << Stdv_511 << endl;
  cout << "-----------------------" << endl;
  cout << "----Fit Statistics-----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_511 << endl;
  cout << "DoF        |  " << NDF_511 << endl;
  cout << "Red Chi-Sq |  " << Red_511 << endl;
  cout << "=======================" << endl;

  /*========Na-22 1274 keV Peak=========*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *naHist_1274 = (TH1D*)h->Clone("naHraw");
  /*Define Spectrum Fit Function*/
  TF1 *fSpec_1274 = new TF1("fSpec_1274", "gaus+pol0(3)+expo(4)", 1200., 1700.);
  /*Estimate Parameters of Fit*/
  fSpec_1274->SetParameters(100, 1500, 2, 50, 0, 0);
  TCanvas *c3 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  naHist_1274->Fit("fSpec_1274", "Q", "", 1200., 1700.);

  /*Obtain Fit Function from Histogram*/
  TF1 *fStat_1274 = naHist_1274->GetFunction("fSpec_1274");

  /*Assign Fit Parameters to Variables*/
  double Peak_1274 = fStat_1274->GetParameter(1);
  double Stdv_1274 = fStat_1274->GetParameter(2);
  /*Assign Fit Statistics to Variables*/
  double Chi_1274 = fStat_1274->GetChisquare();
  double NDF_1274 = fStat_1274->GetNDF();
  double Red_1274 = Chi_1274/NDF_1274;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!Finding 1274 keV Peak!" << endl;
  cout << "-----------------------" << endl;
  cout << "Peak Occurs at: " << endl;
  cout << Peak_1274 << " +/- " << Stdv_1274 << endl;
  cout << "-----------------------" << endl;
  cout << "----Fit Statistics-----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Sq     |  " << Chi_1274 << endl;
  cout << "DoF        |  " << NDF_1274 << endl;
  cout << "Red Chi-Sq |  " << Red_1274 << endl;
  cout << "=======================" << endl;

  /*Append Values to Vectors*/
  energy.push_back(511.);
  mean.push_back(Peak_511);
  stdev.push_back(Stdv_511);
  energy.push_back(1274.);
  mean.push_back(Peak_1274);
  stdev.push_back(Stdv_1274);

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

  c1->Close();
  c2->Close();
  c3->Close();

  return 0;
}
