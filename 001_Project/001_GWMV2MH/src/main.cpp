/**
 * generated by DCIF CodeGen Version: R2_v2.3.0
 * generated on: Tue Aug 01 13:37:53 CST 2017
 */

#include <thread>

#include <CommonAPI/CommonAPI.hpp>

#include "provides/v0/com/harman/adas/AdasServiceStubImpl.hpp"
#include "provides/v0/com/harman/adas/PASServiceStubImpl.hpp"
#include "provides/v0/com/harman/adas/RvcServiceStubImpl.hpp"
#include "provides/v0/com/harman/adas/AVMServiceStubImpl.hpp"
#include "provides/v0/com/harman/adas/APAServiceStubImpl.hpp"
#include "RvcServiceStubImplGWM.h"

#include <iostream>
#include <memory>
#include <unistd.h>
#include "CAdasManagerGWMv2.h"

#include "RvcMsgQDefine.h"
#include "ReverseSignalReceive.h"

using namespace std;
using namespace Harman::Adas::AProject::GWMV2MH;

int main(int argc, char **argv) {
    #ifdef DLTLOG
        PRINTINIT;
    #endif
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
	std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
	std::string domain = "local";

    std::string AVMServiceInst0_prov_connection = "adas";
    std::string AVMServiceInst0_prov_instance = "adas.AVMServiceInst0";
    std::shared_ptr<v0::com::harman::adas::AVMServiceStubImpl> AVMServiceInst0_prov_svc = std::make_shared<v0::com::harman::adas::AVMServiceStubImpl>();
    runtime->registerService(domain, AVMServiceInst0_prov_instance, AVMServiceInst0_prov_svc, AVMServiceInst0_prov_connection);

    std::string AdasServiceInst0_prov_connection = "adas";
    std::string AdasServiceInst0_prov_instance = "adas.AdasServiceInst0";
    std::shared_ptr<v0::com::harman::adas::AdasServiceStubImpl> AdasServiceInst0_prov_svc = std::make_shared<v0::com::harman::adas::AdasServiceStubImpl>();
    runtime->registerService(domain, AdasServiceInst0_prov_instance, AdasServiceInst0_prov_svc, AdasServiceInst0_prov_connection);

    std::string RvcServiceInst0_prov_connection = "adas";
    std::string RvcServiceInst0_prov_instance = "adas.RvcServiceInst0";
    std::shared_ptr<v0::com::harman::adas::RvcServiceStubImpl> RvcServiceInst0_prov_svc = std::shared_ptr<v0::com::harman::adas::RvcServiceStubImpl>(RvcServiceStubImplGWM::getInstance());
    runtime->registerService(domain, RvcServiceInst0_prov_instance, RvcServiceInst0_prov_svc, RvcServiceInst0_prov_connection);

    std::string PASServiceInst0_prov_connection = "adas";
    std::string PASServiceInst0_prov_instance = "adas.PASServiceInst0";
    std::shared_ptr<v0::com::harman::adas::PASServiceStubImpl> PASServiceInst0_prov_svc = std::make_shared<v0::com::harman::adas::PASServiceStubImpl>();
    runtime->registerService(domain, PASServiceInst0_prov_instance, PASServiceInst0_prov_svc, PASServiceInst0_prov_connection);

    std::string APAServiceInst0_prov_connection = "adas";
    std::string APAServiceInst0_prov_instance = "adas.APAServiceInst0";
    std::shared_ptr<v0::com::harman::adas::APAServiceStubImpl> APAServiceInst0_prov_svc = std::make_shared<v0::com::harman::adas::APAServiceStubImpl>();
    runtime->registerService(domain, APAServiceInst0_prov_instance, APAServiceInst0_prov_svc, APAServiceInst0_prov_connection);

	CAdasManagerGWMv2::getInstance()->start();

    ReverseSignalReceive* receiver = new ReverseSignalReceive();

    while (true) {
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }

    delete receiver;
    receiver = NULL;

    #ifdef DLTLOG
        PRINTDEINIT;
    #endif

    return 0;
}