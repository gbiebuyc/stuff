/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:12:34 by nathan            #+#    #+#             */
/*   Updated: 2020/05/26 16:51:59 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VEC3_CLASS_H
# define VEC3_CLASS_H

#include <sstream>
#include <string>
#include <cmath>
#include <iostream>

class Matrix;
class Vec3 {
public:
	static const Vec3 ZERO;
	static const Vec3 ONE;
	Vec3( void );
	Vec3( float xx, float yy, float zz );
	Vec3( Vec3& copy );
	~Vec3(){}

	float getLength() const;
	std::string toString() const;
	void print() const;
	
	Vec3 operator+( const Vec3& rhs ) const;
	Vec3 operator-( const Vec3& rhs ) const;
	Vec3 operator*( const float scale ) const;

	float x, y, z;
private:
};

#endif
