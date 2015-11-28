/*
 * Edge.h
 *
 *  Created on: 12 Kas 2015
 *      Author: Guner
 */

#ifndef EDGE_H_
#define EDGE_H_
#include "Vertex.h"
class Edge {
public:
	/*constructors*/

	Edge(Vertex s,Vertex d){
		source=s;
		dest=d;
		int x_dis=s.getX()-d.getX();
		int y_dis=(s.getY()-d.getY());
		int result=(x_dis*x_dis)+(y_dis*y_dis);
		weight = result;
	}

	/*return weight of edge*/
	inline unsigned int getWeight()const {
		return weight;
	}

	/*set weight*/
	inline void setWeight(unsigned int value){
		weight = value;
	}

	/*return source vertex*/
	inline int getSource()const {
		return source.getNo();
	}

	/*return destination vertex*/
	inline int getDest()const {
		return dest.getNo();
	}

	/*set source vertex*/
	inline void setSource(Vertex v1) {
		source = v1;
	}

	/*set destination vertex*/
	inline void setDest(Vertex v2) {
		dest = v2;
	}

	inline Vertex getSourceVertex(){return source;}

	inline Vertex getDestVertex(){return dest;}

	~Edge() {
	}
	// destructor
private:
	Vertex source;                 // a vertex on one side of the edge
	Vertex dest;                // a vertex on the other side of the edge
	unsigned int weight;              // the value of the edge ( or its weight )

};

#endif /* EDGE_H_ */
