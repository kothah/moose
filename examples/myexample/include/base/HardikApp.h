#ifndef HARDIKAPP_H
#define HARDIKAPP_H

#include "MooseApp.h"

class HardikApp;

template <>
InputParameters validParams<HardikApp>();

class HardikApp : public MooseApp{
    public:
        HardikApp(InputParameters parameters);

        virtual ~HardikApp();

        static void registerApps();
        static void registerObjects(Factory & factory);
        static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif // HARDIKAPP_H
