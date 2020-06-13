/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"

template<typename PointT>
// Structure to represent node of kd tree
struct Node
{
	PointT point;
	int id;
	Node* left;
	Node* right;

	Node(PointT arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

template<typename PointT>
struct KdTree
{
	Node<PointT>* root;

	KdTree()
	: root(NULL)
	{}

	void insertHelper(Node<PointT>** node, uint depth, PointT point, int id) {
		if(*node == NULL) {
			*node = new Node<PointT>(point, id);
		} else {
			uint cd = depth % 3;

			if(cd == 0) {
				if(point.x < ((*node)->point.x)) {
					insertHelper(&((*node)->left), depth+1, point, id);
				} else {
					insertHelper(&((*node)->right), depth+1, point, id);
				}
			} else {
				if(point.y < ((*node)->point.y)) {
					insertHelper(&((*node)->left), depth+1, point, id);
				} else {
					insertHelper(&((*node)->right), depth+1, point, id);
				}
			}
			
		}
	}

	void insert(PointT point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
		insertHelper(&root,0, point, id);

	}

	void searchHelper(PointT target, Node<PointT>* node, int depth, float distanceTol, std::vector<int>& ids) {
		if(node!= NULL){
			if( (node->point.x>=(target.x-distanceTol) &&node->point.x<=(target.x+distanceTol)) && (node->point.y>=(target.y-distanceTol) &&node->point.y<=(target.y+distanceTol))) {
				float distance = sqrt((node->point.x-target.x)*(node->point.x-target.x) + (node->point.y-target.y)*(node->point.y-target.y));
				if(distance <= distanceTol) {
					ids.push_back(node->id);
				}
			}

			if(depth%3 == 0) {
				if(target.x-distanceTol < node->point.x) {
					searchHelper(target, node->left, depth+1, distanceTol, ids);
				}
				if(target.x+distanceTol > node->point.x) {
					searchHelper(target, node->right, depth+1, distanceTol, ids);
				}
			} else {
				if(target.y-distanceTol < node->point.y) {
					searchHelper(target, node->left, depth+1, distanceTol, ids);
				}
				if(target.y+distanceTol > node->point.y) {
					searchHelper(target, node->right, depth+1, distanceTol, ids);
				}
			}
			
			
		}
	}
	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(PointT target, float distanceTol)
	{
		std::vector<int> ids;
		searchHelper(target, root, 0, distanceTol, ids);
		return ids;
	}
	

};




