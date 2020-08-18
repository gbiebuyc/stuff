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
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void Skeleton::init() {
	Cube::init();
}

void Skeleton::draw() {
	static unsigned int anim = 0;
	static unsigned int frame = 0;
	static float chestScale = 1.0f;
	static float headScale = 1.0f;
	static float rightUpperArmScale = 1.0f;
	static float rightLowerArmScale = 1.0f;
	static float leftUpperArmScale = 1.0f;
	static float leftLowerArmScale = 1.0f;
	static float rightUpperLegScale = 1.0f;
	static float rightLowerLegScale = 1.0f;
	static float leftUpperLegScale = 1.0f;
	static float leftLowerLegScale = 1.0f;
#define GREEN {  3/255.0, 102/255.0,   3/255.0}
#define BLUE  {  3/255.0,  76/255.0, 153/255.0}
#define BEIGE {224/255.0, 171/255.0, 148/255.0}
	static float chestColor[3] = GREEN;
	static float headColor[3] = BEIGE;
	static float rightUpperArmColor[3] = BEIGE;
	static float rightLowerArmColor[3] = BEIGE;
	static float leftUpperArmColor[3] = BEIGE;
	static float leftLowerArmColor[3] = BEIGE;
	static float rightUpperLegColor[3] = BLUE;
	static float rightLowerLegColor[3] = BLUE;
	static float leftUpperLegColor[3] = BLUE;
	static float leftLowerLegColor[3] = BLUE;
	ImGui::Text("Head         ");
	ImGui::SameLine(); ImGui::SliderFloat("##headScale", &headScale, 0.1f, 2.0f);
	ImGui::SameLine(); ImGui::ColorEdit3("##headColor", headColor, ImGuiColorEditFlags_NoInputs);
	ImGui::Text("Chest        ");
	ImGui::SameLine(); ImGui::SliderFloat("##chestScale", &chestScale, 0.1f, 2.0f);
	ImGui::SameLine(); ImGui::ColorEdit3("##chestColor", chestColor, ImGuiColorEditFlags_NoInputs);
	ImGui::Text("RightUpperArm");
	ImGui::SameLine(); ImGui::SliderFloat("##rightUpperArmScale", &rightUpperArmScale, 0.1f, 2.0f);
	ImGui::SameLine(); ImGui::ColorEdit3("##rightUpperArmColor", rightUpperArmColor, ImGuiColorEditFlags_NoInputs);
	ImGui::Text("RightLowerArm");
	ImGui::SameLine(); ImGui::SliderFloat("##rightLowerArmScale", &rightLowerArmScale, 0.1f, 2.0f);
	ImGui::SameLine(); ImGui::ColorEdit3("##rightLowerArmColor", rightLowerArmColor, ImGuiColorEditFlags_NoInputs);
	ImGui::Text("LeftUpperArm ");
	ImGui::SameLine(); ImGui::SliderFloat("##leftUpperArmScale", &leftUpperArmScale, 0.1f, 2.0f);
	ImGui::SameLine(); ImGui::ColorEdit3("##leftUpperArmColor", leftUpperArmColor, ImGuiColorEditFlags_NoInputs);
	ImGui::Text("LeftLowerArm ");
	ImGui::SameLine(); ImGui::SliderFloat("##leftLowerArmScale", &leftLowerArmScale, 0.1f, 2.0f);
	ImGui::SameLine(); ImGui::ColorEdit3("##leftLowerArmColor", leftLowerArmColor, ImGuiColorEditFlags_NoInputs);
	ImGui::Text("RightUpperLeg");
	ImGui::SameLine(); ImGui::SliderFloat("##rightUpperLegScale", &rightUpperLegScale, 0.1f, 2.0f);
	ImGui::SameLine(); ImGui::ColorEdit3("##rightUpperLegColor", rightUpperLegColor, ImGuiColorEditFlags_NoInputs);
	ImGui::Text("RightUpperLeg");
	ImGui::SameLine(); ImGui::SliderFloat("##rightLowerLegScale", &rightLowerLegScale, 0.1f, 2.0f);
	ImGui::SameLine(); ImGui::ColorEdit3("##rightLowerLegColor", rightLowerLegColor, ImGuiColorEditFlags_NoInputs);
	ImGui::Text("LeftUpperLeg ");
	ImGui::SameLine(); ImGui::SliderFloat("##leftUpperLegScale", &leftUpperLegScale, 0.1f, 2.0f);
	ImGui::SameLine(); ImGui::ColorEdit3("##leftUpperLegColor", leftUpperLegColor, ImGuiColorEditFlags_NoInputs);
	ImGui::Text("LeftLowerLeg ");
	ImGui::SameLine(); ImGui::SliderFloat("##leftLowerLegScale", &leftLowerLegScale, 0.1f, 2.0f);
	ImGui::SameLine(); ImGui::ColorEdit3("##leftLowerLegColor", leftLowerLegColor, ImGuiColorEditFlags_NoInputs);
	ImGui::Text("Anim %d", anim);
	if (ImGui::Button("Prev anim")) {
		anim--; frame=0;
	}
	if (ImGui::Button("Next anim")) {
		anim++; frame=0;
	}
	anim %= animations.size();
	vector<vector<float>>& motion = animations[anim];
	frame %= motion.size();

	Cube::setViewMat(Matrix::createTranslationMatrix(-5, 0, -15).exportForGL());

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
	mat = mat * Matrix::createScaleMatrix(1*chestScale, 3*chestScale, 1*chestScale);
	mat = mat * Matrix::createTranslationMatrix(0, .5, 0);
	Cube::draw(mat.exportForGL(), chestColor);

	// Head
#define HEAD_IDX 3*2
	mat = chestMat;
	mat = mat * Matrix::createTranslationMatrix(0, 3*chestScale, 0);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][HEAD_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][HEAD_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][HEAD_IDX+2]);
	mat = mat * rx * ry * rz;
	mat = mat * Matrix::createScaleMatrix(1.2*headScale, 1.2*headScale, 1.2*headScale);
	mat = mat * Matrix::createTranslationMatrix(0, .5, 0);
	Cube::draw(mat.exportForGL(), headColor);

	// Right arm
#define RIGHTUPPERARM_IDX 3*5
	mat = chestMat;
	mat = mat * Matrix::createTranslationMatrix(-.5*chestScale, 2.9*chestScale, 0);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][RIGHTUPPERARM_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][RIGHTUPPERARM_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][RIGHTUPPERARM_IDX+2]);
	mat = mat * rx * ry * rz;
	Matrix upperArm = mat * Matrix::createScaleMatrix(1.5*rightUpperArmScale, .5*rightUpperArmScale, .5*rightUpperArmScale);
	upperArm = upperArm * Matrix::createTranslationMatrix(-.5, 0, 0);
	Cube::draw(upperArm.exportForGL(), rightUpperArmColor);

	mat = mat * Matrix::createTranslationMatrix(-1.5*rightUpperArmScale, 0, 0);
#define RIGHTLOWERARM_IDX 3*6
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][RIGHTLOWERARM_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][RIGHTLOWERARM_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][RIGHTLOWERARM_IDX+2]);
	mat = mat * rx * ry * rz;
	Matrix lowerArm = mat * Matrix::createScaleMatrix(1.5*rightLowerArmScale, .5*rightLowerArmScale, .5*rightLowerArmScale);
	lowerArm = lowerArm * Matrix::createTranslationMatrix(-.5, 0, 0);
	Cube::draw(lowerArm.exportForGL(), rightLowerArmColor);

	// Left arm
#define LEFTUPPERARM_IDX 3*3
	mat = chestMat;
	mat = mat * Matrix::createTranslationMatrix(.5*chestScale, 2.9*chestScale, 0);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][LEFTUPPERARM_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][LEFTUPPERARM_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][LEFTUPPERARM_IDX+2]);
	mat = mat * rx * ry * rz;
	upperArm = mat * Matrix::createScaleMatrix(1.5*leftUpperArmScale, .5*leftUpperArmScale, .5*leftUpperArmScale);
	upperArm = upperArm * Matrix::createTranslationMatrix(.5, 0, 0);
	Cube::draw(upperArm.exportForGL(), leftUpperArmColor);

	mat = mat * Matrix::createTranslationMatrix(1.5*leftUpperArmScale, 0, 0);
#define LEFTLOWERARM_IDX 3*4
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][LEFTLOWERARM_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][LEFTLOWERARM_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][LEFTLOWERARM_IDX+2]);
	mat = mat * rx * ry * rz;
	lowerArm = mat * Matrix::createScaleMatrix(1.5*leftLowerArmScale, .5*leftLowerArmScale, .5*leftLowerArmScale);
	lowerArm = lowerArm * Matrix::createTranslationMatrix(.5, 0, 0);
	Cube::draw(lowerArm.exportForGL(), leftLowerArmColor);

	// Right leg
#define RIGHTUPPERLEG_IDX 3*9
	mat = chestMat;
	mat = mat * Matrix::createTranslationMatrix(-.25*chestScale, 0, 0);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][RIGHTUPPERLEG_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][RIGHTUPPERLEG_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][RIGHTUPPERLEG_IDX+2]);
	mat = mat * rx * ry * rz;
	Matrix upperLeg = mat * Matrix::createScaleMatrix(.5*rightUpperLegScale, 1.5*rightUpperLegScale, .5*rightUpperLegScale);
	upperLeg = upperLeg * Matrix::createTranslationMatrix(0, -.5, 0);
	Cube::draw(upperLeg.exportForGL(), rightUpperLegColor);

	mat = mat * Matrix::createTranslationMatrix(0, -1.5*rightUpperLegScale, 0);
#define RIGHTLOWERLEG_IDX 3*10
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][RIGHTLOWERLEG_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][RIGHTLOWERLEG_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][RIGHTLOWERLEG_IDX+2]);
	mat = mat * rx * ry * rz;
	Matrix lowerLeg = mat * Matrix::createScaleMatrix(.5*rightLowerLegScale, 1.5*rightLowerLegScale, .5*rightLowerLegScale);
	lowerLeg = lowerLeg * Matrix::createTranslationMatrix(0, -.5, 0);
	Cube::draw(lowerLeg.exportForGL(), rightLowerLegColor);

	// Left leg
#define LEFTUPPERLEG_IDX 3*7
	mat = chestMat;
	mat = mat * Matrix::createTranslationMatrix(.25*chestScale, 0, 0);
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][LEFTUPPERLEG_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][LEFTUPPERLEG_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][LEFTUPPERLEG_IDX+2]);
	mat = mat * rx * ry * rz;
	upperLeg = mat * Matrix::createScaleMatrix(.5*leftUpperLegScale, 1.5*leftUpperLegScale, .5*leftUpperLegScale);
	upperLeg = upperLeg * Matrix::createTranslationMatrix(0, -.5, 0);
	Cube::draw(upperLeg.exportForGL(), leftUpperLegColor);

	mat = mat * Matrix::createTranslationMatrix(0, -1.5*leftUpperLegScale, 0);
#define LEFTLOWERLEG_IDX 3*8
	rx = Matrix::createRotationMatrix(Matrix::RotationDirection::X, motion[frame][LEFTLOWERLEG_IDX+0]);
	ry = Matrix::createRotationMatrix(Matrix::RotationDirection::Y, motion[frame][LEFTLOWERLEG_IDX+1]);
	rz = Matrix::createRotationMatrix(Matrix::RotationDirection::Z, motion[frame][LEFTLOWERLEG_IDX+2]);
	mat = mat * rx * ry * rz;
	lowerLeg = mat * Matrix::createScaleMatrix(.5*leftLowerLegScale, 1.5*leftLowerLegScale, .5*leftLowerLegScale);
	lowerLeg = lowerLeg * Matrix::createTranslationMatrix(0, -.5, 0);
	Cube::draw(lowerLeg.exportForGL(), leftLowerLegColor);

	frame++;
}
