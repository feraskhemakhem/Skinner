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

bool WIREFRAME = false;

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

void ShapeSkin::loadMesh(const int num_vertices_horiz, const int num_vertices_vert, const int length, const int width) {

	cout << "vertices are " << num_vertices_horiz << " x " << num_vertices_vert << endl;
    // determine how much to seperate each vertex, and the set points
    float dist_seperation_horiz = (float)width / (num_vertices_horiz - 1); // -1 because the distance is betweens points, which there are 1 less distance than point
    float dist_seperation_vert = (float)length / (num_vertices_vert - 1);
    float current_x = -1 * width / 2.0;
    float current_z = -1 * length / 2.0;
    vector<float> vertical_vertex_locations;
    this->num_vertices_horiz = num_vertices_horiz;
    this->num_vertices_vert = num_vertices_vert;

    // std::cout << "Loading mesh with " << current_x << " " << -1 * length / 2.0 << std::endl;

    // calculate the locations in the z direction where vertices go once
    cout << "z locations at ";
    while ((current_z - (float)length / 2) <= 0.001) {
        vertical_vertex_locations.push_back(current_z);
        cout << current_z << " ";
        current_z += dist_seperation_vert;
    }
    cout << endl;

    // first vertex is at -width/2, all the way to width/2
    // cout << dist_seperation_horiz << " is distance between each vertex" << endl;
    // cout << "vertices at "; 
    while ((current_x - ((float)width / 2)) <= 0.001) {

        // add vertices and normals, one for each unique z value
        for (int i = 0; i < vertical_vertex_locations.size(); ++i) {
            // add vertex
            posBuf.push_back(current_x); // x value calculated in parent while loop
            posBuf.push_back(0); // y value always 0 for 2D vertices
            posBuf.push_back(vertical_vertex_locations.at(i)); // precalculated z value

            // add normal
            norBuf.push_back(current_x); // x value calculated in parent while loop
            norBuf.push_back(1); // y value always 1 for 2D normals
            norBuf.push_back(vertical_vertex_locations.at(i)); // precalculated z value
        }
        cout << current_x << " ";

        current_x += dist_seperation_horiz;
    }
    cout << endl;

    skinnedPos = posBuf;
    skinnedNor = norBuf;
    assert(posBuf.size() == norBuf.size());

    // TRIANGLES START

		// creating lower left triangles
		for (int i = 0; i < posBuf.size()/3 - 1 - this->num_vertices_vert; ++i) { // additional -1 because of the we are using lower left corners
				if ((i+1) % this->num_vertices_vert != 0) { // top row doesn't create triangles
						elemBuf.push_back(i);
						elemBuf.push_back(i+1);
						elemBuf.push_back(i+this->num_vertices_vert);  
				}
		}

		// creating upper right triangles
		for (int i = this->num_vertices_vert+1; i < posBuf.size()/3; ++i) {
				if (i % this->num_vertices_vert != 0) { // top row doesn't create triangles
						elemBuf.push_back(i);
						elemBuf.push_back(i-1);
						elemBuf.push_back(i-this->num_vertices_vert);
				}
		}

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

// loads locations of vertices in xyz place
void ShapeSkin::loadAttachment(const int num_bones, const int width) 
{
    assert (num_bones != 0);
    this->num_bones = num_bones;
    this->dist_seperation = float(width) / (num_bones + 1); // +1 becuse there are "invisible" bones at the ends of the mesh
    float seperation_ratio = float(num_bones + 1) / float(num_vertices_horiz - 1);
    float bone_index, prev_bone, next_bone;
    cout << "seperation ratio " << seperation_ratio << " dist seperation " << dist_seperation << endl; 

    float wei1, wei2, bon1, bon2;

    numInfl = std::vector<float>(this->num_vertices_horiz * this->num_vertices_vert, 2);

    float x_location = -1 * width / 2.0;
    for (int i = 0; i < num_bones; ++i) {
        x_location += dist_seperation;
        bonLoc.push_back(x_location);
        cout << "x_location " << x_location << endl;
    }
    bonLoc.push_back(dist_seperation); //FIXME: TESTING WITH ILLEGAL VALUE DONT MIND ME
    for (int i = 0; i < this->num_vertices_horiz; ++i) {
        // lower, then upper vertex
        
        // vertex location * ratio will give us the index of bone we are at
        // +1 to make up for index, and -2 because the first bone is at index 1
        bone_index = (i * seperation_ratio) - 1;
        // bone_index = 1;
        cout << "bone index " << bone_index << endl;

        // edge cases - if an invisible bone is weighted, make it unimportant
        if (bone_index < 0) { // if using the first bone
        // cout << "first bone" << endl;

            wei1 = 1;
            wei2 = 0;
            bon1 = 0;
            bon2 = 0;

        }
        else if (bone_index > num_bones-1) { // if using the last 2 bones
        // cout << "last bone" <<endl;

            wei1 = 1;
            wei2 = 0;
            bon1 = num_bones-1;
            bon2 = num_bones-2;
        }
        else 
        {
            // cout << bone_index << " is bone index\t";
            prev_bone = floor(bone_index);
            next_bone = ceil(bone_index);

            // if the two bones are the same, give a weight of 1
            if ((next_bone - prev_bone) < 0.001) {
                // cout << "ok\t" << endl;

                wei1 = 1;
                wei2 = 0;
            }
            else {
                // cout << next_bone - bone_index << " ";
                // cout << "nah\t";

                wei2 = next_bone - bone_index;
                wei1 = bone_index - prev_bone;
						}
            bon1 = next_bone;
            bon2 = prev_bone;
        }
        // cout << prev_bone << " " << next_bone << endl;
				cout << wei1 << " for bone " << bon1 << " and " << wei2 << " for bone " << bon2 << endl;
  
        for (int j = 0; j < this->num_vertices_vert; ++j) {
            weiBuf.push_back(wei1);
            weiBuf.push_back(wei2);
            bonBuf.push_back(bon1);
            bonBuf.push_back(bon2);
        }

    }
		// 	for (int i = 0; i < this->num_vertices_horiz/2; ++i) {
    //     // lower, then upper vertex
        
    //     // vertex location * ratio will give us the index of bone we are at
    //     // +1 to make up for index, and -2 because the first bone is at index 1
    //     bone_index = (i * seperation_ratio) - 1;
    //     bone_index = -1;
    //     cout << "bone index " << bone_index << endl;

    //     // edge cases - if an invisible bone is weighted, make it unimportant
    //     if (bone_index < 0) { // if using the first bone
    //     // cout << "first bone" << endl;
    //         weiBuf.push_back(1); // ratio wrt distance
    //         weiBuf.push_back(0); // "
    //         bonBuf.push_back(0);
    //         bonBuf.push_back(1);
    //         weiBuf.push_back(1); // ratio wrt distance
    //         weiBuf.push_back(0); // "
    //         bonBuf.push_back(0);
    //         bonBuf.push_back(1);
    //     }
    //     else if (bone_index > num_bones-1) { // if using the last 2 bones
    //     // cout << "last bone" <<endl;
    //         weiBuf.push_back(1); // ratio wrt distance
    //         weiBuf.push_back(0); // "
    //         bonBuf.push_back(num_bones-1);
    //         bonBuf.push_back(num_bones-2);
    //         weiBuf.push_back(1); // ratio wrt distance
    //         weiBuf.push_back(0); // "
    //         bonBuf.push_back(num_bones-1);
    //         bonBuf.push_back(num_bones-2);
    //     }
    //     else 
    //     {
    //         // cout << bone_index << " is bone index\t";
    //         prev_bone = floor(bone_index);
    //         next_bone = ceil(bone_index);

    //         // if the two bones are the same, give a weight of 1
    //         if ((next_bone - prev_bone) < 0.001) {
    //             weiBuf.push_back(1);
    //             weiBuf.push_back(0);
    //             weiBuf.push_back(1);
    //             weiBuf.push_back(0);
    //             // cout << "ok\t" << endl;
    //         }
    //         else {
    //             weiBuf.push_back(next_bone - bone_index);
    //             weiBuf.push_back(bone_index - prev_bone);
    //             weiBuf.push_back(next_bone - bone_index);
    //             weiBuf.push_back(bone_index - prev_bone);
    //             cout << next_bone - bone_index << " ";
    //             // cout << "nah\t";
    //         }
    //         bonBuf.push_back(next_bone);
    //         bonBuf.push_back(prev_bone);
    //         bonBuf.push_back(next_bone);
    //         bonBuf.push_back(prev_bone);
    //     }
    //     cout << prev_bone << " " << next_bone << endl;

    // }
}

// this is the animation that the vertices do, in x y z format
void ShapeSkin::loadSkeleton(std::shared_ptr<Skinner> skin)
{
    int nbones;
    nbones = this->num_bones;

    // read first line of points and quaternions
    glm::quat q; // quaternion
    glm::vec3 p; // position
    glm::mat4 E;
    PushDQ();
    for (int i = 0; i < nbones; ++i) {
        // we read the first line seperately in order to have the initial

        q.x = 0;
        q.y = 0;
        q.z = 0;
        q.w = 1;

        q = normalize(q);

        // bind_rotation.push_back(q);

        // do not move, just rotate
        p.x = bonLoc.at(i);
        p.y = 0;
        p.z = 0;

        // bind_translation.push_back(p);

        QuatTrans2UDQ(0, q, p);
            
        E = mat4_cast(q); // converting each 4-tuple to one 4x4 trans matrix
        E[3] = glm::vec4(p, 1.0f);
        skin->addBind(E);
    }
    
    for (int j = 0; j < 18; ++j) { // 18 animations, to get to 90 degrees
        // we read the the rest of the lines are not bind pose so yeah
        skin->pushAnime();
        PushDQ();
        for (int i = 0; i < nbones; ++i) {
            // rotate 5 degree across y axis

            //https://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToQuaternion/index.htm
            q.x = 0;
            // if (i == nbones-1) { // last bone
            //     q.y = 0;
            //     q.w = 1;
            // }
            // if (i == 0) { // first bone
            //     q.y = sin(PI / 144 * j);
            //     q.w = cos(PI / 144 * j);
            // }    
            if (i%2 == 0) { // even bone
                // q.y = sin(PI / 72 * j);
                // q.w = cos(PI / 72 * j);
                q.y = sin(PI / 144 * j);
                q.w = cos(PI / 144 * j);
            }
            else { // odd bone
                // q.y = -1*sin(PI / 72 * j);
                // q.w = cos(PI / 72 * j);
                q.y = -1*sin(PI / 144 * j);
                q.w = cos(PI / 144 * j);
            }
        
            q.z = 0;

            q = normalize(q);
            E = mat4_cast(q); // converting each 7-tuple to one 4x4 trans matrix

            // add rotation quaternion to vector with heirarchy for DQS
            if (i != 0)
                q = normalize(rotations.at(i-1) * q);
            rotations.push_back(q);


            // do not move, just rotate
            if (i == 0)
                p.x = bonLoc.at(i);
            else
                p.x = bonLoc.at(i);
            p.y = 0;
            p.z = 0;
            
            E[3] = glm::vec4(p, 1.0f);
            skin->addAnime(j, E);

            if (i != 0)
                p = translations.at(i-1) + p;
            translations.push_back(p);

            // create dual quaternion based on this data
            QuatTrans2UDQ(j+1, q, p);
        }

        
    }    
}

void ShapeSkin::LBSskinOn (std::shared_ptr<Skinner> skin, int k) 
{
    // cout << "LBS CALLED" << endl;

    // heirarchy applied to bones
    assert(num_bones != 0);
    // vector<glm::mat4> howdy;
    // // howdy.push_back(skin->getAnime(k, 0));
    // // for (int i = 1; i < num_bones; ++i) {
    // //     howdy.push_back(howdy.at(i-1) * skin->getAnime(k,i));
    // // }

    // iterates all the vertices
    for (int i = 0; i < posBuf.size()/3; ++i) {

        // creates clear dummy vectors
        glm::vec4 position(0.0);
        glm::vec4 normal(0.0);
        glm::vec4 x(posBuf.at(i*3),posBuf.at(3*i+1),posBuf.at(3*i+2), 1.0f);
        glm::vec4 y(norBuf.at(i*3),norBuf.at(3*i+1),norBuf.at(3*i+2), 0.0f);

        glm::mat4 temp (0.0f);
        // calculates skinned position and normal
        for (int j = 0; j < 2; ++j) {

            // i is vertex, j is bone, k is time
            int bone = bonBuf.at(2*i+j);

            // glm::vec4 dum1 = skin->getBind(bone) * x; // inverse bind matrix * initial vertex
            glm::mat4 dum1 = skin->getBind(bone); // inverse bind matrix * initial vertex
            // dum1 = howdy.at(bone) * dum1; // animation
            dum1 = skin->getAnime(k,bone) * dum1; // animation
            dum1 = weiBuf.at(2*i+j) * dum1; // apply weight of ith vertex on jth bone
            // position = position + dum1;
            temp += dum1;

            // glm::vec4 dum2 = skin->getBind(bone) * x; // inverse bind matrix * initial vertex
            // // glm::mat4 dum2 = skin->getBind(bone); // inverse bind matrix * initial vertex
            // // dum2 = howdy.at(bone) * dum1; // animation
            // dum2 = skin->getAnime(k,bone) * dum1; // animation
            // dum2 = weiBuf.at(2*i+j) * dum1; // apply weight of ith vertex on jth bone
            // normal = normal + dum1;
            // temp += dum1;
        }

        position = temp * x;
        normal = temp * y;
        
        // adjusts values of position and normal respectively
        skinnedPos.at(3*i) = position.x;
        skinnedPos.at(3*i+1) = position.y;
        skinnedPos.at(3*i+2) = position.z;
        
        skinnedNor.at(3*i) = normal.x;
        skinnedNor.at(3*i+1) = normal.y;
        skinnedNor.at(3*i+2) = normal.z;
    }
}

// based heavily on C source code from https://www.cs.utah.edu/~ladislav/dq/
// input: animation index 'j', unit quaternion 'q0', translation vector 't' 
// output: unit dual quaternion 'dq'
void ShapeSkin::QuatTrans2UDQ(int j, const glm::quat& r, const glm::vec3& t)
{
    glm::quat real, dual;
    // non-dual part (just copy q0):
    real = normalize(r);
    // dual part: https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/arithmetic/index.htm
    // dual.w = -0.5*(t.x*r.x + t.y*r.y + t.z*r.z);
    // dual.x = 0.5*( t.x*r.w + t.y*r.z - t.z*r.y);
    // dual.y = 0.5*(-t.x*r.z + t.y*r.w + t.z*r.x);
    // dual.z = 0.5*( t.x*r.y - t.y*r.x + t.z*r.w);
		dual.w = 0;
		dual.x = t.x;
		dual.y = t.y;
		dual.z = t.z;

		dual = dual * real * 0.5f;

    if (j == -1) {
        r1 = real;
        d1 = dual;
        return;
    }
    else if (j == -2) {
        r2 = real;
        d2 = dual;
        return;
    }
    addDQ(j, real, dual);

    // if (j == 0) {
    //     cout << "t " <<  t.x << " " << t.y << " " << t.z << " r " << r.w << " " << r.x << " " << r.y << " " << r.z << endl;
    // }
}

// influenced heavily on course Cg source code from https://www.cs.utah.edu/~ladislav/dq/dqs.cg
// input: real quaternion, dual quaternion
// output: transformation matrix
glm::mat4 ShapeSkin::DQToMatrix(glm::quat Qr, glm::quat Qd)
{	
	glm::mat4 M;
	float len2 = glm::dot(Qr, Qr);
	// cout << len2 << endl;
	// float w = Qr.x, x = Qr.y, y = Qr.z, z = Qr.w;
	float w = Qr.w, x = Qr.x, y = Qr.y, z = Qr.z;


    // cout << "DQToMatrix " << len2 << " " << Qr.w << " " << Qr.x << " " << Qr.y << " " << Qr.z << endl;
    
    // https://cs.gmu.edu/~jmlien/teaching/cs451/uploads/Main/dual-quaternion.pdf - pg 9
	M[0][0] = w*w + x*x - y*y - z*z; M[0][1] = 2*x*y + 2*w*z; M[0][2] = 2*x*z - 2*w*y;
	M[1][0] = 2*x*y - 2*w*z; M[1][1] = w*w + y*y - x*x - z*z; M[1][2] = 2*y*z + 2*w*x; 
	M[2][0] = 2*x*z + 2*w*y; M[2][1] = 2*y*z - 2*w*x; M[2][2] = w*w + z*z - x*x - y*y;

  glm::quat t = Qd * 2.0f * glm::conjugate(Qr);
  M[3][0] = t.x;
	M[3][1] = t.y;
	M[3][2] = t.z;

	M /= len2;

	
	return M;
}

void ShapeSkin::DQSskinOn(std::shared_ptr<Skinner> skin, int k) 
{
    // cout << "DQS CALLED" << endl;

    // https://www.cs.utah.edu/~ladislav/dq/dqs.cg - dqsAntipod
    // glm::quat r, d;

	// bone_translation.clear();
    // bone_translation.push_back(skin->getAnime(k, 0));
    // for (int i = 1; i < num_bones; ++i) {
    //     bone_translation.push_back(bone_translation.at(i-1) * skin->getAnime(k,i));
    // }

    // iterates all the vertices
    for (int i = 0; i < posBuf.size()/3; ++i) {

        // int bone1 = bonBuf.at(2*i);
        // int bone2 = bonBuf.at(2*i+1);

        // // cout << i << " " << bone1 << " " << weiBuf.at(2*i) << " " << bone2 << " " << weiBuf.at(2*i+1) << endl;

        // // glm::quat r1 = glm::conjugate(GetReal(0, bone1)) * GetReal(k+1, bone1);
        // // glm::quat d1 = glm::conjugate(GetDual(0, bone1)) * GetDual(k+1, bone1);
        // // glm::quat r2 = glm::conjugate(GetReal(0, bone2)) * GetReal(k+1, bone2);
        // // glm::quat d2 = glm::conjugate(GetDual(0, bone2)) * GetDual(k+1, bone2);

        // // multiple bind with E and parents
        // // convert to quat and vec3
        // // quattrans2uqd
        // // glm::mat4 temp = bone_translation.at(bone1) * skin->getBind(bone1);
        // glm::mat4 temp = skin->getAnime(k, bone1) * skin->getBind(bone1);
        // glm::vec3 trans = glm::vec3(temp[3][0], temp[3][1], temp[3][2]);
        // // cout << trans.x << " " << trans.y << " " << trans.z << endl;
        // glm::quat rot = quat_cast(temp);
        // QuatTrans2UDQ(-1, rot, trans);
        
        // temp = skin->getAnime(k, bone2) * skin->getBind(bone2);
        // // temp = bone_translation.at(bone2) * skin->getBind(bone2);
        // trans = glm::vec3(temp[3][0], temp[3][1], temp[3][2]);
        // rot = quat_cast(temp);
        // QuatTrans2UDQ(-2, rot, trans);

        
        // // glm::quat r1 = GetReal(k+1, bone1);
        // // glm::quat d1 = GetDual(k+1, bone1);
        // // glm::quat r2 = GetReal(k+1, bone2);
        // // glm::quat d2 = GetDual(k+1, bone2);


        // // to ensure shortest path rotation
        // if (glm::dot(r1, r2) < 0.0) {
        //     r2 *= -1.0;
        //     d2 *= -1.0;
        // }

        // // apply weights
        // // bone 1
        // r = weiBuf.at(2*i) * r1;
        // d = weiBuf.at(2*i) * d1;
        // // bone 2
        // r += weiBuf.at(2*i+1) * r2;
        // d += weiBuf.at(2*i+1) * d2;

        glm::mat4 trans_mat = DQS(skin, i, k);
        glm::vec4 x(posBuf.at(i*3),posBuf.at(3*i+1),posBuf.at(3*i+2), 1.0f);
        glm::vec4 y(norBuf.at(i*3),norBuf.at(3*i+1),norBuf.at(3*i+2), 0.0f);

        // if (i == 8 || i == 9) {
        //     cout << "DQS " << i << endl;
        //     cout << weiBuf.at(2*i) << " " << weiBuf.at(2*i+1) << endl;
        //     for (int a = 0; a < 4; ++a) {
        //             for (int b = 0; b < 4; ++b) {
        //                     cout << trans_mat[a][b] << " ";
        //             }
        //             cout << endl;
        //     }
        //     cout << endl;
        // }

        
        glm::vec4 position = trans_mat * x;
        glm::vec4 normal = trans_mat * y; 

        skinnedPos.at(3*i) = position.x;
        skinnedPos.at(3*i+1) = position.y;
        skinnedPos.at(3*i+2) = position.z;

        skinnedNor.at(3*i) = normal.x;
        skinnedNor.at(3*i+1) = normal.y;
        skinnedNor.at(3*i+2) = normal.z;

    }
}

glm::mat4 ShapeSkin::DQS(std::shared_ptr<Skinner> skin, int vertex, int k) {
    glm::quat r, d;
    int bone1 = bonBuf.at(2*vertex);
    int bone2 = bonBuf.at(2*vertex+1);

    // multiple bind with E and parents
    // convert to quat and vec3
    // quattrans2uqd
    glm::mat4 temp = skin->getAnime(k, bone1) * skin->getBind(bone1);
    glm::vec3 trans = glm::vec3(temp[3][0], temp[3][1], temp[3][2]);
    glm::quat rot = quat_cast(temp);
    QuatTrans2UDQ(-1, rot, trans); // saves to r1, d1
    
    temp = skin->getAnime(k, bone2) * skin->getBind(bone2);
    trans = glm::vec3(temp[3][0], temp[3][1], temp[3][2]);
    rot = quat_cast(temp);
    QuatTrans2UDQ(-2, rot, trans); // saves to r2, d2

    // to ensure shortest path rotation
    if (glm::dot(r1, r2) < 0.0) {
        r2 *= -1.0;
        d2 *= -1.0;
    }

    // apply weights
    // bone 1
    r = weiBuf.at(2*vertex) * r1;
    d = weiBuf.at(2*vertex) * d1;
    // bone 2
    r += weiBuf.at(2*vertex+1) * r2;
    d += weiBuf.at(2*vertex+1) * d2;

    glm::mat4 trans_mat = DQToMatrix(r, d);
    return trans_mat;
}

glm::mat4 ShapeSkin::LBS(std::shared_ptr<Skinner> skin, int vertex, int k) {
	// calculates skinned position and normal
	glm::mat4 lbs_mat(0.0f);
	for (int j = 0; j < 2; ++j) {

        // i is vertex, j is bone, k is time
        int bone = bonBuf.at(2*vertex+j);

        glm::mat4 dum1 = skin->getBind(bone);
        dum1 = skin->getAnime(k, bone) * dum1; // inverse bind matrix * initial vertex
        // dum1 = bone_translation.at(bone) * dum1; // inverse bind matrix * initial vertex
        dum1 = weiBuf.at(2*vertex+j) * dum1; // apply weight of ith vertex on jth bone

        lbs_mat += dum1;
    }
	// if (vertex == 8 || vertex == 9) {
	// 	cout << "LBS at " << vertex << endl;
	// 	for (int a = 0; a < 4; ++a) {
	// 			for (int b = 0; b < 4; ++b) {
	// 					cout << lbs_mat[a][b] << " ";
	// 			}
	// 			cout << endl;
	// 	}
	// 	cout << endl;
	// }
		return lbs_mat;
}

void ShapeSkin::skinOn(std::shared_ptr<Skinner> skin, int k, const float deform_factor)
{
    // cout << "COMBO CALLED" << endl;

	// cout << "deform is " << deform_factor << endl;
    // apply heirarchy of animations
    assert(num_bones != 0);
    bone_translation.clear();
    bone_translation.push_back(skin->getAnime(k, 0));
    for (int i = 1; i < num_bones; ++i) {
        bone_translation.push_back(bone_translation.at(i-1) * skin->getAnime(k,i));
    }

        // iterates all the vertices
    for (int i = 0; i < posBuf.size()/3; ++i) {

        // creates clear dummy vectors
        glm::vec4 position;
        glm::vec4 normal;
        glm::vec4 x(posBuf.at(i*3),posBuf.at(3*i+1),posBuf.at(3*i+2), 1.0f);
        glm::vec4 y(norBuf.at(i*3),norBuf.at(3*i+1),norBuf.at(3*i+2), 0.0f);

        
        // calculates skinned position and normal with an interpolation of LBS and DQS
				// glm::mat4 interpol = LBS(skin, i, k);
        glm::mat4 interpol = (1-deform_factor) * LBS(skin, i, k) + deform_factor * DQS(skin, i, k);
        position = interpol * x;
        normal = interpol * y;
        
        // adjusts values of position and normal respectively
        skinnedPos.at(3*i) = position.x;
        skinnedPos.at(3*i+1) = position.y;
        skinnedPos.at(3*i+2) = position.z;
        
        skinnedNor.at(3*i) = normal.x;
        skinnedNor.at(3*i+1) = normal.y;
        skinnedNor.at(3*i+2) = normal.z;
    }
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

