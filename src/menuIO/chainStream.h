/* -*- C++ -*- */
/***********
Sept. 2014 Rui Azevedo - ruihfazevedo(@rrob@)gmail.com

scan a chain of several input streams to provide input

***/

#ifndef RSITE_CHAINSTREAM_DEF_H
  #define RSITE_CHAINSTREAM_DEF_H

  #include "../menuDefs.h"

  namespace Menu {

  template<int N>
  class chainStream:public menuIn {
    public:
    menuIn* const* const inputs;
    chainStream(menuIn* const* inputs):inputs(inputs) {}
    int available(void) override {
      for(int n=0;n<N;n++) {
        int r=inputs[n]->available();
        if (r) return r;
      }
      return 0;
    }
    int peek(void) override {
      for(int n=0;n<N;n++) {
        int r=inputs[n]->peek();
        if (r>=0) return r;
      }
      return -1;
    }
    int read(void) override {
      for(int n=0;n<N;n++) {
        int r=inputs[n]->read();
        if (r>=0) return r;
      }
      return -1;
    }
    void flush(void) override {
      for(int n=0;n<N;n++) inputs[n]->flush();
    }
    size_t write(uint8_t v) override {
      for(int n=0;n<N;n++) inputs[n]->write(v);
      return 1;
    }
  };


  }//namespace Menu

#endif
