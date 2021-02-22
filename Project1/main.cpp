#include <iostream>
#include <chrono>
#include "BaseStation.h"
#include "Channel.h"
#include "WirelessNetwork.h"
#include "Channel.h"
#include "logger.h"
#include "Simulator.h"
#include <memory>
using namespace std;

int main()
{
	int k = 10;
	auto logger_ = new Logger();
	auto wifi_ = new WirelessNetwork(k);
	auto channel_ = new Channel();
	//-------------------------------------- 10 nadajniki * 10 symulacji = 100 ziaren + 1 ziarno TER = 101 ziaren-------------------------
	int seed = 123;
	auto generator = Generators(seed);
	vector<int> cgpk_kernels;
	vector<int> ctpk_kernels;
	vector<int> r_kernels;
	vector<int> t_kernels;
	int ter_kernel;

	//CGP
	generator.GenerateKernels(100, cgpk_kernels);
	generator.ImportKernelsToFile(cgpk_kernels, "cgpk_kernels.txt");


	//CTP
	generator.GenerateKernels(100, ctpk_kernels);
	generator.ImportKernelsToFile(ctpk_kernels, "ctpk_kernels.txt");


	//R
	generator.GenerateKernels(100, r_kernels);
	generator.ImportKernelsToFile(r_kernels, "r_kernels.txt");


	//T
	generator.GenerateKernels(100, t_kernels);
	//generator.ImportKernelsToFile(t_kernels, "t_kernels.txt");

	//TER
	generator.GenerateKernels(ter_kernel);
	generator.ImportKernelsToFile(ter_kernel, "ter_kernel.txt");

	for (int i = 0; i < k; i++)
	{
		double kernel = cgpk_kernels.at(i+8);
		wifi_->basestation_[i]->SetCgpkKernel(kernel);
		wifi_->basestation_[i]->CreateCgpkGenerator();
		wifi_->basestation_[i]->Generate_CGP();
	}

	for (int i = 0; i < k; i++)
	{
		double kernel = ctpk_kernels.at(i+8);
		wifi_->basestation_[i]->SetCtpkKernel(kernel);
		wifi_->basestation_[i]->CreateCtpkGenerator();
		wifi_->basestation_[i]->Generate_CTP();
	}

	for (int i = 0; i < k; i++)
	{
		double kernel = r_kernels.at(i+8);
		wifi_->basestation_[i]->SetRKernel(kernel);
		wifi_->basestation_[i]->CreateeRGenerator();

	}

	for (int i = 0; i < k; i++)
	{
		double kernel = t_kernels.at(i + 8);
		wifi_->basestation_[i]->SetTKernel(kernel);
		wifi_->basestation_[i]->CreateeTGenerator();
	}
	double czas;
	wifi_->SetTerKernel(ter_kernel);
	wifi_->CreateTerGenerator();
	std::cout << "Write max time of simulation: ";
	std::cin >> czas;
	std::cout << endl;
	Simulator simulator = Simulator(wifi_, channel_,logger_);
	simulator.M1( czas);

	system("Pause");

	return 0;
}