#include "HardikApp.h"
#include "Moose.h"
#include "Factory.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

#include "HardikConvection.h"
#include "HardikGradConvection.h"
#include "HardikGaussContForcing.h"
#include "HardikCoefDiffusion.h"

#include "HCoupledDirichletBC.h"
#include "HCoupledNeumannBC.h"
#include "HardikTimeDerivative.h"
#include "HardikIC.h"
#include "HardikMaterial.h"
#include "HStatefulMaterial.h"
#include "HardikMaterialDiffusion.h"
#include "HardikNewConvection.h"

#include "HardikAux.h"
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
    registerKernel(HardikCoefDiffusion); // <- registration
    registerKernel(HardikTimeDerivative); // <- registration
    registerKernel(HardikIC); // <- registration
    registerKernel(HardikMaterial); // <- registration
    
    registerKernel(HardikMaterialDiffusion); // <- registration
    registerKernel(HardikNewConvection); // <- registration

    registerKernel(HStatefulMaterial); // <- registration
    registerKernel(HardikAux); // <- registration
}

void HardikApp::registerApps(){
    registerApp(HardikApp);
}

void HardikApp::associateSyntax(Syntax &, ActionFactory &){

}
