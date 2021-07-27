#include<bits/stdc++.h>

using namespace std;


#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define FOR(a, c) for (int(a) = 0; (a) < (c); (a)++)
#define FORL(a, b, c) for (int(a) = (b); (a) <= (c); (a)++)
#define FORR(a, b, c) for (int(a) = (b); (a) >= (c); (a)--)
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define F first
#define S second
#define max(a, b) (a < b ? b : a)
#define min(a, b) ((a > b) ? b : a)

typedef vector<int> vi;
typedef pair<int, int> pi;
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
// typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.F); cerr << ","; _print(p.S); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}


class binarySearchTree{
public:
	int data;
	int height;
	binarySearchTree* left;
	binarySearchTree* right;
	 binarySearchTree(int data){
	 	this->data = data;
	 	this->height = 1;
	 	left = NULL;
	 	right = NULL;
	 }
	~ binarySearchTree(){
		delete left;
		delete right;
	}
	
};

///// Utilites Function

int height(binarySearchTree* root){
	if(!root) return 0;
	return root->height;
}

int getBalance(binarySearchTree* root){
	if(!root) return 0;

	return height(root->left) - height(root->right);
}

void levelOrderTraversal(binarySearchTree* root){

	if(!root) return;

	queue<binarySearchTree*> node;

	node.push(root);

	while(!node.empty()){

		int count = node.size();

		while(count--){
			binarySearchTree* ptr = node.front();
			node.pop();

			cout<<ptr->data<<" ";

			if(ptr->left) node.push(ptr->left);

			if(ptr->right) node.push(ptr->right);
		}
		cout<<"\n";

	} 
}

////Rotation in AVL Tree

//   1.LeftRotate
binarySearchTree* leftRotate(binarySearchTree* x){

	binarySearchTree* y = x->right;
	binarySearchTree* templeft = y->left;

	//Rotation
	y->left = x;
	x->right = templeft;

	x->height = max(height(x->left),height(x->right))+1;

	y->height = max(height(y->left),height(y->right))+1;

	return y;
}

///   2. Right Rotate
binarySearchTree* rightRotate( binarySearchTree* y){

	binarySearchTree* x = y->left;
	binarySearchTree* T2 = x->right;

	///Rotation
	x->right = y;
	y->left = T2;

	y->height = max(height(y->left),height(y->right)) + 1;

	x->height = max(height(x->left),height(x->right)) + 1;

	return x;
}
 

////// insertion With AVL Tree 
binarySearchTree* insert( binarySearchTree* root, int data){

	if(!root){
		binarySearchTree* temp = new binarySearchTree(data);
		return temp;
	}

	if( data < root->data){
		root->left = insert(root->left,data);
	}
	else if( data > root->data){
		root->right = insert(root->right,data);
	}
 else{
		return root;
	}

	root->height = 1 + max( height(root->left),height(root->right));

	int balance  = getBalance(root);

    ///Left Left Rotation
    if( balance > 1 && data < root->left->data){
    	return rightRotate(root);
    }

    /// Right Right Rotation
    if( balance < -1 && data > root->right->data){
    	return leftRotate(root);
    }

    /// Left Right Rotation
    if( balance > 1 && data > root->left->data){
    	root->left = leftRotate(root->left);
    	return rightRotate(root);
    }

    /// Right Left Rotation
    if( balance < -1 && data < root->right->data){
    	root->right = rightRotate(root->right);
    	return leftRotate(root);
    }

    return root;
}

binarySearchTree* deleteNode( binarySearchTree* root,int data){

	if( !root){
		return root;
	}
	if( data < root->data){
		root->left = deleteNode(root->left,data);
	}
	else if( data > root->data){
		root->right = deleteNode( root->right,data);
	}
	else{

       if( (root->left == NULL) || (root->right == NULL) )
        {
            binarySearchTree *temp = root->left ? root->left : root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of
                           // the non-empty child
            delete(temp);
        }
        else
        {

            binarySearchTree* temp = root->right;
            while(temp->left != NULL){
            	temp = temp->left;
            }
 

            root->data = temp->data;
 
            // Delete the inorder successor
            root->right = deleteNode(root->right,temp->data);
        }
	}

	if( root == NULL) return root;

	root->height = max( height(root->left),height(root->right)) + 1;

	int balance = getBalance(root);

	////Rotation

	/////Left Left Rotation
	if( balance > 1 && getBalance(root->left) >= 0){
		return rightRotate(root);
	}
	///// Right Right Rotation
	if( balance < -1 &&  getBalance(root->right) <= 0){
		return leftRotate(root);
	}

	///// Left Right Rotation
	if( balance > 1 && getBalance( root->left) < 0){
		root->left = rightRotate( root->left);
		return rightRotate( root);
	}

	//// Right Left Rotation
	if( balance < -1 && getBalance( root->right) > 0){
		root->right = rightRotate( root->right);
		return leftRotate( root);
	}

	return root;

}

int main() {
#ifndef ONLINE_JUDGE
  freopen("Error.txt", "w", stderr);
#endif
fastio();
 
 binarySearchTree* root;
 int n;
 cin>>n;
 while(n--){
 	int x;
 	cin>>x;
 	root = insert(root,x);
 }

 // preOrder(root);
 cout<<"\n Before Deletion :";
 cout<<"\n\t Level Order Traversal \n";

 levelOrderTraversal(root);

 deleteNode(root,10);

 cout<<"\n After Deletion :";
 cout<<"\n\t Level Order Traversal \n";

 levelOrderTraversal(root);

	
return 0;
}
/*
Input :
9
8 3 10 1 6 14 4 7 13 

Output:

 Before Deletion :
	 Level Order Traversal 
8 
3 13 
1 6 10 14 
4 7 

 After Deletion :
	 Level Order Traversal 
8 
3 13 
1 6 14 
4 7 
*/
