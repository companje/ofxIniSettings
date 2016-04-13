#pragma once
#include "ofMain.h"

class ofxIniSettings {
public:

  ofxIniSettings() {}
  ofxIniSettings(string filename) { load(filename); }

  bool load(string filename, bool clearFirst=false, bool setAsOutputFile=true); // you can call multiple times with different files, incremental
  bool has(string key) { return keys[key]!=""; };
  void clear();
  string replaceVariables(string value);
  void print();

  map<string,string> keys;
  string outputFilename;

  //getters
  int get(string key, int defaultValue);
  bool get(string key, bool defaultValue);
  float get(string key, float defaultValue);
  string get(string key, string defaultValue);
  string get(string key, const char* defaultValue);
  ofPoint get(string key, ofPoint defaultValue);
  ofRectangle get(string key, ofRectangle defaultValue);
  ofQuaternion get(string key, ofQuaternion defaultValue);
  ofMatrix4x4 get(string key, ofMatrix4x4 defaultValue);

  int getInt(string key) { return get(key,0); }
  string getString(string key) { return get(key,""); }
  float getFloat(string key) { return get(key,0.0f); }
  ofColor getColor(string key) { return ofColor::fromHex(getInt(key)); }
  bool getBool(string key) { return get(key,false); }

  //setters
  void setString(string id, string value);

  template<typename T> void set(string id, string key, T value) { set(id=="" ? key : (id+"."+key), value); } //returntype void
  template<typename T> void set(string key, T value) { setString(key, ofToString(value)); } //returntype void

private:

  ofRectangle ofxToRectangle(string str) {
    vector <string> v = ofSplitString(str,",");
    if (v.size()==5) return ofRectangle(ofPoint(ofToFloat(v[0]),ofToFloat(v[1]),ofToFloat(v[2])),ofToFloat(v[3]),ofToFloat(v[4]));
    else if (v.size()==4) return ofRectangle(ofToFloat(v[0]),ofToFloat(v[1]),ofToFloat(v[2]),ofToFloat(v[3]));
    else return ofRectangle();
  }

  ofPoint ofxToPoint(string str) {
    vector <string> v = ofSplitString(str,",");
    if (v.size()==3) return ofPoint(ofToFloat(v[0]),ofToFloat(v[1]),ofToFloat(v[2]));
    else if (v.size()==2) return ofPoint(ofToFloat(v[0]),ofToFloat(v[1]));
    else return ofPoint();
  }

  ofMatrix4x4 ofxToMatrix4x4(string s) {
    vector<string> a = ofSplitString(s, ",");
    float mat[16];
    for (int i=0; i<16; i++) {
        mat[i] = ofToFloat(a[i]);
    }
    return ofMatrix4x4(mat);
  }

  vector<float> ofxToFloatVector(string s, string delimiter) {
    vector<float> f;
    vector<string> items = ofSplitString(s,delimiter);
    for (int i=0; i<items.size(); i++) {
      f.push_back(ofToFloat(items.at(i)));
    }
    return f;
  }

  ofQuaternion ofxToQuaternion(string str) {
    vector <string> v = ofSplitString(str,",");
    if (v.size()!=4) return ofVec4f(0,0,0,0);
    else return ofVec4f(ofToFloat(v[0]),ofToFloat(v[1]),ofToFloat(v[2]),ofToFloat(v[3]));
  }
};
