/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:12:31 by nathan            #+#    #+#             */
/*   Updated: 2020/05/26 16:52:01 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vec3.hpp"


Vec3::Vec3( void )
{
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3( float xx, float yy, float zz)
{
	x = xx;
	y = yy;
	z = zz;
}

Vec3::Vec3( Vec3& copy)
{
	x = copy.x;
	y = copy.y;
	z = copy.z;
}

float Vec3::getLength() const
{
	return sqrtf( x * x + y * y + z * z);
}

std::string Vec3::toString() const
{
	std::stringstream ss;
	ss.precision(2); // print only 2 first decimals
	ss << std::fixed; // put precision for 0.00 too
	ss << "{";
	ss.width(4);
	ss << " " << x;
	ss << " " << y;
	ss << " " << z;
	ss << " }";
	ss << std::endl;
	return ss.str();
}

void Vec3::print() const
{
	std::cout << toString();
}

Vec3 Vec3::operator+(const Vec3& rhs) const
{
	Vec3 newVector( x + rhs.x, y + rhs.y, z + rhs.z );
	return newVector;
}

Vec3 Vec3::operator-(const Vec3& rhs) const
{
	Vec3 newVector( x - rhs.x, y - rhs.y, z - rhs.z );
	return newVector;
}

Vec3 Vec3::operator*(const float scale) const
{
	Vec3 newVector( x * scale, y * scale, z * scale );
	return newVector;
}

const Vec3 Vec3::ZERO(0, 0 ,0);
const Vec3 Vec3::ONE(1, 1 ,1);
