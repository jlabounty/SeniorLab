int FitGaussian()
{

	//Open file and get the attached histogram for the data
	std::string file_name = "Cs_137_Weak_090716_141039.root";
	//std::string file_name = "Co_60_Weak_090716_140110.root";
	TFile *f = new TFile(("./data/"+file_name).c_str());
	TH1F *hraw = new TH1F();
	hraw = (TH1F*)f->Get("h");
	TCanvas *c1 = new TCanvas();
	hraw->Draw();

	//Open file and get the attached histogram for the background
	std::string file_name_back = "Cs_137_Weak_090716_141039.root";
	//std::string file_name = "Co_60_Weak_090716_140110.root";
	TFile *fback = new TFile(("./data/"+file_name_back).c_str());
	TH1F *hback = new TH1F();
	hback = (TH1F*)f->Get("h");
	TCanvas *c2 = new TCanvas();
	hback->Draw();

	//Create a new histogram which is the data w/o background
	TCanvas *c3 = new TCanvas();
	TH1F *h = (TH1F*)h->Clone("hraw");
//	h->Add(hback,-1);
	h->Draw();

	//Fit the histogram to a gaussian
        TF1 *fit1 = new TF1("fit1","gaus",650,2000);
        h->Fit("fit1","R");

	


	return 0;
}
