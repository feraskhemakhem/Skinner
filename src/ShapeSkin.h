#pragma once
#ifndef _SHAPESKIN_H_
#define _SHAPESKIN_H_

#include <memory>
#include <vector>
#include <math.h>

#define PI 3.14159265

class MatrixStack;
class Program;

class Skinner
{
    // xi(0) will be handled in the shaders
    int numBones;
    std::vector<glm::mat4> bindPose; // Mj(0) bone
    std::vector<std::vector<glm::mat4>> boneAnimations; // Mj(k) time.bone
    std::vector<std::vector<float>> weights; // wij vertex.bone
public:
    Skinner(int numBones) {this->numBones = numBones;};
    virtual ~Skinner() {};
    
    // adding to vectors
    void pushWeight() {weights.push_back(std::vector<float> ());};
    void addWeight(int j, float weight) {weights.at(j).push_back(weight);};
    void pushAnime() {boneAnimations.push_back(std::vector<glm::mat4> ());};
    void addAnime(int k, glm::mat4 j) {boneAnimations.at(k).push_back(j);};
    void addBind(glm::mat4 j) {bindPose.push_back(glm::inverse(j));};
    
    // get specific element
    int getBones() {return numBones;};
    glm::mat4 getBind(int j) {return bindPose.at(j%bindPose.size());};
    glm::mat4 getAnime(int k, int j) {k = k%boneAnimations.size(); return boneAnimations.at(k).at(j%boneAnimations.at(k).size());};
    float getWei(int j, int i) {return weights.at(j%weights.size()).at(i%weights.at(j).size());};
    
    // return vectors for da skinning eq
    std::vector<glm::mat4>  V () {return bindPose;};
    std::vector<glm::mat4> getAnimeV (int k) {return boneAnimations.at(k%boneAnimations.size());};
    
};


class ShapeSkin
{
public:
	ShapeSkin();
	virtual ~ShapeSkin();
	void loadMesh(const std::string &meshName);
    void loadMesh(const int num_vertices, const int height, const int width);
    // void loadAttachment(std::shared_ptr<Skinner> skin, const int num_bones);
    void loadSkeleton(std::shared_ptr<Skinner> skin, const int num_bones);
	void setProgram(std::shared_ptr<Program> p) { prog = p; }
	void init(bool b = false);
	void draw(bool b = false);
    void skinOn(std::shared_ptr<Skinner> skin, int k);
	
private:
    int num_bones;
	std::shared_ptr<Program> prog;
	std::vector<unsigned int> elemBuf;
	std::vector<float> posBuf;
	std::vector<float> norBuf;
    std::vector<float> skinnedPos;
    std::vector<float> skinnedNor;
    std::vector<float> weiBuf;
    std::vector<float> numInfl;
    std::vector<float> bonBuf;
	unsigned elemBufID;
	unsigned posBufID;
	unsigned norBufID;
	unsigned weiBufID;
    unsigned influID;
    unsigned bonBufID;
};

#endif
