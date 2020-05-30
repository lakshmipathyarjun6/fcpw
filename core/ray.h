#pragma once

#include "core.h"

namespace fcpw {

template<int DIM>
struct Ray {
	// constructor
	Ray(const Vector<DIM>& o_, const Vector<DIM>& d_, float tMax_=maxFloat):
		o(o_), d(d_), invD(cwiseInverse<DIM>(d)), tMax(tMax_) {}

	// operator()
	Vector<DIM> operator()(float t) const {
		return o + d*t;
	}

	// computes transformed ray
	Ray<DIM> transform(const Transform<DIM>& t) const {
		Vector<DIM> to = transformVector<DIM>(t, o);
		Vector<DIM> td = transformVector<DIM>(t, o + d*(tMax < maxFloat ? tMax : 1.0f)) - to;
		float tdNorm = norm<DIM>(td);

		return Ray<DIM>(to, td/tdNorm, tMax < maxFloat ? tdNorm : maxFloat);
	}

	// members
	Vector<DIM> o, d, invD;
	float tMax;
};

} // namespace fcpw
