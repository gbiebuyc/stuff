/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Skeleton.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 05:32:43 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/05/26 05:32:43 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Skeleton.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include "Matrix.hpp"
#include "Window.hpp"
#include "math.h"
#include "animations.hpp"

void Skeleton::init() {
	Cube::init();
}

void Skeleton::draw(unsigned int anim, unsigned int frame) {
	anim %= animations.size();
	vector<vector<float>>& motion = animations[anim];
	frame %= motion.size();
	glfwSetWindowTitle(Window::getWindow(), ("frame " + to_string(frame) + ", Anim " + to_string(anim)).c_str());

	Cube::setViewMat(Matrix::createTranslationMatrix(0, 0, -10).exportForGL());
#define GREEN {  3/255.0, 102/255.0,   3/255.0}
#define BLUE  {  3/255.0,  76/255.0, 153/255.0}
#define BEIGE {224/255.0, 171/255.0, 148/255.0}

	Matrix mat, rx, ry, rz;

	// Chest
	mat = Matrix();
#define CHEST_POS_IDX 3*0
	mat = mat * Matrix::createTranslationMatrix(motion[frame][CHEST_POS_IDX+0] * 0.05,
			motion[frame][CHEST_POS_IDX+1] * 0.05, motion[frame][CHEST_POS_IDX+2] * 0.05);
#define CHEST_ROT_IDX 3*1
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][CHEST_ROT_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][CHEST_ROT_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][CHEST_ROT_IDX+2]);
	mat = mat * rx * ry * rz;
	Matrix chestMat = mat;
	mat = mat * Matrix::createScaleMatrix(1, 3, 1);
	mat = mat * Matrix::createTranslationMatrix(0, .5, 0);
	Cube::draw(mat.exportForGL(), GREEN);

	// Head
#define HEAD_IDX 3*2
	mat = chestMat;
	mat = mat * Matrix::createTranslationMatrix(0, 3, 0);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][HEAD_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][HEAD_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][HEAD_IDX+2]);
	mat = mat * rx * ry * rz;
	mat = mat * Matrix::createScaleMatrix(1.2, 1.2, 1.2);
	mat = mat * Matrix::createTranslationMatrix(0, .5, 0);
	Cube::draw(mat.exportForGL(), BEIGE);

	// Right arm
#define RIGHTUPPERARM_IDX 3*5
	mat = chestMat;
	mat = mat * Matrix::createTranslationMatrix(-.5, 2.9, 0);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][RIGHTUPPERARM_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][RIGHTUPPERARM_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][RIGHTUPPERARM_IDX+2]);
	mat = mat * rx * ry * rz;
	Matrix upperArm = mat * Matrix::createScaleMatrix(1.5, .5, .5) * Matrix::createTranslationMatrix(-.5, 0, 0);
	Cube::draw(upperArm.exportForGL(), BEIGE);
	mat = mat * Matrix::createTranslationMatrix(-1.5, 0, 0);
#define RIGHTLOWERARM_IDX 3*6
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][RIGHTLOWERARM_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][RIGHTLOWERARM_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][RIGHTLOWERARM_IDX+2]);
	mat = mat * rx * ry * rz;
	Matrix lowerArm = mat * Matrix::createScaleMatrix(1.5, .5, .5) * Matrix::createTranslationMatrix(-.5, 0, 0);
	Cube::draw(lowerArm.exportForGL(), BEIGE);

	// Left arm
#define LEFTUPPERARM_IDX 3*3
	mat = chestMat;
	mat = mat * Matrix::createTranslationMatrix(.5, 2.9, 0);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][LEFTUPPERARM_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][LEFTUPPERARM_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][LEFTUPPERARM_IDX+2]);
	mat = mat * rx * ry * rz;
	upperArm = mat * Matrix::createScaleMatrix(1.5, .5, .5) * Matrix::createTranslationMatrix(.5, 0, 0);
	Cube::draw(upperArm.exportForGL(), BEIGE);
	mat = mat * Matrix::createTranslationMatrix(1.5, 0, 0);
#define LEFTLOWERARM_IDX 3*4
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][LEFTLOWERARM_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][LEFTLOWERARM_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][LEFTLOWERARM_IDX+2]);
	mat = mat * rx * ry * rz;
	lowerArm = mat * Matrix::createScaleMatrix(1.5, .5, .5) * Matrix::createTranslationMatrix(.5, 0, 0);
	Cube::draw(lowerArm.exportForGL(), BEIGE);

	// Right leg
#define RIGHTUPPERLEG_IDX 3*9
	mat = chestMat;
	mat = mat * Matrix::createTranslationMatrix(-.25, 0, 0);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][RIGHTUPPERLEG_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][RIGHTUPPERLEG_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][RIGHTUPPERLEG_IDX+2]);
	mat = mat * rx * ry * rz;
	Matrix upperLeg = mat * Matrix::createScaleMatrix(.5, 1.5, .5) * Matrix::createTranslationMatrix(0, -.5, 0);
	Cube::draw(upperLeg.exportForGL(), BLUE);
	mat = mat * Matrix::createTranslationMatrix(0, -1.5, 0);
#define RIGHTLOWERLEG_IDX 3*10
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][RIGHTLOWERLEG_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][RIGHTLOWERLEG_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][RIGHTLOWERLEG_IDX+2]);
	mat = mat * rx * ry * rz;
	Matrix lowerLeg = mat * Matrix::createScaleMatrix(.5, 1.5, .5) * Matrix::createTranslationMatrix(0, -.5, 0);
	Cube::draw(lowerLeg.exportForGL(), BLUE);

	// Left leg
#define LEFTUPPERLEG_IDX 3*7
	mat = chestMat;
	mat = mat * Matrix::createTranslationMatrix(.25, 0, 0);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][LEFTUPPERLEG_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][LEFTUPPERLEG_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][LEFTUPPERLEG_IDX+2]);
	mat = mat * rx * ry * rz;
	upperLeg = mat * Matrix::createScaleMatrix(.5, 1.5, .5) * Matrix::createTranslationMatrix(0, -.5, 0);
	Cube::draw(upperLeg.exportForGL(), BLUE);
	mat = mat * Matrix::createTranslationMatrix(0, -1.5, 0);
#define LEFTLOWERLEG_IDX 3*8
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][LEFTLOWERLEG_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][LEFTLOWERLEG_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][LEFTLOWERLEG_IDX+2]);
	mat = mat * rx * ry * rz;
	lowerLeg = mat * Matrix::createScaleMatrix(.5, 1.5, .5) * Matrix::createTranslationMatrix(0, -.5, 0);
	Cube::draw(lowerLeg.exportForGL(), BLUE);
}
