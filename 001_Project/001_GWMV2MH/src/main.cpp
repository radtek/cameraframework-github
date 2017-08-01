/**
 * generated by DCIF CodeGen Version: R2_v2.3.0
 * generated on: Tue Aug 01 13:37:53 CST 2017
 */

#include <thread>

#include <CommonAPI/CommonAPI.hpp>

#include "provides/v0/com/harman/adas/AVMServiceStubImpl.hpp"
#include "provides/v0/com/harman/adas/PASServiceStubImpl.hpp"
#include "provides/v0/com/harman/adas/AdasServiceStubImpl.hpp"

#include <iostream>
#include <memory>
#include <unistd.h>
#include "CAdasManagerGWMv2.h"
#include "MessageForQueue.h"
using namespace std;
using namespace Harman::Adas::AProject::GWMV2MH;

int main(int argc, char **argv) {
	CommonAPI::Runtime::setProperty("LogContext", "adas");
	CommonAPI::Runtime::setProperty("LibraryBase", "adas");

	/*
	 * create the runtime
	 */
	std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
	if(!runtime)
	{
		// Error: could not load runtime
		return 1;
	}
	
	std::string domain = "local";

		std::string PASServiceInst0_prov_connection = "adas";
		std::string PASServiceInst0_prov_instance = "adas.PASServiceInst0";
		std::shared_ptr<v0::com::harman::adas::PASServiceStubImpl> PASServiceInst0_prov_svc = std::make_shared<v0::com::harman::adas::PASServiceStubImpl>();
		runtime->registerService(domain, PASServiceInst0_prov_instance, PASServiceInst0_prov_svc, PASServiceInst0_prov_connection);
	
		std::string AdasServiceInst0_prov_connection = "adas";
		std::string AdasServiceInst0_prov_instance = "adas.AdasServiceInst0";
		std::shared_ptr<v0::com::harman::adas::AdasServiceStubImpl> AdasServiceInst0_prov_svc = std::make_shared<v0::com::harman::adas::AdasServiceStubImpl>();
		runtime->registerService(domain, AdasServiceInst0_prov_instance, AdasServiceInst0_prov_svc, AdasServiceInst0_prov_connection);
	
		std::string AVMServiceInst0_prov_connection = "adas";
		std::string AVMServiceInst0_prov_instance = "adas.AVMServiceInst0";
		std::shared_ptr<v0::com::harman::adas::AVMServiceStubImpl> AVMServiceInst0_prov_svc = std::make_shared<v0::com::harman::adas::AVMServiceStubImpl>();
		runtime->registerService(domain, AVMServiceInst0_prov_instance, AVMServiceInst0_prov_svc, AVMServiceInst0_prov_connection);
	
		CAdasManagerGWMv2::getInstance()->start();
		CAdasManagerGWMv2::getInstance()->pushMessage(new MessageForQueue(0,0, string("456")));
		CAdasManagerGWMv2::getInstance()->join();
    
    while (true) {
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }
    return 0;
}
