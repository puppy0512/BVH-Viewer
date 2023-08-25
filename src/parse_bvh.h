#ifndef PARSE_BVH_H
#define PARSE_BVH_H
#include <GL/glew.h>
#include <iostream>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <GL/glut.h>
#include <vector>
#include <string>

enum TransformationType {
    CAN_ROTATE_TRANSLATE,
    CAN_ROTATE,
    CAN_TRANSLATE,
    NO_CHANNEL
};

struct Joint{
    glm::vec3 position;
    bool isthereChild;
    int depth = 0;
    int numChannels = 0;
    std::string jointName = "";
    TransformationType t;
    std::vector<std::string> realOrder;
    std::vector<std::string> transformationOrder;




    bool canTranslateRotate = false;
    bool canRotate = false;
    bool canTranslate = false;

    Joint(std::string jName) {
        jointName = jName;
    } 

    Joint(GLfloat x, GLfloat y, GLfloat z) {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    int howManyChannels() {
        if(this->t == 0) {
            return 6;
        } else if(this->t == 1 || this->t == 2){
            return 3;
        } else {
            return 0;
        }
    }

    void setRealOrder() {

        realOrder.clear();
        if(transformationOrder.size() == 6) {
            
            for(int i = 0; i < transformationOrder.size(); i++) {
                if(transformationOrder[i].find("Xpos") != -1) {
                    this->realOrder.push_back("Xpos");
                } 
                if(transformationOrder[i].find("Ypos") != -1) {
                    this->realOrder.push_back("Ypos");
                } 
                if(transformationOrder[i].find("Zpos") != -1) {
                    this->realOrder.push_back("Zpos");
                } 
                if(transformationOrder[i].find("Xrot") != -1) {
                    this->realOrder.push_back("Xrot");
                } 
                if(transformationOrder[i].find("Yrot") != -1) {
                    this->realOrder.push_back("Yrot");
                } 
                if(transformationOrder[i].find("Zrot") != -1) {
                    this->realOrder.push_back("Zrot");
                } 
        }
        } else {
            for(int i = 0; i < transformationOrder.size(); i++) {
                if(transformationOrder[i].find("Xrot") != -1) {
                    this->realOrder.push_back("Xrot");
                } 
                if(transformationOrder[i].find("Yrot") != -1) {
                    this->realOrder.push_back("Yrot");
                } 
                if(transformationOrder[i].find("Zrot") != -1) {
                    this->realOrder.push_back("Zrot");
                } 
            }
        }
    }

    // Return the ith index of rotations
    int channelIndex(std::string str) {
        size_t transformation_index = -1;
        for (unsigned int i = 0; i < transformationOrder.size(); i++) {
            if(transformationOrder[i].find(str) != -1) {
                return i;
            }
        }
    }

};

class BVHModel{

    public: std::vector<Joint> joints;
            GLfloat frameTime = 0.0f;
            int numFrames = 0;
            std::vector<std::vector<GLfloat>> motionData;

    public: 
    
    BVHModel() {}
    
    
    void setNumFrames(int nf) {
        numFrames = nf;
    }

    void setFrameTime(GLfloat fTime) {
        frameTime = fTime;
    }

};

//std::vector<BVHModel> bvhmotions;

std::vector<std::string> split(std::string str, char delimiter);

std::vector<std::string> readBVHFiles();
BVHModel parse(std::string filename);



#endif 