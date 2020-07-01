/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:07:43 by nathan            #+#    #+#             */
/*   Updated: 2020/05/26 10:04:50 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MATRIX_CLASS_H
# define MATRIX_CLASS_H
#include <vector>
#include <string>
#include <sstream>
#include <GL/gl.h>

class Matrix {
public:
	enum RotationDirection {
		X,
		Y,
		Z
	};
	Matrix( void );// also is identity matrix
	Matrix( std::vector<std::vector<float>> dataParam );
	Matrix( const Matrix& copy );

	static Matrix createProjMatrix( float fov, float aspect, float near, float far );// takes fov as degree
	static Matrix createTranslationMatrix( float x, float y, float z );
	static Matrix createScaleMatrix( float x, float y, float z );
	static Matrix createRotationMatrix( RotationDirection dir, float angle ); //takes angle as degree

	~Matrix( void );
	GLfloat* exportForGL(  );
	Matrix operator*( const Matrix& rhs );
	void print();
	std::string toString( std::vector<std::vector<float>> dataParam );

private:
	std::vector<std::vector<float>> data;
	std::vector<GLfloat> exportData;
};

#endif
