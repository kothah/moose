#include "HardikApp.h"
#include "Moose.h"
#include "Factory.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

#include "HardikConvection.h"
#include "HardikGradConvection.h"
#include "HardikGaussContForcing.h"

#include "HCoupledDirichletBC.h"
#include "HCoupledNeumannBC.h"

template <>
InputParameters
validParams<HardikApp>(){
    InputParameters params = validParams<MooseApp>();
    return params;
}

HardikApp::HardikApp(InputParameters parameters) : MooseApp(parameters){
    srand(processor_id());
    
    Moose::registerObjects(_factory);
    HardikApp::registerObjects(_factory);

    Moose::associateSyntax(_syntax, _action_factory);
    HardikApp::associateSyntax(_syntax, _action_factory);
}

HardikApp::~HardikApp(){}

void HardikApp::registerObjects(Factory & factory){
    // Register any custom objects you have built on the MOOSE Framework
    registerKernel(HardikConvection); // <- registration
    registerKernel(HardikGradConvection); // <- registration

    registerKernel(HardikGaussContForcing); // <- registration
    registerKernel(HCoupledDirichletBC); // <- registration
    registerKernel(HCoupledNeumannBC); // <- registration
}

void HardikApp::registerApps(){
    registerApp(HardikApp);
}

void HardikApp::associateSyntax(Syntax &, ActionFactory &){

}
