

double get_epsilon(double mean);

int GetCsPeaks_Angle(
	      //TString infile = "data/Cs_137_Angle_000_AlScatter_091416_124734.root",
	      TString infile = "data/Cs_137_Angle_000_NoScatter_091416_124126.root",
	      double mean_est = 661.6,
	      double angle = 90,
	      double fit_low = 650.,
	      double fit_high = 2000.
)
{
  TFile *csFile = TFile::Open(infile); 
  TH1D *csHraw = new TH1D();
  csHraw = (TH1D*)csFile->Get("h");
  TCanvas *c1 = new TCanvas();
  csHraw->Draw();

  vector<double> mean, stdev, energy;

  /*Output Results to Terminal*/
  cout << "=======================" << endl;
  cout << "!                     !" << endl;
  cout << "!       Cs-137        !" << endl;
  cout << "!                     !" << endl;
  cout << "=======================" << endl;

  /*===================================*/

  /*======Cs-137 661.6 keV Peak======*/
  /*Clone Histogram of Spectrum from Data File*/
  TH1D *csHist_662 = (TH1D*)h->Clone("csHraw");
  /*Define Spectrum Fit*/
  TF1 *fSpec_662 = new TF1("fSpec_662", "gaus+pol0(3)+expo(4)", fit_low, fit_high);
  /*Estimate Parameters of Fit Function*/
  fSpec_662->SetParNames("Strength", "Mean","Sigma", "Back1", "Back2", "Back3"); 
  fSpec_662->SetParameters(100, mean_est, 2, 50, 0, 0);
  TCanvas *c3 = new TCanvas();
  /*Fit Pre-Defined Function to Spectrum*/
  csHist_662->Fit("fSpec_662", "Q", "", fit_low, fit_high);

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
  double mean_energy = 0.000170654*(Peak_662**2) + 0.600313*Peak_662 - 5.13889;
  energy.push_back(mean_energy);
  mean.push_back(Peak_662);
  stdev.push_back(Stdv_662);

//*************************************************************************

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
	Double_t param[6];
	fSpec_662->GetParameters(param);
	TF1 *fSignal = new TF1("fSignal","gaus",0.,2048.);
		fSignal->SetLineColor(kGreen);
		fSignal->SetParameters(param);
	fSignal->Draw("SAME");
	Double_t sumundercurve;
	double peaktototal = get_peak2total(mean_energy);
	sumundercurve = (fSignal->Integral(0,2048) ) / peaktototal;
	cout << "sumundercurve = " << sumundercurve << endl;

//	c22->Print("./plots/CsBinnedSpectrum.png");

	TCanvas *c2 = new TCanvas();

	TH1F *blank2 = new TH1F("blank2","^{137}Cs Calibrated Spectrum",10, 0, 1000);
		blank2->GetYaxis()->SetRangeUser(0, 2800);
		blank2->GetXaxis()->SetTitle("Energy (keV)");
		blank2->GetYaxis()->SetTitle("Photon Count");
		blank2->GetYaxis()->SetTitleOffset(1.65);
		blank2->GetXaxis()->SetNdivisions(505);
		blank2->GetYaxis()->SetNdivisions(505);
		blank2->SetLineColor(0);
	blank2->Draw();

	TTree *t2 = (TTree*)csFile->Get("t");	
	t2->Draw("Count:Bin:Time","","goff");
	vector<double> v_count, v_bin;
	for(int i = 0; i < t2->GetEntries(); i++)
	{
	  double x = t2->GetV2()[i];
		v_count.push_back(t2->GetV1()[i]);
		// v_bin.push_back( calibfit->Eval( t2->GetV2()[i] ) );
		v_bin.push_back( -5.13889 + 0.600313*x + 0.000170654*x**2 );

	}
	TGraph *gr1 = new TGraph(v_count.size(), &(v_bin[0]), &(v_count[0]));
	gr1->Draw("p SAME");

//	c2->Print("./plots/CsCalibSpectrum.png");

  /*===================================*/

	//Calculation of dsigma / dOmega
	double epsilon = get_epsilon(mean_energy)*100;			//Correction to dOmega bc of detector efficiency. x100 because percentage.
		cout << "mean energy = " << mean_energy << endl;
		cout << "epsilon = " << epsilon << endl;
	double Y_theta = sumundercurve/(t->GetV3()[0]*epsilon);			//Photons recieved with scatterer at angle theta
		cout << "Y_theta = " << Y_theta << endl;
	double r_SourceToScat = 21.5*2.54;				//Distance from detector to scattering point
	double r_SourceToDet = 32.6*2.54;				//Distance from source to dectector.
	double Area_detector = 45.6;					//cm^2
/**/	double N_gamma = 902.049 / (get_peak2total(661.6));		//Number of photons which impact the detector per second with no scattering
	double flux = N_gamma/Area_detector;				//Flux. Counts/(cm^2 * s)
	double dOmega = Area_detector / TMath::Power(r_SourceToDet,2);	//Angle subtended by detector. Crystal area / r^2
	double d_scatter = 2.5*2.54;					//Diameter of the scatterer
	double h_scatter = (6.0 + (13./16.))*2.54;			//Height of the scatterer
	double rho_Al = 2.7;						//Density of Al (g/cm^3)
	double A_Al = 27.0;						//Atomic weight of Al
	double Z_Al = 13.0;						//Number of protons/electrons in Al atom
	double AvoNum = TMath::Na();					//Avogadros Number
	double N_e;							//Number of electrons in the path of beam
	double dsigma_dOmega;						//Angular Dependance on scattering probability

	double flux_target = (flux / (get_epsilon(661.6)*100))*TMath::Power((r_SourceToDet / r_SourceToScat),2);	//photons/(cm^2 *s)

	N_e = TMath::Pi()*TMath::Power((d_scatter / 2.0),2)*h_scatter*rho_Al*(AvoNum / A_Al)*Z_Al; //electrons

//	dsigma_dOmega = Y_theta / (dOmega * N_gamma * N_e * epsilon);
//	dsigma_dOmega = Y_theta / (dOmega * N_gamma * N_e * flux_target);
	dsigma_dOmega = Y_theta / (dOmega * N_e * flux_target);

	cout << "dsigma_dOmega: " << dsigma_dOmega << endl;

	//Calculation of error in dsigma_dOmega 
	double err_Y_theta = 0.05*Y_theta;
	double err_r_SourceToScat = 0.1*2.54;
	double err_r_SourceToDet = 0.1*2.54;
	double err_Area_detector = Area_detector*TMath::Sqrt(TMath::Power((err_r_SourceToDet/ r_SourceToDet),2) + TMath::Power((err_r_SourceToScat / r_SourceToScat),2));
	double err_N_gamma = 0.05*N_gamma;
	double err_flux = flux*TMath::Sqrt(TMath::Power(( err_Area_detector / Area_detector ),2) + TMath::Power(( err_N_gamma / N_gamma  ),2));
	double err_dOmega = dOmega*TMath::Sqrt(TMath::Power(( err_Area_detector / Area_detector ),2) + 2.0*TMath::Power(( err_r_SourceToScat / r_SourceToScat  ),2));
	double err_epsilon = 0.01*epsilon;
	double err_d_scatter = 0.1*2.54;
	double err_h_scatter = 0.5*2.54;

	double err_flux_target = flux_target*TMath::Sqrt( TMath::Power(( err_flux / flux ),2) + TMath::Power(( err_epsilon / epsilon ),2) * 2.0*TMath::Power(( err_r_SourceToDet / r_SourceToDet ),2) * 2.0*TMath::Power(( err_r_SourceToScat / r_SourceToScat ),2));

	double err_N_e = N_e = TMath::Sqrt(2*TMath::Power(( err_d_scatter / d_scatter ),2) + TMath::Power(( err_h_scatter / h_scatter  ),2));
	double err_dsigma_dOmega = dsigma_dOmega*TMath::Sqrt(TMath::Power(( err_Y_theta / Y_theta ),2) + TMath::Power(( err_dOmega / dOmega  ),2) * TMath::Power(( err_N_e / N_e  ),2)* TMath::Power(( err_flux_target / flux_target ),2));

	cout << "Error: " << err_dsigma_dOmega << endl;
  /*===================================*/

  /*Output the data to a root file*/
  /*Create a root file to store the data taken from the files*/
  std::string file_root = "OutputFile_PeakShift.root";
  TFile f(("./"+file_root).c_str(),"UPDATE");
  TTree *t = (TTree*)f.Get("t");
  double mean_i, stdev_i, energy_i; 

  t->SetBranchAddress("mean",&mean_i);
  t->SetBranchAddress("stdev",&stdev_i);
  t->SetBranchAddress("energy",&energy_i);
  t->SetBranchAddress("angle",&angle);
  t->SetBranchAddress("integral",&sumundercurve);
  t->SetBranchAddress("dsigma_dOmega",&dsigma_dOmega);
  t->SetBranchAddress("err_dsigma_dOmega",&err_dsigma_dOmega);

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
	c22->Close();
	c3->Close();

  return 0;
}

double get_epsilon(double mean)
{

  double keV = mean / 1000.;
  double epsilon = -0.000145367/(keV**2) + 0.00175559/keV + 0.0038941; 

	return epsilon;
}

double get_peak2total(double mean)
{

  double keV = mean / 1000.;
  double peak2total = 0.00416806/(keV**3) - 0.0720311/(keV**2) + 0.423607/keV + 0.0654975;

	return peak2total;
}
