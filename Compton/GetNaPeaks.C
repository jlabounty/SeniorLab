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

  TH1D *naHist_511 = (TH1D*)h->Clone("naHraw");
  TF1 *fSpec_511 = new TF1("fSpec_511", "gaus+pol0(3)+expo(4)", 500., 1000.);
  fSpec_511->SetParameters(100, 700, 2, 50, 0, 0);
  TCanvas *c2 = new TCanvas();
  naHist_511->Fit("fSpec_511", "Q", "", 500., 1000.);

  TF1 *fGausStat_511 = naHist_511->GetFunction("fSpec_511");

  double Chi_511 = fGausStat_511->GetChisquare();
  double NDF_511 = fGausStat_511->GetNDF();
  double Red_511 = Chi_511/NDF_511;

  cout << "=======================" << endl;
  cout << "!                     !" << endl;
  cout << "!        Na-22        !" << endl;
  cout << "!                     !" << endl;
  cout << "=======================" << endl;

  cout << "=======================" << endl;
  cout << "!Finding 511 keV Peak!" << endl;
  cout << "-----------------------" << endl;
  double Peak_511 = fGausStat_511->GetParameter(1);
  double Stdv_511 = fGausStat_511->GetParameter(2);
  cout << "Peak Occurs at: " << endl;
  cout << Peak_511 << " +/- " << Stdv_511 << endl;
  cout << "-----------------------" << endl;
  cout << "----Fit Statistics-----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Squared: " << Chi_511 << endl;
  cout << "Degrees of Freedom: " << NDF_511 << endl;
  cout << "Reduced Chi-Squared: " << Red_511 << endl;
  cout << "=======================" << endl;

  /*========Na-22 1274 keV Peak=========*/

  TH1D *naHist_1274 = (TH1D*)h->Clone("naHraw");
  TF1 *fSpec_1274 = new TF1("fSpec_1274", "gaus+pol0(3)+expo(4)", 1200., 1700.);
  fSpec_1274->SetParameters(100, 1500, 2, 50, 0, 0);
  TCanvas *c2 = new TCanvas();
  naHist_1274->Fit("fSpec_1274", "Q", "", 1200., 1700.);

  TF1 *fGausStat_1274 = naHist_1274->GetFunction("fSpec_1274");

  double Chi_1274 = fGausStat_1274->GetChisquare();
  double NDF_1274 = fGausStat_1274->GetNDF();
  double Red_1274 = Chi_1274/NDF_1274;

  cout << "=======================" << endl;
  cout << "!Finding 1274 keV Peak!" << endl;
  cout << "-----------------------" << endl;
  double Peak_1274 = fGausStat_1274->GetParameter(1);
  double Stdv_1274 = fGausStat_1274->GetParameter(2);
  cout << "Peak Occurs at: " << endl;
  cout << Peak_1274 << " +/- " << Stdv_1274 << endl;
  cout << "-----------------------" << endl;
  cout << "----Fit Statistics-----" << endl;
  cout << "-----------------------" << endl;
  cout << "Chi-Squared: " << Chi_1274 << endl;
  cout << "Degrees of Freedom: " << NDF_1274 << endl;
  cout << "Reduced Chi-Squared: " << Red_1274 << endl;
  cout << "=======================" << endl;

  /*===================================*/

  energy.push_back(511.);
  mean.push_back(Peak_511);
  stdev.push_back(Stdv_511);
  energy.push_back(1274.);
  mean.push_back(Peak_1274);
  stdev.push_back(Stdv_1274);


  //Output the data to a root file                                                   
  //Create a root file to store the data taken from the files                        
  std::string file_root = "OutputFile.root";
  TFile f(("./"+file_root).c_str(),"UPDATE");
//  TTree *t = new TTree("t","Peaks of Functions and their Standard Deviations");
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

  return 0;
}
