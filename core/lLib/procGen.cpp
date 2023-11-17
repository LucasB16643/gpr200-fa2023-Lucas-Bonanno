#include "procGen.h"
#include <stdlib.h>

namespace lLib {
	ew::MeshData createSphere(float radius, int numSegments) {
		ew::MeshData data;
		ew::Vertex v;
		float thetaStep = (2 * (3.14)) / numSegments;
		float phiStep = (3.14) / numSegments;

		for (int row = 0; row <= numSegments; row++) {
			float phi = row * phiStep;

			for (int col = 0; col <= numSegments; col++) {
				float theta = col * thetaStep;

				v.pos.x = radius * sin(phi) * cos(theta);
				v.pos.y = radius * cos(phi);
				v.pos.z = radius * sin(phi) * sin(theta);
				v.normal = ew::Normalize(v.pos);
				v.uv = ew::Vec2(sin(phi) * cos(theta), sin(phi) * sin(theta));
				data.vertices.push_back(v);

			}
		}
		int poleStart = 0;
		int sideStart = numSegments + 1;

		for (size_t i = 0; i < numSegments; i++) {
			data.indices.push_back(sideStart + i);
			data.indices.push_back(poleStart + i); //Pole
			data.indices.push_back(sideStart + i + 1);
		}

		int columns = numSegments + 1;
			//Skip top and bottom poles
		for (int row = 1; row < numSegments - 1; row++) {
			for (int col = 0; col < numSegments; col++) {
				int start = row * columns + col;
					//Triangle 1
					data.indices.push_back(start);
				data.indices.push_back(start + 1);
				data.indices.push_back(start + columns);
					//Triangle 2…
				data.indices.push_back(start + 1);
				data.indices.push_back(start + columns);
				data.indices.push_back(start + columns + 1);
			}
		}
		return data;
	}
	ew::MeshData createCylinder(float height, float radius, int numSegments) {
		float topY = height / 2;
		float bottemY = -topY;
		int vCounter = 0;
		int sideStart;
		ew::MeshData data;
		ew::Vertex top;
		ew::Vertex bottem;
		ew::Vertex v;
		top.pos.x = 0;
		top.pos.y = topY;
		top.pos.z = 0;
		top.normal.y = topY;
		data.vertices.push_back(top);
		vCounter++;
		
		float thetaStep = (2 * (3.14)) / numSegments;

		for (int i = 0; i <= numSegments; i++) {
			float theta = i * thetaStep;
			v.pos.x = cos(theta) * radius;
			v.pos.z = sin(theta) * radius;
			v.pos.y = topY; //or bottomY
			v.normal.y = topY;
			data.vertices.push_back(v);
			vCounter++;
			
		}
		sideStart = vCounter;
		for (int i = 0; i <= numSegments; i++) {
			float theta = i * thetaStep;
			v.pos.x = cos(theta) * radius;
			v.pos.z = sin(theta) * radius;
			v.pos.y = topY; //or bottomY
			v.normal = ew::Normalize(v.pos);
			
			data.vertices.push_back(v);
			vCounter++;
		}
		for (int i = 0; i <= numSegments; i++) {
			float theta = i * thetaStep;
			v.pos.x = cos(theta) * radius;
			v.pos.z = sin(theta) * radius;
			v.pos.y = bottemY; //or bottomY
			v.normal = ew::Normalize(v.pos);
			data.vertices.push_back(v);
			vCounter++;
		}

		for (int i = 0; i <= numSegments; i++) {
			float theta = i * thetaStep;
			v.pos.x = cos(theta) * radius;
			v.pos.z = sin(theta) * radius;
			v.pos.y = bottemY; //or bottomY
			v.normal.x = 0;
			v.normal.y = bottemY;
			v.normal.z = 0;
			data.vertices.push_back(v);
			vCounter++;
		}
		

		
		bottem.pos.x = 0;
		bottem.pos.y = bottemY;
		bottem.pos.z = 0;
		bottem.normal.y = bottemY;
		data.vertices.push_back(bottem);
		vCounter++;

		int start = 0;
		int center = 0;
		for (int i = 0; i <= numSegments; i++) {
			data.indices.push_back(start + i);
			data.indices.push_back(center);
			data.indices.push_back(start + i + 1);
		}
		
		start = vCounter - 1;
		center = vCounter - 1;
		for (int i = 0; i <= numSegments; i++) {
			data.indices.push_back(start - i);
			data.indices.push_back(center);
			data.indices.push_back(start - i - 1);
		}
		//index of first top ring vertex
		int columns = numSegments + 1;
		for (int i = 0; i < columns; i++) {
			start = sideStart + i;
				//Triangle 1
			data.indices.push_back(start);
			data.indices.push_back(start + 1);
			data.indices.push_back(start + columns);
				//Triangle 2…
			data.indices.push_back(start + columns);
			data.indices.push_back(start + columns + 1);
			data.indices.push_back(start + 1);
		}
		
		return data;
	}
	ew::MeshData createPlane(float size, int subdivisions) {
		ew::MeshData data;
		
		for (float row = 0; row <= subdivisions; row++) {
			for (float col = 0; col <= subdivisions; col++) {
				ew::Vertex v;
				v.pos.x = size * (col / subdivisions);
				v.pos.z = -size * (row / subdivisions);
				v.normal.y = 1;
				v.uv = ew::Vec2(col/subdivisions, row/subdivisions);
				data.vertices.push_back(v);
			}
		}
		int columns = subdivisions + 1;
			for (int row = 0; row < subdivisions; row++) {
				for (int col = 0; col < subdivisions; col++) {
					int start = row * columns + col;
						//Bottom right triangle
					data.indices.push_back(start);
					data.indices.push_back(start + 1);
					data.indices.push_back(start + columns + 1);
						//Top left triangle…
					data.indices.push_back(start + columns + 1);
					data.indices.push_back(start + columns);
					data.indices.push_back(start);
				}
			}
		return data;
	}
}