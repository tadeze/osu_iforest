/*
 * Tree.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: Tadeze
 */
#include "classes.hpp"
#include "utility.h"
using namespace std;
void Tree::iTree(Data data, int height,int maxheight)
{   
	this->depth=height;
	// Set size of the node
	nodeSize = data.nrows;
	if(data.nrows<=1 || this->depth>maxheight)
	  {  
		 this->isLeaf=true;
		 return;
	  }
	  //compute min and max of the attribute
	vector<vector<double> > minmax;//[2][data.ncols];
	 for(int j=0;j<data.ncols;j++) //look better design for performance
	 {
		 //minmax[0][j]=data.data[0][j];
		 //minmax[1][j]=minmax[0][j];
	vector<double> tmp;
        tmp.push_back( data.data[0][j]);
  	tmp.push_back( data.data[0][j] );
	minmax.push_back(tmp); //initialize max and min to random value
	 }
	 

	for(int i=0;i<data.nrows;i++) 
	{
	    vector<double> inst= data.data.at(i);
		 for(int j=0;j<data.ncols;j++)
		 {
			 if(inst[j]<minmax[j].at(0))
				 minmax[j].at(0)=inst[j];
			 if(inst[j]>minmax.at(j).at(1))
				 minmax[j].at(1)=inst[j];
		 }

	 }

	  //use only valid attributes
	 vector<int> attributes;
	 for(int j=0;j<data.ncols;j++)
	 {
		 if(minmax[j][0]<minmax[j][1])
		 {
			 attributes.push_back(j);
		 }
	 }
	 if(attributes.size()==0)
		 return ;

	 //Randomly pick an attribute and a split point
	 int randx=randomI(0,attributes.size());
	this->splittingAtt=attributes[randx];
	ffile<<"splitting att\t"<<this->splittingAtt<<endl;
	//cout<<randx<<"\t Att "<<randAtt<<endl;
	this->splittingPoint = randomD(minmax[this->splittingAtt][0],minmax[this->splittingAtt][1]); //(double) rand()/(RAND_MAX+1) *(minmax[1][this->splittingAtt] - minmax[0][this->splittingAtt]);
	vector<vector<double> > lnodeData;
	vector<vector<double> > rnodeData;

	//Split the node into two
	 for(int j=0;j<data.nrows;j++)
	 {
		 if(data.data[j][splittingAtt] > splittingPoint)
		 {
			 lnodeData.push_back(data.data[j]);
		 }
		 else
		 {
			 rnodeData.push_back(data.data[j]);
		 }
	 }

	Data dataL ={data.ncols,(int)lnodeData.size(),lnodeData};
	leftChild= new Tree();//&dataL,height+1,maxheight);
	leftChild->parent=this;
	leftChild->iTree(dataL,this->depth+1,maxheight);

	Data dataR= {data.ncols,(int)rnodeData.size(),rnodeData};
	rightChild= new Tree();//&dataR,height+1,maxheight);
	rightChild->parent=this;
	rightChild->iTree(dataR,this->depth +1,maxheight);



}

double Tree::pathLength(vector<double> inst)
{
//cout<<this->depth;
    if (this->isLeaf)
    {
      return avgPL(this->nodeSize);
    }

    if (inst[this->splittingAtt] > this->splittingPoint) {

      return this->leftChild->pathLength(inst) +1.0;

    }
    else {
      return this->rightChild->pathLength(inst) +1.0;
    }
}




