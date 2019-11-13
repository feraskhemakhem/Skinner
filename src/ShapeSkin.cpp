#include <iostream>
#include <fstream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "ShapeSkin.h"
#include "GLSL.h"
#include "Program.h"

using namespace std;

ShapeSkin::ShapeSkin() :
	prog(NULL),
	elemBufID(0),
	posBufID(0),
	norBufID(0),
	weiBufID(0),
    influID(0),
    bonBufID(0)
{
}

ShapeSkin::~ShapeSkin()
{
}

// this loads the obj, so in our case we will load a rectangle
void ShapeSkin::loadMesh(const string &meshName)
{
	// Load geometry 
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if(!rc) {
		cerr << errStr << endl;
	} else {
		posBuf = attrib.vertices;
		norBuf = attrib.normals;
        skinnedPos = posBuf;
        skinnedNor = norBuf;
		assert(posBuf.size() == norBuf.size());
		// Loop over shapes
		for(size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			const tinyobj::mesh_t &mesh = shapes[s].mesh;
			size_t index_offset  = 0;
			for(size_t f = 0; f < mesh.num_face_vertices.size(); f++) {
				size_t fv = mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for(size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = mesh.indices[index_offset + v];
					elemBuf.push_back(idx.vertex_index);
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}
}

void ShapeSkin::loadMesh(const int num_vertices, const int length, const int width) {
    // determine how much to seperate each vertex, and the set points
    float dist_seperation = (float)width / ((num_vertices / 2) - 1); // -1 because the distance is betweens points, which there are 1 less distance than point
    float current_x = -1 * width / 2.0;
    this->num_vertices = num_vertices;

    std::cout << "Loading mesh with " << current_x << " " << -1 * length / 2.0 << std::endl;

    // first vertex is at -width/2, all the way to width/2
    cout << dist_seperation << " is distance between each vertex" << endl;
    cout << "vertices at "; 
    while ((current_x - ((float)width / 2)) <= 0.001) {
            // std::cout << "Loading mesh with " << current_x << " " << -1 * length / 2.0 << std::endl;
        // add lower vertex
        posBuf.push_back(current_x);
        posBuf.push_back(0);
        posBuf.push_back(-1 * length / 2.0);

        // add lower normal
        norBuf.push_back(current_x);
        norBuf.push_back(1);
        norBuf.push_back(-1 * length / 2.0);

        // add upper vertex
        posBuf.push_back(current_x);
        posBuf.push_back(0);
        posBuf.push_back(length / 2.0);

        // add upper normal
        norBuf.push_back(current_x);
        norBuf.push_back(1);
        norBuf.push_back(length / 2.0);
        cout << current_x << " ";

        current_x += dist_seperation;
    }
    cout << endl;

    skinnedPos = posBuf;
    skinnedNor = norBuf;
    assert(posBuf.size() == norBuf.size());

    // add vertices that make up a face (first and last 2 vertices)
        elemBuf.push_back(posBuf.size()/3 - 2);
        elemBuf.push_back(0);
        elemBuf.push_back(1);

        elemBuf.push_back(1);
        elemBuf.push_back(posBuf.size()/3 - 1);
        elemBuf.push_back(posBuf.size()/3 - 2);

        elemBuf.push_back(1);
        elemBuf.push_back(0);
        elemBuf.push_back(posBuf.size()/3 - 2);
        
        elemBuf.push_back(posBuf.size()/3 - 2);
        elemBuf.push_back(posBuf.size()/3 - 1);
        elemBuf.push_back(1);

    // no shapes to loop because no groups object names
}

// takes in the number of bones and the skin, and over time applies different 
// attachment file is a file of vertices... this will just be inside the rectangle hearts
// void ShapeSkin::loadAttachment(std::shared_ptr<Skinner> skin, const int num_bones)
// {
// 	int nverts, nbones;
//     nbones = num_bones;
//     nverts = 4; // rectangles always have 4
// 	assert(nverts == posBuf.size()/3);

//     // for filling in weights
//     float dummi;
// 	for (int i = 0; i < nverts; ++i) {
//         // actually adding in weights, for one vertex
//         skin->pushWeight();
//         numInfl.push_back(0);
//         int internalCount = 0;
//         for (int j = 0; j < nbones; ++j) {
//             // dummi is the weight
//             skin->addWeight(i, dummi);
//             if ((dummi * 100.0f) != 0.0f) {
//                 internalCount++;
//                 numInfl.at(i) = numInfl.at(i) + 1;
//                 weiBuf.push_back(dummi);
//                 bonBuf.push_back(j);
//             }

//         }
//         for (int j = 0; j < (16 - internalCount); ++j) {
//             weiBuf.push_back(0.0f);
//             bonBuf.push_back(0.0f);
//         }
        
// 	}
// }

// load self generated attachment file
void ShapeSkin::loadAttachment(const int num_bones, const int width) 
{
    assert (num_bones != 0);
    this->num_bones = num_bones;
    this->dist_seperation = float(width) / (num_bones + 1); // +1 becuse there are "invisible" bones at the ends of the mesh
    float seperation_ratio = float(num_bones + 1) / float((num_vertices/2) - 1);
    float bone_index, prev_bone, next_bone;
    cout << "seperation ratio " << seperation_ratio << " dist seperation " << dist_seperation << endl; 

    numInfl = std::vector<float>(this->num_vertices, 2);

    float x_location = -1 * width / 2.0;
    // cout << "bones at ";
    for (int i = 0; i < num_bones; ++i) {
        x_location += dist_seperation;
        // cout << x_location << '\t';
        bonLoc.push_back(x_location);
    }
    bonLoc.push_back(dist_seperation); //FIXME: TESTING WITH ILLEGAL VALUE DONT MIND ME
    // cout << endl;
    for (int i = 0; i < this->num_vertices/2; ++i) {
        // lower, then upper vertex
        
        // vertex location * ratio will give us the index of bone we are at
        // +1 to make up for index, and -2 because the first bone is at index 1
        bone_index = (i * seperation_ratio) - 1;
        cout << "bone index " << bone_index << endl;
        // weiBuf.push_back(1);
        // weiBuf.push_back(0);
        // weiBuf.push_back(1);
        // weiBuf.push_back(0);
        // bonBuf.push_back(1);
        // bonBuf.push_back(0);            
        // bonBuf.push_back(1);
        // bonBuf.push_back(0);

        // edge cases - if an invisible bone is weighted, make it unimportant
        if (bone_index < 0) { // if using the first bone
        // cout << "first bone" << endl;
            weiBuf.push_back(1); // ratio wrt distance
            weiBuf.push_back(0); // "
            bonBuf.push_back(0);
            bonBuf.push_back(1);
            weiBuf.push_back(1); // ratio wrt distance
            weiBuf.push_back(0); // "
            bonBuf.push_back(0);
            bonBuf.push_back(1);
        }
        else if (bone_index > num_bones-1) { // if using the last 2 bones
        // cout << "last bone" <<endl;
            weiBuf.push_back(1); // ratio wrt distance
            weiBuf.push_back(0); // "
            bonBuf.push_back(num_bones-1);
            bonBuf.push_back(num_bones-2);
            weiBuf.push_back(1); // ratio wrt distance
            weiBuf.push_back(0); // "
            bonBuf.push_back(num_bones-1);
            bonBuf.push_back(num_bones-2);
        }
        else 
        {
            // cout << bone_index << " is bone index\t";
            prev_bone = floor(bone_index);
            next_bone = ceil(bone_index);

            // if the two bones are the same, give a weight of 1
            if ((next_bone - prev_bone) < 0.001) {
                weiBuf.push_back(1);
                weiBuf.push_back(0);
                weiBuf.push_back(1);
                weiBuf.push_back(0);
                // cout << "ok\t" << endl;
            }
            else {
                weiBuf.push_back(next_bone - bone_index);
                weiBuf.push_back(bone_index - prev_bone);
                weiBuf.push_back(next_bone - bone_index);
                weiBuf.push_back(bone_index - prev_bone);
                cout << next_bone - bone_index << " ";
                // cout << "nah\t";
            }
            bonBuf.push_back(next_bone);
            bonBuf.push_back(prev_bone);
            bonBuf.push_back(next_bone);
            bonBuf.push_back(prev_bone);
        }
        cout << prev_bone << " " << next_bone << endl;

    }
} 

// this is the animation that the vertices do, in x y z format
void ShapeSkin::loadSkeleton(std::shared_ptr<Skinner> skin)
{
    int nbones;
    nbones = this->num_bones;
    // assert(bonLoc.size() == nbones);

    // read first line of points and quaternions
    glm::quat q; // quaternion
    glm::vec3 p; // position
    glm::mat4 E;
    for (int i = 0; i < nbones; ++i) {
        // we read the first line seperately in order to have the initial

        q.x = 0;
        q.y = 0;
        q.z = 0;
        q.w = 1;

        // do not move, just rotate
        // if (i==0)
            p.x = bonLoc.at(i);
        // else
        //     p.x = bonLoc.at(bonLoc.size()-1);
        p.y = 0;
        p.z = 0;
            
        E = mat4_cast(q); // converting each 4-tuple to one 4x4 trans matrix
        E[3] = glm::vec4(p, 1.0f);
        skin->addBind(E);
    }
    
    for (int j = 0; j < 18; ++j) { // 18 animations, to get to 90 degrees
        // we read the the rest of the lines are not bind pose so yeah
        skin->pushAnime();
        for (int i = 0; i < nbones; ++i) {
            // rotate 5 degree across y axis

            //https://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm
            q.x = 0;
            // if (i == nbones-1) { // last bone
            //     q.y = 0;
            //     q.w = 1;
            // }
            // else if (i == 0) {
            //     q.y = sin(PI / 144 * j);
            //     q.w = cos(PI / 144 * j);
            // }
            // else if (i%2 == 0) {
            //     q.y = sin(PI / 72 * j);
            //     q.w = cos(PI / 72 * j);
            // }
            // else {
            //     q.y = -1*sin(PI / 72 * j);
            //     q.w = cos(PI / 72 * j);
            // }
            // if (i == 0) {
            //     q.y = sin(PI / 8);
            //     q.w = cos(PI / 8);
            // }
            // else if (i%2 == 0) {
            //     q.y = sin(PI / 4);
            //     q.w = cos(PI / 4);
            // }
            // else {
            //     q.y = -1*sin(PI / 4);
            //     q.w = cos(PI / 4);
            // }
            q.z = 0;
            q.y = 0;
            q.w = 1;

            q = normalize(q);
            
            E = mat4_cast(q); // converting each 7-tuple to one 4x4 trans matrix

            // add rotation quaternion to vector with heirarchy
            if (i != 0)
                q = normalize(rotations.at(i-1) * q);
            rotations.push_back(q);


            // do not move, just rotate
            p.x = bonLoc.at(i);
            // if (i == 0)
            //     p.x = bonLoc.at(0);
            // else
                // p.x = dist_seperation;
            p.y = 0;
            if (i == 1)
                p.z = -1.0*j/2;
            else
                p.z = 0;
            
            E[3] = glm::vec4(p, 1.0f);
            skin->addAnime(j, E);
        }

        
    }    
}

void ShapeSkin::LBSskinOn (std::shared_ptr<Skinner> skin, int k) {

    // heirarchy applied to bones
    // move_bones(k);
    assert(num_bones != 0);
    vector<glm::mat4> howdy;
    howdy.push_back(skin->getAnime(k, 0));
    for (int i = 1; i < num_bones; ++i) {
        howdy.push_back(howdy.at(i-1) * skin->getAnime(k,i));
    }

    // iterates all the vertices
    for (int i = 0; i < posBuf.size()/3; ++i) {
        bool idk = false;

        // creates clear dummy vectors
        glm::vec4 position;
        glm::vec4 normal;
        glm::vec4 x(posBuf.at(i*3),posBuf.at(3*i+1),posBuf.at(3*i+2), 1.0f);
        glm::vec4 y(norBuf.at(i*3),norBuf.at(3*i+1),norBuf.at(3*i+2), 0.0f);

        
        // calculates skinned position and normal
        for (int j = 0; j < 2; ++j) {
            // i is vertex, j is bone, k is time
            int bone = bonBuf.at(2*i+j);
            if (bone > 2) {
                cout << "BONE TOO BIG" << endl;
            }

            // glm::vec4 dum1 = skin->getBind(bone) * x; // inverse bind matrix * initial vertex
            // // dum1 = howdy.at(bone) * dum1; // inverse bind matrix * initial vertex
            // dum1 = skin->getAnime(k, bone) * dum1; // inverse of bind matrix of jth bone at frame k
            // dum1 = weiBuf.at(2*i+j) * dum1; // apply weight of ith vertex on jth bone
            // position = position + dum1;

            // // skinned normals
            // glm::vec4 dum2 = skin->getBind(bone) * y;
            // dum2  = skin->getAnime(k, bone) * dum2;
            // // dum2 = howdy.at(bone) * dum2;
            // dum2 = weiBuf.at(2*i+j) * dum2;
            // normal = normal + dum2;

            glm::vec4 dum1 = skin->getBind(bone) * x;
            glm::vec4 dum2 = skin->getAnime(k, bone) * dum1;
            glm::vec4 dum3 = weiBuf.at(2*i+j) * dum2;
            position = position + dum3;

            if (weiBuf.at(2*i+j) == 1 && bone == 1 && i%2 == 0 && position.z != -1) {
                idk = true;
            }

            // skinned normals
            // glm::vec4 dum4 = y;
            glm::vec4 dum4 = skin->getBind(bone) * y;
            glm::vec4 dum5  = skin->getAnime(k, bone) * dum4;
            glm::vec4 dum6 = weiBuf.at(2*i+j) * dum5;
            normal = normal + dum6;
        }
        
        // adjusts values of position and normal respectively
        skinnedPos.at(3*i) = position.x;
        skinnedPos.at(3*i+1) = position.y;
        skinnedPos.at(3*i+2) = position.z;
        if (idk) {
            cout << skinnedPos.at(3*i+2) << endl;
        }
        
        skinnedNor.at(3*i) = normal.x;
        skinnedNor.at(3*i+1) = normal.y;
        skinnedNor.at(3*i+2) = normal.z;
        idk = false;
    }
}

// glm::vec4 DQS(int vertex) {
     
// }

void ShapeSkin::DQSskinOn(std::shared_ptr<Skinner> skin, int k) {

}

void ShapeSkin::init(bool b)
{
    
    // for the influencing weights
    glGenBuffers(1, &weiBufID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, weiBufID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, weiBuf.size()*sizeof(unsigned int), &weiBuf[0], GL_STATIC_DRAW);

    // for the influencing weights
    glGenBuffers(1, &bonBufID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bonBufID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bonBuf.size()*sizeof(unsigned int), &bonBuf[0], GL_STATIC_DRAW);

    // for the influencing weights
    glGenBuffers(1, &influID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, influID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numInfl.size()*sizeof(unsigned int), &numInfl[0], GL_STATIC_DRAW);
    
	// Send the element array to the GPU
	glGenBuffers(1, &elemBufID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemBufID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elemBuf.size()*sizeof(unsigned int), &elemBuf[0], GL_STATIC_DRAW);
	
	// Unbind the arrays
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	assert(glGetError() == GL_NO_ERROR);
}

void ShapeSkin::draw(bool b)
{
	assert(prog);
    
    if (b) {
        // Send the position array to the GPU
        glGenBuffers(1, &posBufID);
        glBindBuffer(GL_ARRAY_BUFFER, posBufID);
        glBufferData(GL_ARRAY_BUFFER, posBuf.size()*sizeof(float), &posBuf[0], GL_STATIC_DRAW);
        
        // Send the normal array to the GPU
        glGenBuffers(1, &norBufID);
        glBindBuffer(GL_ARRAY_BUFFER, norBufID);
        glBufferData(GL_ARRAY_BUFFER, norBuf.size()*sizeof(float), &norBuf[0], GL_STATIC_DRAW);
    }
    else {
        // Send the position array to the GPU
        glGenBuffers(1, &posBufID);
        glBindBuffer(GL_ARRAY_BUFFER, posBufID);
        glBufferData(GL_ARRAY_BUFFER, skinnedPos.size()*sizeof(float), &skinnedPos[0], GL_STATIC_DRAW);
        
        // Send the normal array to the GPU
        glGenBuffers(1, &norBufID);
        glBindBuffer(GL_ARRAY_BUFFER, norBufID);
        glBufferData(GL_ARRAY_BUFFER, skinnedNor.size()*sizeof(float), &skinnedNor[0], GL_STATIC_DRAW);
    }
    
	int h_pos = prog->getAttribute("aPos");
	glEnableVertexAttribArray(h_pos);
	glBindBuffer(GL_ARRAY_BUFFER, posBufID);
	glVertexAttribPointer(h_pos, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);
	
	int h_nor = prog->getAttribute("aNor");
	glEnableVertexAttribArray(h_nor);
	glBindBuffer(GL_ARRAY_BUFFER, norBufID);
	glVertexAttribPointer(h_nor, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);
    
    // placed outside to remove compilation error of undeclared variables later
    int h_wei0 = prog->getAttribute("weights0");
    int h_wei1 = prog->getAttribute("weights1");
    int h_wei2 = prog->getAttribute("weights2");
    int h_wei3 = prog->getAttribute("weights3");
    int h_bon0 = prog->getAttribute("bones0");
    int h_bon1 = prog->getAttribute("bones1");
    int h_bon2 = prog->getAttribute("bones2");
    int h_bon3 = prog->getAttribute("bones3");
    int h_num = prog->getAttribute("numInfl");
    
    if (b) {

        glEnableVertexAttribArray(h_wei0);
        glEnableVertexAttribArray(h_wei1);
        glEnableVertexAttribArray(h_wei2);
        glEnableVertexAttribArray(h_wei3);
        glBindBuffer(GL_ARRAY_BUFFER, weiBufID);
        unsigned stride = 16*sizeof(float);
        glVertexAttribPointer(h_wei0, 4, GL_FLOAT, GL_FALSE, stride, (const void *)( 0*sizeof(float)));
        glVertexAttribPointer(h_wei1, 4, GL_FLOAT, GL_FALSE, stride, (const void *)( 4*sizeof(float)));
        glVertexAttribPointer(h_wei2, 4, GL_FLOAT, GL_FALSE, stride, (const void *)( 8*sizeof(float)));
        glVertexAttribPointer(h_wei3, 4, GL_FLOAT, GL_FALSE, stride, (const void *)(12*sizeof(float)));
        


        glEnableVertexAttribArray(h_bon0);
        glEnableVertexAttribArray(h_bon1);
        glEnableVertexAttribArray(h_bon2);
        glEnableVertexAttribArray(h_bon3);
        glBindBuffer(GL_ARRAY_BUFFER, bonBufID);
        glVertexAttribPointer(h_bon0, 4, GL_FLOAT, GL_FALSE, stride, (const void *)( 0*sizeof(float)));
        glVertexAttribPointer(h_bon1, 4, GL_FLOAT, GL_FALSE, stride, (const void *)( 4*sizeof(float)));
        glVertexAttribPointer(h_bon2, 4, GL_FLOAT, GL_FALSE, stride, (const void *)( 8*sizeof(float)));
        glVertexAttribPointer(h_bon3, 4, GL_FLOAT, GL_FALSE, stride, (const void *)(12*sizeof(float)));

    
        glEnableVertexAttribArray(h_num);
        glBindBuffer(GL_ARRAY_BUFFER, influID);
        glVertexAttribPointer(h_num, 1, GL_FLOAT, GL_FALSE, 0, (const void *)0);
    }

 
	// Draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemBufID);
	glDrawElements(GL_TRIANGLES, (int)elemBuf.size(), GL_UNSIGNED_INT, (const void *)0);
    
    if (b) {
        glDisableVertexAttribArray(h_wei0);
        glDisableVertexAttribArray(h_wei1);
        glDisableVertexAttribArray(h_wei2);
        glDisableVertexAttribArray(h_wei3);
        glDisableVertexAttribArray(h_bon0);
        glDisableVertexAttribArray(h_bon1);
        glDisableVertexAttribArray(h_bon2);
        glDisableVertexAttribArray(h_bon3);
        glDisableVertexAttribArray(h_num);
    }

	glDisableVertexAttribArray(h_nor);
	glDisableVertexAttribArray(h_pos);
    
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    GLSL::checkError(GET_FILE_LINE);

}

