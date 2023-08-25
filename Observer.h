#pragma once

#include <vector>

using namespace std;

class Observer
{
public:
    virtual void update(string message) = 0;
};

class Subject
{
    string m_message;
    vector<Observer*> m_views;
public:
    Subject(string m) : m_message(m) {}

    void attach(Observer* obs)
    {
        m_views.push_back(obs);
    }
    void set_val(string message)
    {
        m_message = message;
        notify();
    }
    void notify()
    {
        for (int i = 0; i < m_views.size(); ++i)
            m_views[i]->update(m_message);
    }
};