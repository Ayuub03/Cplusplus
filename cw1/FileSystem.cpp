#include "FileSystem.h"

Node::Node(const string& name, bool isDir, Node* parent, Node* leftmostChild, Node* rightSibling) {
	// IMPLEMENT ME
	name_ = name;
	isDir_ = isDir;
	parent_ = parent;
	leftmostChild_ = leftmostChild;
	rightSibling_ = rightSibling;

}

Node::~Node() {
	// IMPLEMENT ME
	Node* tmp = leftmostChild_;
	while(tmp != nullptr) {
		Node* next = tmp->rightSibling_;
		delete tmp;
		tmp = next;
	}
}

Node* Node::leftSibling() const {
	// IMPLEMENT ME
	if(parent_ == nullptr) return nullptr;
	
	Node* tmp = parent_->leftmostChild_;
	
	if(tmp == this) return nullptr;
	
	while(tmp != nullptr) {
		if(tmp->rightSibling_ != this) tmp = tmp->rightSibling_;
		else break;
	}

	return tmp; 
}

FileSystem::FileSystem() {
	// IMPLEMENT ME
	curr_ = root_ = new Node("", true);
}

// DO NOT CHANGE
FileSystem::FileSystem(const string& testinput) {

	curr_ = root_ = new Node("", true);

	if (testinput == "1") {
		Node* e   = new Node("e"      , true , root_);
		Node* d   = new Node("d.txt"  , false, root_, nullptr, e);
		Node* c   = new Node("c.txt"  , false, root_, nullptr, d);
		Node* b   = new Node("b"      , true , root_, nullptr, c);
		Node* a   = new Node("a.txt"  , false, root_, nullptr, b);
		Node* ee  = new Node("ee.txt" , false, e);
		Node* bb2 = new Node("bb2"    , true , b);
		Node* bb1 = new Node("bb1"    , true , b, nullptr, bb2);
		Node* bbb = new Node("bbb.txt", false, bb1);
		root_->leftmostChild_ = a;
		b->leftmostChild_ = bb1;
		bb1->leftmostChild_ = bbb;
		e->leftmostChild_ = ee;
	}
	else if (testinput == "2") {
		Node* h = new Node("h"    , true , root_);
		Node* g = new Node("g.txt", false, root_, nullptr, h);
		Node* f = new Node("f"    , true , root_, nullptr, g);
		Node* e = new Node("e.txt", false, root_, nullptr, f);
		Node* d = new Node("d"    , true , root_, nullptr, e);
		Node* c = new Node("c.txt", false, root_, nullptr, d);
		Node* b = new Node("b"    , true , root_, nullptr, c);
		Node* a = new Node("a.txt", false, root_, nullptr, b);
		root_->leftmostChild_ = a;
	}
	else if (testinput == "3") {
		Node* c0 = new Node("c0", true, root_);
		Node* b0 = new Node("b0", true, root_, nullptr, c0);
		Node* a0 = new Node("a0", true, root_, nullptr, b0);
		Node* c1 = new Node("c1", true, a0);
		Node* b1 = new Node("b1", true, a0, nullptr, c1);
		Node* a1 = new Node("a1", true, a0, nullptr, b1);
		Node* c2 = new Node("c2", true, b0);
		Node* b2 = new Node("b2", true, b0, nullptr, c2);
		Node* a2 = new Node("a2", true, b0, nullptr, b2);
		Node* c3 = new Node("c3", true, c0);
		Node* b3 = new Node("b3", true, c0, nullptr, c3);
		Node* a3 = new Node("a3", true, c0, nullptr, b3);
		Node* c4 = new Node("c4", true, a1);
		Node* b4 = new Node("b4", true, a1, nullptr, c4);
		Node* a4 = new Node("a4", true, a1, nullptr, b4);
		root_->leftmostChild_ = a0;
		a0->leftmostChild_ = a1;
		b0->leftmostChild_ = a2;
		c0->leftmostChild_ = a3;
		a1->leftmostChild_ = a4;
	}
}

FileSystem::~FileSystem() {
	// IMPLEMENT ME
	delete root_;
}

string FileSystem::cd(const string& path) {
	// IMPLEMENT ME
	if(path == "..") {
		if(curr_ == root_) return "invalid path";
		curr_ = curr_->parent_;
		return "";
	}

	if(path == "/") {
		curr_ = root_;
		return "";
	} 

	Node* tmp = curr_->leftmostChild_;
	while(tmp != nullptr) {
		if(tmp->name_ == path) {
			if(tmp->isDir_) {
				curr_ = tmp;
				return "";
			}
			return "invalid path";
		}
		tmp = tmp->rightSibling_;
	}

	return "invalid path"; 
}

// This is done for you as an example
string FileSystem::ls() const {

	string res;

	Node* tmp = curr_->leftmostChild_;
	while(tmp != nullptr) {
		res += tmp->name_;
		if (tmp->isDir_) res += "/\n";
		else res += "\n";
		tmp = tmp->rightSibling_;
	}
	if (res != "") res.pop_back(); // remove extra \n

	return res;
}

string FileSystem::pwd() const {
	// IMPLEMENT ME
	string abspath = "";

	if(curr_ == root_) {
		abspath += "/";
		return abspath;
	}

	Node* tmp = curr_;

	while(tmp != root_) {
		abspath = "/" + tmp->name_ + abspath;
		tmp = tmp->parent_;
	}
	
	return abspath;
}

string FileSystem::tree() const {
	// IMPLEMENT ME
	Node* tmp = curr_;
	string tree; 
	traverse(tmp, 0, tree);
	if(tree != "") tree.pop_back();

	return tree;
}

//added function for tree
void FileSystem::traverse(Node* tmp, int depth, string& tree) const {
	if(tmp == nullptr) return; 
	string indent = ""; 
	
	for(int i = 0; i<depth; i++) indent += " ";
	if(depth == 0) tree += tmp->name_; 	
	else tree += indent + tmp->name_;
	
	if(tmp->isDir_) tree += "/"; 
	tree += "\n"; 
	
	traverse(tmp->leftmostChild_, depth+1, tree);
	if(tmp != curr_) traverse(tmp->rightSibling_, depth, tree);
}

string FileSystem::touch(const string& name) {
	// IMPLEMENT ME
	Node* tmp = curr_->leftmostChild_;
	while(tmp != nullptr) {
		if(tmp->name_ == name) return "file/directory already exists";
		tmp = tmp->rightSibling_;
	}

	Node* newFile = new Node(name, false, curr_);

	if(curr_->leftmostChild_ == nullptr || name < curr_->leftmostChild_->name_) {
		newFile->rightSibling_ = curr_->leftmostChild_;
		curr_->leftmostChild_ = newFile;
		return "";
	}

	tmp = curr_->leftmostChild_;
	while(tmp->rightSibling_ != nullptr && tmp->rightSibling_->name_ < name) {
		tmp = tmp->rightSibling_;
	}
	
	newFile->rightSibling_ = tmp->rightSibling_;
	tmp->rightSibling_ = newFile;
	
	return ""; 
}

string FileSystem::mkdir(const string& name) {
	// IMPLEMENT ME
	Node* tmp = curr_->leftmostChild_;
	while(tmp != nullptr) {
		if(tmp->name_ == name) return "file/directory already exists";
		tmp = tmp->rightSibling_;
	}

	Node* newDir = new Node(name, true, curr_);

	if(curr_->leftmostChild_ == nullptr || name < curr_->leftmostChild_->name_) {
		newDir->rightSibling_ = curr_->leftmostChild_;
		curr_->leftmostChild_ = newDir;
		return "";
	}

	tmp = curr_->leftmostChild_;
	while(tmp->rightSibling_ != nullptr && tmp->rightSibling_->name_ < name) {
		tmp = tmp->rightSibling_;
	}
	
	newDir->rightSibling_ = tmp->rightSibling_;
	tmp->rightSibling_ = newDir;
	
	return ""; 
}

string FileSystem::rm(const string& name) {
	// IMPLEMENT ME
	Node* tmp = curr_->leftmostChild_;
	while(tmp != nullptr && tmp->name_ != name) tmp = tmp->rightSibling_;
	if(tmp == nullptr) return "file not found";
	if(tmp->isDir_) return "not a file";

	Node* prev = tmp->leftSibling();

	if(prev == nullptr) curr_->leftmostChild_ = tmp->rightSibling_;
	else prev->rightSibling_ = tmp->rightSibling_;

	delete tmp;

	return ""; 
}

string FileSystem::rmdir(const string& name) {
	// IMPLEMENT ME
	Node* tmp = curr_->leftmostChild_;
	while(tmp != nullptr && tmp->name_ != name) tmp = tmp->rightSibling_;
	if(tmp == nullptr) return "directory not found";
	if(!tmp->isDir_) return "not a directory";
	if(tmp->leftmostChild_ != nullptr) return "directory not empty";

	Node* prev = tmp->leftSibling();

	if(prev == nullptr) curr_->leftmostChild_ = tmp->rightSibling_;
	else prev->rightSibling_ = tmp->rightSibling_;

	delete tmp;

	return ""; // dummy
}

string FileSystem::mv(const string& src, const string& dest) {
	// IMPLEMENT ME
	if(src == dest) return "source and destination are the same";

	Node* source = curr_->leftmostChild_;
	while(source != nullptr && source->name_ != src) source = source->rightSibling_;
	if(source == nullptr) return "source does not exist";

	Node* destination = curr_->leftmostChild_;
	while(destination != nullptr && destination->name_ != dest) destination = destination->rightSibling_;

	if(dest == "..") {
		if(curr_ == root_) return "invalid path";
		destination = curr_->parent_;
	}

	if(destination != nullptr) {
		if(!destination->isDir_) {
			if(source->isDir_) return "source is a directory but destination is an existing file";
			else return "destination already has file of same name";
		}
		
		Node* tmp = destination->leftmostChild_;
		while(tmp != nullptr) {
			if(tmp->name_ == source->name_) return "destination already has file/directory of same name";
			tmp = tmp->rightSibling_;
		}

		Node* prev = source->leftSibling();

		if(prev == nullptr) curr_->leftmostChild_ = source->rightSibling_;
		else prev->rightSibling_ = source->rightSibling_;

		source->parent_ = destination; 

		if(destination->leftmostChild_ == nullptr || src < destination->leftmostChild_->name_) {
			source->rightSibling_ = destination->leftmostChild_;
			destination->leftmostChild_ = source;
			return "";
		}

		tmp = destination->leftmostChild_;
		while(tmp->rightSibling_ != nullptr && tmp->rightSibling_->name_ < src) {
			tmp = tmp->rightSibling_;
		}
	
		source->rightSibling_ = tmp->rightSibling_;
		tmp->rightSibling_ = source;
		
		return "";
	}

	return "";

}
