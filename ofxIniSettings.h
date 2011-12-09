#ifndef OFX_INISETTINGS_H
#define OFX_INISETTINGS_H

#include <fstream>
#include <iostream>
#include <map>

#include "ofMain.h"
#include "ofxExtras.h"

class ofxIniSettings {
public:

    ofxIniSettings() {}
    ofxIniSettings(string filename) { load(filename); }

    bool load(string filename, bool clearFirst=false, bool setAsOutputFile=false); // you can call multiple times with different files, incremental
    bool has(string key) { return keys[key]!=""; };
    void clear();

    map<string,string> keys;
    string outputFilename;

    //getters
    int get(string key, int defaultValue);
    bool get(string key, bool defaultValue);
    float get(string key, float defaultValue);
    string get(string key, string defaultValue);
    string get(string key, const char* defaultValue);
    ofVec2f get(string key, ofVec2f defaultValue);
    ofVec3f get(string key, ofVec3f defaultValue);
    ofVec4f get(string key, ofVec4f defaultValue);
    ofRectangle get(string key, ofRectangle defaultValue);
    ofQuaternion get(string key, ofQuaternion defaultValue);
    ofMatrix4x4 get(string key, ofMatrix4x4 defaultValue);
    
    //setters
    void setString(string id, string value);

    template <typename T> void set(string id, string key, T value) { set(id=="" ? key : (id+"."+key), value); } //returntype void
    template <typename T> void set(string key, T value) { setString(key, ofxToString(value)); } //returntype void

};

#endif

