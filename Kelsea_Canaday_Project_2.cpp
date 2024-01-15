// Kelsea_Canaday_Project_2.cpp
// Kelsea Canaday
// COP4315
// 10/26/23

#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

// files for in.txt and out.txt
FILE *infile = nullptr;
FILE *outfile = nullptr;

// given itemNode class 
class itemNode {
    public:
    string name; // changed name from char to string
    int count;
    
    itemNode *left;
    itemNode *right;

    itemNode() {
        count = 0;
    }

  itemNode(string itemName, int population) {
      name = itemName;
      count = population;
      left = NULL;
      right = NULL;
  }
};

// given treeNameNode class
class treeNameNode {
    public:
    string name;
    treeNameNode *left;
    treeNameNode *right;
    itemNode *theTree;

    treeNameNode() {
        theTree = NULL;
        left = NULL;
        right = NULL;
    }

    treeNameNode(string treeName) {
      name = treeName;
      theTree = NULL;
        left = NULL;
        right = NULL;
  }
};

// Binary Search Tree insert and print functions that have been implemented in class
itemNode *insert(itemNode *root, string itemName, int population);

treeNameNode *insert(treeNameNode *root, string treeName);

void inorder(itemNode *root);

void inorder(treeNameNode *root);



// query functions 
void search(treeNameNode *tree, string category, string name);

void item_before(treeNameNode *tree, string category, string name);

void height_balance(treeNameNode *tree, string category);

void count(treeNameNode *tree, string category);



// required functions 
void traverse_in_traverse(treeNameNode *root);

treeNameNode *searchNameNode(treeNameNode *root, string name);

treeNameNode *buildNameTree();



// insert function from itemNode class using a root, an item name, and a population count. insert into the itemNode, returns new root
itemNode *insert (itemNode *root, string itemName, int population) {
  if (root == nullptr) {
    return new itemNode (itemName, population);
    }
  int comparison = root->name.compare (itemName);
  if (comparison > 0) {
    root->left = insert (root->left, itemName, population);
  }
  else {
    root->right = insert (root->right, itemName, population);
  }
  return root;
}

  // insert function from treeNameNode class using a root and a tree name. insert into the treeNameNode, returns new root
treeNameNode *insert (treeNameNode * root, string treeName) {
  if (root == nullptr) {
    return new treeNameNode (treeName);
    }
    
  int comparison = root->name.compare (treeName); 
  if (comparison > 0) {
    root->left = insert (root->left, treeName);
  }
  else {
    root->right = insert (root->right, treeName);
    }
  return root;
}

  //inorder traversal of itemNode root
void inorder (itemNode *root) {
  if (root == nullptr) {
    return;
  }

  inorder (root->left);
  printf ("%s ", root->name.c_str ());
  fprintf (outfile, "%s ", root->name.c_str ());
  inorder (root->right);
}

  //inorder traversal of treeNameNode root
void inorder (treeNameNode *root) {
  if (root == nullptr) {
    return;
  }

  inorder (root->left);
  printf ("%s ", root->name.c_str ());
  fprintf (outfile, "%s ", root->name.c_str ());
  inorder (root->right);
}

  // recursive helper function to find node for search() to print 
itemNode *find (itemNode *root, string name) {
  if (root == nullptr) {
    return root;
  }

  const int compare = root->name.compare (name);
  if (compare > 0) {
    return find (root->left, name);
  }
  else if (compare < 0) {
    return find (root->right, name);
  }
  else {
    return root;
  }
}

  //prints node info of name, or it does not exist 
void search (treeNameNode *tree, string category, string name) {
    
  // find category first
  tree = searchNameNode (tree, category);
  if (tree == nullptr) {
      printf ("%s does not exist\n", category.c_str ());
      fprintf (outfile, "%s does not exist\n", category.c_str ());
      return;
    }

  itemNode *item = find(tree->theTree, name);

  //print info of item 
  if (item != nullptr) {
      printf ("%d %s found in %s\n", item->count, name.c_str (),
	      category.c_str ());
      fprintf (outfile, "%d %s found in %s\n", item->count, name.c_str (),
	       category.c_str ());
    }
  else {
      printf ("%s not found in %s\n", name.c_str (), category.c_str ());
      fprintf (outfile, "%s not found in %s\n", name.c_str (),
	       category.c_str ());
    }
}

// recursive helper function for item_before's value
int nLessthan (itemNode * root, string name) {
  if (root == nullptr) {
    return 0;
  }
  int compare = root->name.compare (name);
  // add 1 for root
  return nLessthan (root->left, name) + ((compare < 0) ? 1 + nLessthan (root->right, name) : 0);
}

  // prints the number of items in BST which come alphabetically before given name
void item_before (treeNameNode *tree, string category, string name) {
    
  tree = searchNameNode (tree, category);
  if (tree == nullptr) {
      printf ("%s does not exist\n", category.c_str ());
      fprintf (outfile, "%s does not exist\n", category.c_str ());
      return;
    }

  // print info
  printf ("item before %s: %d\n", name.c_str (), nLessthan (tree->theTree, name));
  fprintf (outfile, "item before %s: %d\n", name.c_str (), nLessthan (tree->theTree, name));
}

  // recursive helper function that returns n levels in tree 
int nLevels (itemNode *root) {
  if (root == nullptr) {
    return 0;
  }

   int belowL = nLevels (root->left);
   int belowR = nLevels (root->right);

  // return 1 for root plus the height of deepest subtree
  return ((belowL > belowR) ? belowL : belowR) + 1; 
}

// prints whether or not tree is balanced and n levels in each subtree
void height_balance(treeNameNode *tree, string category) {

  tree = searchNameNode (tree, category);
  if (tree == nullptr) {
      printf ("%s does not exist\n", category.c_str ());
      fprintf (outfile, "%s does not exist\n", category.c_str ());
      return;
}

  // get heights of left and right subtrees and calculate balance 
  int L = nLevels (tree->theTree->left);
  int R = nLevels (tree->theTree->right); 
  int diff = (R > L) ? R - L : L - R;

  printf("%s: left height %d, right height %d, difference %d,%s balanced\n", category.c_str (), L, R, diff, (diff > 1) ? " not" : "");
  fprintf (outfile, "%s: left height %d, right height %d, difference %d,%s balanced\n", category.c_str (), L, R, diff, (diff > 1) ? " not" : "");
}

  // recursive helper function, returns value for count to print
int itemsIn (itemNode *root) {
  if (root == nullptr) {
    return 0;
  }

  // traverse left and right subtrees and return total count 
  return root->count + itemsIn (root->left) + itemsIn (root->right);
}

  // prints the sum of items in BST 
void count (treeNameNode *tree, string category) {
  tree = searchNameNode (tree, category);
  if (tree == nullptr) {
      printf ("%s does not exist\n", category.c_str ());
      fprintf (outfile, "%s does not exist\n", category.c_str ());
      return;
    }

  // print info
  printf ("%s count %d\n", category.c_str (), itemsIn (tree->theTree));
  fprintf (outfile, "%s count %d\n", category.c_str (), itemsIn (tree->theTree));
}



  // print all item subtrees in root  with their type
void traverse_in_traverse (treeNameNode *root) {
  if (root == nullptr) {
    return;
  }

  // traverse left subtree
  traverse_in_traverse (root->left);

  // print root tree
  printf ("***%s***\n", root->name.c_str ());
  fprintf (outfile, "***%s***\n", root->name.c_str ());
  inorder (root->theTree);
  printf ("\n");
  fprintf (outfile, "\n");

  // traverse right subtree
  traverse_in_traverse (root->right);
}

// return node which holds given name
treeNameNode *searchNameNode (treeNameNode *root, string name) {
  if (root == nullptr) {
    return root;
  }

  // if name is found return current node, otherwise keep going 
  int comparison = root->name.compare (name);
  if (comparison > 0) {
    return searchNameNode (root->left, name);
  }
  else if (comparison < 0) {
    return searchNameNode (root->right, name);
  }
  else {
    return root;
  }
}

// generates treeNameNode from in.txt
treeNameNode *buildNameTree() {
  treeNameNode *root = nullptr;

  int nTreeNames = 0, nItems = 0, nQueries = 0;
  int countData = fscanf (infile, "%d %d %d", &nTreeNames, &nItems, &nQueries);

  //read into localBuff from input for as many tree names as given in header
  char *localBuff = new char[30];
  while (nTreeNames--> 0) {
      countData = fscanf (infile, "%s", localBuff);
      root = insert (root, localBuff);
    }

  // insert each given item into appropriate tree
  while (nItems-- > 0) {
      
      // read tree name, go to appropriate tree
      countData = fscanf (infile, "%s", localBuff);
      treeNameNode *a = searchNameNode (root, localBuff);
      if (a == nullptr){
	  printf ("Couldn\'t find %s\n", localBuff);
	  fprintf (outfile, "Couldn\'t find %s\n", localBuff);
	  return root;
	}

      // read item name
      countData = fscanf (infile, "%s", localBuff);

      // read item value
      int population = 0;
      countData = fscanf (infile, "%d", &population);

      // insert name or value into appropriate tree
      a->theTree = insert (a->theTree, localBuff, population);
    }

  // print generated trees
  inorder (root);
  printf ("\n");
  fprintf (outfile, "\n");
  traverse_in_traverse (root);

  // run queries
  while (nQueries-- > 0) {
      countData = fscanf (infile, "%s", localBuff);
      string query = localBuff;

      countData = fscanf (infile, "%s", localBuff);
      string category = localBuff;

      if (query == "search" || query == "item_before")
	countData = fscanf (infile, "%s", localBuff);
      string name = localBuff;
      
      if (query == "search")
	search (root, category, name);
	
      else if (query == "item_before")
	item_before (root, category, name);
	
      else if (query == "height_balance")
	height_balance (root, category);
	
      else if (query == "count")
	count (root, category);
	
      else { // something went wrong 
	  printf ("ERROR: Unrecognized Query\n");
	  fprintf (outfile, "ERROR: Unrecognized Query\n");
	}
  }

  delete[]localBuff;
  return root;
}


// main function, reads in.txt and produces out.txt
int main() {
  outfile = fopen ("out.txt", "w+");
  if (outfile == nullptr)
    printf ("There was an issue with the output file.\n");

  infile = fopen ("in.txt", "r");
  if (infile == nullptr)
    printf ("There was an issue with the input file.\n");

  treeNameNode *root = buildNameTree ();

  fclose (infile);
  fclose (outfile);
}
