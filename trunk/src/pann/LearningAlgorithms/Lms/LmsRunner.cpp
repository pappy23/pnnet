//LmsRunner.cpp

#include "LmsRunner.h"

namespace pann
{
    Runner* LmsFeedforwardRunner::self = 0;
    Runner* LmsBackpropagationRunner::self = 0;

    LmsFeedforwardRunner::LmsFeedforwardRunner()
    {
    } //LmsFeedforwardRunner

    LmsFeedforwardRunner::~LmsFeedforwardRunner()
    {
    } //~LmsFeedforwardRunner

    Runner*
    LmsFeedforwardRunner::Instance()
    {
        if(!self)
            self = new LmsFeedforwardRunner();

        return self;
    } //Instance

    void
    LmsFeedforwardRunner::run(Neuron* _neuron)
    {
        if(!_neuron->learningHint.is(LmsAttributes::LMS))
        {
            _neuron->learningHint.erase();
            _neuron->learningHint[LmsAttributes::LMS] = 1.0;
        }

        //do something useful

    } //run

    RunDirection
    LmsFeedforwardRunner::getDirection()
    {
        return ForwardRun;
    } //getDirection

    LmsBackpropagationRunner::LmsBackpropagationRunner()
    {
    } //LmsBackpropagationRunner

    LmsBackpropagationRunner::~LmsBackpropagationRunner()
    {
    } //~LmsBackpropagationRunner
    
    Runner* 
    LmsBackpropagationRunner::Instance()
    {
        if(!self)
            self = new LmsBackpropagationRunner();

        return self;
    } //Instance

    void
    LmsBackpropagationRunner::run(Neuron* _neuron)
    {
        if(!_neuron->learningHint.is(LmsAttributes::LMS))
            throw E<Exception::ObjectNotFound>()<<"LmsBackpropagationRunner::run(): Feedforward run wasn't made\n";

        //do something useful
        
    } //run

    RunDirection
    LmsBackpropagationRunner::getDirection()
    {
        return BackwardRun;
    } //getDirection

}; //pann

