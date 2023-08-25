#pragma once

#include "CLI.h"
#include "Observer.h"

class View : public Observer {
    CLI* cli;
public:
    View(Subject* model, CLI c)
    {
        model->attach(this);
        cli = &c;
    }
    /* virtual */void update(string message) override {
        cout << message << endl;
    }
};
