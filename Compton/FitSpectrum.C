#include <TSpectrum> 

int FitSpectrum()
{

	int i;
	std::string file_name = "Cs_137_Weak_090716_141039.root";
	TFile *f = new TFile(("./data/"+file_name).c_str());
	TH1F *h = new TH1F();
	h = (TH1F*)f->Get("h");
	TCanvas *c1 = new TCanvas();
	h->Draw();

	//------------------------------------------------------------------------------------------------
	
	int nbins = h->GetSize();
//	TCanvas *c2 = new TCanvas();
	TH1F *d1 = new TH1F("d1","",h->GetSize(),0,h->GetSize());

	Float_t * source = new float[h->GetSize()];

	TSpectrum *s = new TSpectrum();
	for (i = 0; i < nbins; i++) source[i]=h->GetBinContent(i + 1);  
//	s->Background(source,nbins,30,TSpectrum::kBackDecreasingWindow,TSpectrum::kBackOrder2,kFALSE,TSpectrum::kBackSmoothing3,kFALSE);
	s->Background(source,nbins,30,TSpectrum::kBackDecreasingWindow,TSpectrum::kBackOrder8,kTRUE,TSpectrum::kBackSmoothing5,kTRUE);     
	for (i = 0; i < nbins; i++) d1->SetBinContent(i + 1,source[i]);  
	d1->SetLineColor(kRed);
	d1->Draw("SAME L");  

	//------------------------------------------------------------------------------------------------

	Double_t a;
	Int_t nfound=0,bin;
	Int_t xmin  = 0;
	Int_t xmax  = nbins;
	Float_t * source = new float[nbins];
	Float_t * dest = new float[nbins];  
	TH1F *d = new TH1F("d","",nbins,xmin,xmax);     

	for (i = 0; i < nbins; i++) source[i] = h->GetBinContent(i + 1);     
	TCanvas *Fit1 = gROOT->GetListOfCanvases()->FindObject("Fit1");
	if (!Fit1) Fit1 = new TCanvas("Fit1","Fit1",10,10,1000,700);
	h->Draw("L");

	TSpectrum *s = new TSpectrum();

	//searching for candidate peaks positions
	nfound = s->SearchHighRes(source, dest, nbins, 2, 0.5, kFALSE, 1, kFALSE, 0);
	Bool_t *FixPos = new Bool_t[nfound];
	Bool_t *FixAmp = new Bool_t[nfound];     

	for(i = 0; i< nfound ; i++)
	{
		FixPos[i] = kFALSE;
		FixAmp[i] = kFALSE;   
	}

	//filling in the initial estimates of the input parameters
	Float_t *PosX = new Float_t[nfound];        
	Float_t *PosY = new Float_t[nfound];
	PosX = s->GetPositionX();
	for (i = 0; i < nfound; i++) 
	{
		a=PosX[i];
		bin = 1 + Int_t(a + 0.5);
		PosY[i] = h->GetBinContent(bin);
	}  

	TSpectrumFit *pfit=new TSpectrumFit(nfound);
	pfit->SetFitParameters(xmin, xmax-1, 1000, 0.1, pfit->kFitOptimChiCounts, pfit->kFitAlphaHalving, pfit->kFitPower2, pfit->kFitTaylorOrderFirst);  
	pfit->SetPeakParameters(2, kFALSE, PosX, (Bool_t *) FixPos, PosY, (Bool_t *) FixAmp);  
	pfit->FitStiefel(source);
	Double_t *CalcPositions = new Double_t[nfound];     
	Double_t *CalcAmplitudes = new Double_t[nfound];        
	CalcPositions=pfit->GetPositions();
	CalcAmplitudes=pfit->GetAmplitudes();  

	for (i = 0; i < nbins; i++) d->SetBinContent(i + 1,source[i]);

	d->SetLineColor(kRed);  
	d->Draw("SAME L"); 

	for (i = 0; i < nfound; i++) 
	{
		a=CalcPositions[i];
		bin = 1 + Int_t(a + 0.5);               
		PosX[i] = d->GetBinCenter(bin);
		PosY[i] = d->GetBinContent(bin);
	}

	TPolyMarker * pm = (TPolyMarker*)h->GetListOfFunctions()->FindObject("TPolyMarker");
	if (pm) 
	{
		h->GetListOfFunctions()->Remove(pm);
		delete pm;
	}

	pm = new TPolyMarker(nfound, PosX, PosY);
	h->GetListOfFunctions()->Add(pm);
	pm->SetMarkerStyle(23);
	pm->SetMarkerColor(kRed);
	pm->SetMarkerSize(1);	

	return 0;
}
