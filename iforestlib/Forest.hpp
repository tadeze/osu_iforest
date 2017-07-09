/*
 * Forest.h
 *
 *  Created on: Aug 12, 2015
 *      Author: tadeze
 */

#ifndef FOREST_H_
#define FOREST_H_
#include "utility.hpp"
#include "Tree.hpp"
#include "cincl.hpp"

class Forest {
public:
	std::vector<Tree*> trees;
	int ntree;
	bool rsample;
	int nsample;
    	bool stopheight;
    	int maxheight;
   	bool rangecheck;
	doubleframe* dataset;  // holds the original dataset
    	Forest()
	{
		rsample = false;
		ntree = 0;
		nsample = 256;
		dataset = NULL;

	};
Forest(int _ntree,doubleframe* _dataset,int _nsample,int _maxheight, bool _stopheight,bool _rsample)//bool _rangecheck)
    {
	ntree=_ntree;
    	dataset=_dataset;
	nsample=_nsample;
	stopheight=_stopheight;
	maxheight=_maxheight;
 	rsample = _rsample;
//	rangecheck=_rangecheck;	
//	Tree::rangeCheck = rangecheck;
    };
virtual ~Forest()
	{
		for (std::vector<Tree*>::iterator it = trees.begin(); it != trees.end();
				++it)
		{
			delete (*it);

		}
    }

	double instanceScore(double *inst);
	std::vector<double> AnomalyScore(doubleframe* df);
	std::vector<double> outOfBagScore(doubleframe* df);
	
	virtual std::vector<double> pathLength(double *inst);
	std::vector<std::vector<double> > pathLength(doubleframe* data);
	std::vector<double> meandepth();
	std::vector<double> ADtest(const std::vector<std::vector<double> > &pathlength, bool weighttotail);
	std::vector<double> importance(double *inst);
	virtual double getdepth(double *inst,Tree* tree);
	void getSample(std::vector<int> &sampleIndex,const int nsample,bool rSample,int nrow);
	struct larger
	{
		bool operator()(const std::pair<int,double> p1,const std::pair<int,double> p2)

		{
			return p1.second <p2.second;
		}
	};
    /* virtual function for adaptive forest*/
     virtual int adaptiveForest(double alpha,int stopLimit); 
    
     /*Fixed tree forest */
     virtual void fixedTreeForest(int epoch) {};

     virtual int confTree(double alpha,double rho,int init_tree);
	 /*
	  * @input two vector v1 and 
	 * @return proporation of intersection ,[0,1]
	 */


	double topcommonK(std::vector<int> &v1,std::vector<int> &v2)
	{
		std::vector<int> v3;
		std::sort(v1.begin(),v1.end());
		std::sort(v2.begin(),v2.end());
		std::set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
		return (double)v3.size()/(double)v1.size();
	}


};
#endif /* FOREST_H_ */