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
    glm::mat4 getAnime(int k, int j) {if (k >= boneAnimations.size()) {k = boneAnimations.size()-1;} return boneAnimations.at(k).at(j%boneAnimations.at(k).size());};
    void getSize() {std::cout << boneAnimations.size() << " " << boneAnimations.at(0).size() << std::endl;}
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
    void loadMesh(const int num_vertices, const int length, const int width);
    // void loadAttachment(std::shared_ptr<Skinner> skin, const int num_bones);
    void loadAttachment(const int num_bones, const int width);
    // void loadSkeleton(std::shared_ptr<Skinner> skin);
    void loadSkeleton(std::shared_ptr<Skinner> skin);
	void setProgram(std::shared_ptr<Program> p) { prog = p; }
	void init(bool b = false);
	void draw(bool b = false);
    void LBSskinOn(std::shared_ptr<Skinner> skin, int k);
    void DQSskinOn(std::shared_ptr<Skinner> skin, int k);

    // helpers 
    glm::vec4 DQS(std::shared_ptr<Skinner> skin, int vertex);
    // glm::vec4 LBS(std::shared_ptr<Skinner> skin, int vertex);
	
private:
    int num_bones;
    int num_vertices;
    float dist_seperation;
	std::shared_ptr<Program> prog;
	std::vector<unsigned int> elemBuf; // index of vertex in triangular face (2 faces, 6)
	std::vector<float> posBuf; // x, y, z of each vert position
	std::vector<float> norBuf; // x, y, z of each vert normal
    std::vector<float> skinnedPos;
    std::vector<float> skinnedNor;
    std::vector<float> weiBuf; // weight of bone on vertex (2 weights per vertex, num_vert * 2)
    std::vector<float> numInfl; // num bones influencing
    std::vector<float> bonBuf; // bone index for corresponding weight (2 weights per vertex, num_vert * 2)
    std::vector<float> bonLoc; // location of each bone from 0 to b (#bones, one for each x of each bone)
	unsigned elemBufID;
	unsigned posBufID;
	unsigned norBufID;
	unsigned weiBufID;
    unsigned influID;
    unsigned bonBufID;

    // DQS
    std::vector<glm::quat> translations;
    std::vector<glm::quat> rotations;
};

#endif
