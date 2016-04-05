#ifndef OFX_INISETTINGS_H
#define OFX_INISETTINGS_H

#include <fstream>
#include <iostream>
#include <map>

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

    //template<typename T> T operator[](const string& key)

    //getters
    int get(string key, int defaultValue);
    bool get(string key, bool defaultValue);
    float get(string key, float defaultValue);
    string get(string key, string defaultValue);
    string get(string key, const char* defaultValue);
    ofPoint get(string key, ofPoint defaultValue);
//    ofVec3f get(string key, ofVec3f defaultValue);
//    ofVec4f get(string key, ofVec4f defaultValue);
    ofRectangle get(string key, ofRectangle defaultValue);
    ofQuaternion get(string key, ofQuaternion defaultValue);
    ofMatrix4x4 get(string key, ofMatrix4x4 defaultValue);

    //WORKS: string operator[](string key) { return get(key,""); }  but not with multiple overloading

    int getInt(string key) { return get(key,0); }
    string getString(string key) { return get(key,""); }
    float getFloat(string key) { return get(key,0.0f); }
    ofColor getColor(string key) { return ofColor::fromHex(getInt(key)); }
    bool getBool(string key) { return get(key,false); }

    //int operator[](string key) { return get(key,0); }    //cannot overload previous one
    //template<typename T> operator [](const string& x) { return  };

//    int get(string key) { return get(key,0); }
//    bool get(string key) { return get(key,false); }
//    float get(string key) { return get(key,0.0f); }
//    string get(string key) { return get(key,""); }
//    ofVec2f get(string key) { return get(key,ofVec2f());
//    ofVec3f get(string key) { return get(key,ofVec3f());
//    ofVec4f get(string key) { return get(key,ofVec4f());

    //template<typename T> operator [](const string& x) { return };
    //template<typename T> T operator[](const string& key) { return get(key,T()); }
    // string operator[](const string& key) { return get(key,string()); }
    //ofTrueTypeFont &operator[](const string& fontnamesize);

    //setters
    void setString(string id, string value);

    template<typename T> void set(string id, string key, T value) { set(id=="" ? key : (id+"."+key), value); } //returntype void
    template<typename T> void set(string key, T value) { setString(key, ofToString(value)); } //returntype void

private:

    //functions copied from ofxExtras
    // trim trailing spaces
    string ofxTrimStringRight(string str) {
        size_t endpos = str.find_last_not_of(" \t\r\n");
        return (string::npos != endpos) ? str.substr( 0, endpos+1) : str;
    }

    // trim trailing spaces
    string ofxTrimStringLeft(string str) {
        size_t startpos = str.find_first_not_of(" \t\r\n");
        return (string::npos != startpos) ? str.substr(startpos) : str;
    }

    string ofxTrimString(string str) {
        return ofxTrimStringLeft(ofxTrimStringRight(str));;
    }

//    int ofxToInteger(string str) {
//        //works also for hex: 0xff0000....
//        istringstream stream(str);
//        stream.unsetf(ios_base::dec);
//        int result; stream >> result; return result;
//    }

//    bool ofxToBoolean(string str) { //rick 3-1-2008
//        return str=="true" || str=="True" || str=="TRUE" || str=="1";
//    }

//    ofVec2f ofxToVec2f(string str) {
//        vector<string> v = ofSplitString(str,",");
//        if (v.size()==1) return ofVec2f(ofToFloat(v[0]),ofToFloat(v[0])); ///is dit gewenst?
//        if (v.size()!=2) return ofVec2f(0,0);
//        else return ofVec2f(ofToFloat(v[0]),ofToFloat(v[1]));
//    }

//    ofVec3f ofxToVec3f(string str) {
//        vector <string> v = ofSplitString(str,",");
//        if (v.size()==1) return ofVec3f(ofToFloat(v[0]),ofToFloat(v[0]),ofToFloat(v[0])); ///is dit gewenst? .5 wordt dus (.5,.5,.5) wordt oa gebruikt voor scale.
//        if (v.size()==2) return ofVec3f(ofToFloat(v[0]),ofToFloat(v[1]),0); //2D
//        if (v.size()!=3) return ofVec3f(0,0,0);
//        else return ofVec3f(ofToFloat(v[0]),ofToFloat(v[1]),ofToFloat(v[2]));
//    }

//    ofVec3f ofxToVec3f(float *a) {
//        return ofVec3f(a[0],a[1],a[2]);
//    }


//    ofVec4f ofxToVec4f(string str) {
//        vector <string> v = ofSplitString(str,",");
//        if (v.size()!=4) return ofVec4f(0,0,0,0);
//        else return ofVec4f(ofToFloat(v[0]),ofToFloat(v[1]),ofToFloat(v[2]),ofToFloat(v[3]));
//    }

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

//    ofRectangle ofxToRectangle(string str) {
//        return ofxToRectangle(ofxToVec4f(str));
//    }

//    ofRectangle ofxToRectangle(ofVec4f v) {
//        return ofRectangle(v.x,v.y,v.z,v.w);
//    }

//    string ofxToString(ofVec2f v) {
//        return ofToString(v.x) + "," + ofToString(v.y);
//    }

//    string ofxToString(ofVec3f v, int precision) {
//        return ofToString(v.x,precision) + "," + ofToString(v.y,precision) + "," + ofToString(v.z,precision);
//    }

//    string ofxToString(ofVec4f v) {
//        return ofToString(v.x) + "," + ofToString(v.y) + "," + ofToString(v.z) + "," + ofToString(v.w);
//    }

//    string ofxToString(ofPoint p) {
//      return ofToString(p);
//    }

//    string ofxToString(ofMatrix4x4 m) {
//        stringstream ss;
//        ss << m;
//        string s = ss.str();
//        ofStringReplace(s, "\n", ",");
//        ofStringReplace(s, " ", "");
//        return s;
//    }

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

#endif

