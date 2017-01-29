#pragma once

class Projection {
public:
	Projection(double mi, double ma) :min(mi), max(ma) {}
	~Projection() {}
	double min;
	double max;
	bool overlap(const Projection& other) const;
	double getOverlap(const Projection& other) const;
};